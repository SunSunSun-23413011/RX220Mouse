/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
// LED(1秒)点滅 メインクロック20MHz
// RX220用 LCDﾗｲﾌﾞﾗﾘテスト 2022/6/30
// タイマー割込み 2022/7/1 4 5 6
// スイッチ操作 7/6  モード切替 7/6 バッテリーA/D 7/6  Beep関数対応 7/6
// センサ取り込み 7/6 7 8
// モータ動作テスト 7/8
// モータ駆動タイマ 7/11 12  姿勢制御 7/12 1&N区間前進 7/12 13 ターン 7/13 探索関数 7/13 
// 足立法実装 座標を入れようとしたが、左手法などのコードもあったので飛ばして実装する 7/13 二次走行 713
// センサ値調整 7/13  フル迷路で探索はゴールした 7/13
// 2022/7/14 RX220マウス用としてソース作成 
// 2022/7/20 ブザー部分の作成 7/21 ブザー部完成
// 2022/7/21 I/O設定を整理  7/22 ループ部など整理
// 2022/7/22 コンパイルオプション最適化 ディフォルトの2はＮＧ 1,0 は共に動作、最適化なしの0で行うことにする
// 2022/9/16 タイマーの設定値を変更
// 2022/9/21 センサ値を修正  目標速度を下げる
// 2022/9/23 前壁修正用の関数、前壁修正処理を入れる

// H8よりRX220マウス用としてソース作成 
// 2025/10/2 ソース整理 ->10/31
// 2025/11/5 ミスの修正、パラメータ試作機に合わせる。ビルドOK モータON.OFFが逆だった
// 2025/11/6 AD変換タイマー修正テスト センサ調整
// 2025\11/7 コメント整理

//#include "typedefine.h"
#include "iodefine.h"
#include "LCDrx220.h"			// LCDﾗｲﾌﾞﾗﾘ
#include "160926AccTable.h"   // モータ速度用ヘッダ

#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

//---------------------------------------------------------------
//  型宣言
//---------------------------------------------------------------
#define  uchar    unsigned char
#define  ushort   unsigned short
#define  vshort   volatile short
#define  vushort  volatile unsigned short

//-------------------------------------------------------------------------
//  ポート定義
//-------------------------------------------------------------------------
#define   CPU_LED      PORTB.PODR.BIT.B0    // CPU層LED 赤
#define   LED               PORT5.PODR.BIT.B4    // センサLEDスイッチ
#define   SW_EXEC      PORT3.PIDR.BIT.B2    // 実行スイッチ 中
#define   SW_UP         PORT3.PIDR.BIT.B1    // モード選択スイッチ+ 右
#define   SW_DOWN    PORT2.PIDR.BIT.B7    // モード選択スイッチ- 左
#define   MOTOR_EN    PORTH.PODR.BIT.B2    // モータドライバスイッチ OFF:0, ON:1  SLA7078 11/6
#define   L_MOT_MODE  PORTH.PODR.BIT.B3    // 左モータの回転方向
#define   R_MOT_MODE  PORTB.PODR.BIT.B5    // 右モータの回転方向
#define   BUZZER_TGR   MTU0.TGRB                // 周期(音程)の設定レジスタ 7/20

//-------------------------------------------------------------------------
//  マクロ定義
//-------------------------------------------------------------------------
// スイッチ関連
#define   SW_ON       0    // スイッチON (Active Low)
#define   SW_OFF      1    // スイッチOFF
#define   KEY_OFF   200    // スイッチ用チャタリングキャンセル時間
// モード関連
#define   ModeMax     8    // 動作モード数
#define   DISP        0    // モード表示
#define   EXEC        1    // モード実行
// センサ関連
#define   LED_ON      1    // センサ用LED点燈
#define   LED_OFF     0    // センサ用LED消灯
// モータ関連
#define   LeftGo      1    // 左モータ前進
#define   LeftBack    0    // 左モータ後進
#define   RightGo     0    // 右モータ前進
#define   RightBack   1    // 右モータ後進
// 探索関連
#define   GOAL_X      7    // ゴール x座標  5 
#define   GOAL_Y      8    // ゴール y座標  3 
#define   S_MODE      0    // Search Mode : 未探索区間は壁無しとして扱う
#define   T_MODE      1    // Try Mode    : 未探索区間は壁有りとして扱う

#define   GSPEED        500    // 目標速度 ディフォルト200

//---------------------------------------------------------------
//  グローバル変数定義
//---------------------------------------------------------------
vushort  wait_timer = 0;   // 内部時計( msec ) : wait関数用カウンタ
ushort   SENSOR_PT;        // 割り込み回数カウント用ポインタ
int      MODE = 0;         // 現在モード格納用
vshort   Batt;             // 電池の電圧
//ブザー関連 : 休符,ド,ド#,レ,レ#,ミ,ファ,ファ#,ソ,ソ#,ラ,ラ#,シ,ド
unsigned short beep_data[14]
   = { 0, 298, 282, 266, 252, 236, 224, 212, 200, 188, 178, 168, 158, 150 };  //20MHz/64の為値2倍に 

// センサの事前値格納用
vushort  R_PRE;           // 右センサの値
vushort  L_PRE;           // 左センサの値
vushort  F_PRE;           // 前センサの値
// センサの現在値格納用
vushort  R_SEN;           // 右センサの値
vushort  L_SEN;           // 左センサの値
vushort  F_SEN;           // 前センサの値
// センサのON/OFF用
short    R_SW;            // 右センサのスイッチ
short    L_SW;            // 左センサのスイッチ
short    F_SW;            // 前センサのスイッチ
// センサのしきい値
short    R_REF;            // 右センサしきい値
short    L_REF;            // 左センサしきい値
///short    F_REF;            // 前センサしきい値  前壁位置合わせなし
// 壁の有無判定用しきい値
short    R_LIM;            // 右壁有無しきい値
short    L_LIM;            // 左壁有無しきい値
short    F_LIM;            // 前壁有無しきい値
// モータ関連
ushort   timerL;           // 左タイマー設定値
ushort   timerR;           // 右タイマー設定値
short    ldir;             // 左モータ回転方向
short    rdir;             // 右モータ回転方向
short    speed;            // 目標速度
short    speed_now;        // 現在速度
short    MotorTimer;       // モータ電源コントロールタイマー
short    control_mode;     // 姿勢制御モード  0:なし  1:あり
	//ステップ数(割り込み内でカウントアップ) 
volatile unsigned int step_r;		//右モータ用
volatile unsigned int step_l;			//左モータ用
short stepf_r = 1;
short stepf_l = 1;

// 走行関連
short    STEP;             // モータのステップ数
short    GO_STEP;          // 1区間のステップ数
short    TURN_STEP;        // 超信旋回ステップ数
short GSPEEDvar ;		// 目標速度  -----> これはRX用として残す
// 探索関連
uchar    head;             // マウスの進行方向 0:北 1:東 2:南 3:西
uchar    head_change;      // 進行方向更新用変数 0:前 1:右 2:後 3:左
uchar    pos_x;            // マウスの現在座標 x
uchar    pos_y;            // マウスの現在座標 y
uchar    map[16][16];      // MAPデータ
uchar    p_map[16][16];    // ポテンシャルMAPデータ


//---------------------------------------------------------------
//  関数プロトタイプ宣言
//---------------------------------------------------------------
void IO_init( void );
void load_param( void );
void pause( int x );
void timerc_200us( void );	//RX
void int_mot_r(void);		//RX
void int_mot_l(void); 		//RX
void WaitKeyOff( void );
void beep(unsigned char tone,int value);
void change_mode( int x );
void exec_mode( void );
void mode0( int x );
void mode1( int x );
void mode2( int x );
void mode3( int x );
void mode4( int x );
void mode5( int x );
void mode6( int x );
void mode7( int x );
void mouse_search( int goal_x, int goal_y, int speed, int mode );
void com_go( int n );
void com_stop( void );
void com_turn( int t_mode );
void countdown( void );
void finish( void );
int get_wall_data( void );
void clear_map( void );
void make_map_data( void );
void make_potential( int gx, int gy, int mode );
int search_adachi( void );

//---------------------------------------------------------------
//  メインプログラム
//---------------------------------------------------------------
void main(void)
{

  IO_init();    // IOの初期化
  LCD_init();   // LCDの初期化
  CPU_LED = 1;  // CPU層LEDを消灯 赤
  LED = LED_OFF;                        // LEDを消灯
  MOTOR_EN =0;  // モータOFF

  // 起動音
  beep( 1, 150 );
  beep( 8, 150 );
  beep( 1, 150 );
  beep( 8, 150 );
  // タイトル表示
  LCD_print( 0, "LE-S200P" );

  // 電圧表示
  LCD_print( 8, "   .  v " );
  LCD_dec_out( 9, Batt/100, 1);    // 十の位を表示
  Batt %= 100;                     // 十の位を削除
  LCD_dec_out(10, Batt/10 , 1);    // 一の位を表示
  Batt %= 10;                      // 一の位を削除
  LCD_dec_out(12, Batt    , 1);    // 残った小数値を表示
  pause( 2000 );

  clear_map();                     // MAPデータ初期化
  load_param();                    // 各種パラメータを読み込み
  change_mode( 0 );                // まず初期画面にする = Mode0

  // メインループ
  while( 1 ){
    if( SW_UP == SW_ON ){          // 上SWが押されている場合
      WaitKeyOff();                // チャタリング防止処理
      change_mode(+1);             // モード+1
    }else if( SW_DOWN == SW_ON ){  // 下SWが押されている場合
      WaitKeyOff();                // チャタリング防止処理
      change_mode(-1);             // モード-1
    }else if( SW_EXEC == SW_ON ){  // 実行SWが押されている場合
      beep( 3, 150 );              // 実行音 : ド
      WaitKeyOff();                // チャタリング防止処理
      exec_mode();                 // モード実行
      MODE = 0;
      change_mode( 0 );            // 実行後は初期画面に戻す
    }

    // モードが0ならセンサデータをLCD表示
    if( MODE == 0 )
    {
      LCD_dec_out(  3, F_SEN, 3 ); // 前センサ値をLCD上中央に表示
      LCD_dec_out(  9, L_SEN, 3 ); // 左センサ値をLCD左下に表示
      LCD_dec_out( 13, R_SEN, 3 ); // 右センサ値をLCD右下に表示
      
    }
  }
}

//---------------------------------------------------------------
//  RX220初期化 (ここは後で整理7/14)
//---------------------------------------------------------------
void IO_init( void )
{
  // ===== クロック設定 =====           
    SYSTEM.PRCR.WORD = 0xa50b;		// クロックソース選択の保護解除
    
    SYSTEM.SCKCR.BIT.PCKB = 0x00;	// PCLKB 1分周  7/6
    SYSTEM.SCKCR.BIT.ICK = 0x00;		// ICLK 1分周

    // クロックソースの選択
    SYSTEM.SCKCR3.WORD = 0x0200;	//大元のクロックをメインクロック(20MHz)を使用

    //クロックの元栓の設定
    SYSTEM.MOSCCR.BYTE = 0;		// メインクロック発振器 動作:0 停止:1
    SYSTEM.SOSCCR.BYTE = 0;		// サブクロック発振器 動作:0 停止:1

  // ===== I/O ポートの初期化 =====           ピン番号  7654 3210
//    -------設定まとめた形に----- 7/21
    PORT0.PODR.BYTE=0x00;
    PORT0.PDR.BYTE=0x28;		// 03,05を出力設定 0010 1000
    PORT1.PDR.BYTE=0x30;		// 14,15を出力設定 0011 0000
    PORT5.PDR.BIT.B4=1;		// ポート54 出力設定
    PORTA.PODR.BYTE=0x00;
    PORTA.PDR.BYTE=0x5b;	// ポートA出力設定 0101 1011 存在ピン:0,1,3,4,6 
    PORTB.PODR.BYTE=0x00;
    PORTB.PDR.BYTE=0xeb;	// ポートB出力設定 1110 1011 存在ピン:0,1,3,5,6,7
    PORTC.PODR.BYTE=0x00;
    PORTH.PODR.BYTE=0x00;
    PORTH.PDR.BYTE=0x0f;		// ポートH出力設定 0000 1111 存在ピン:0,1,2,3

    PORT3.PDR.BIT.B1=0;		// P31 入力設定 
    PORT3.PDR.BIT.B2=0;		// P32 入力設定 
    PORT2.PDR.BIT.B7=0;		// P27 入力設定 
    PORT3.PCR.BIT.B1=1;		// P31 プルアップ設定 
    PORT3.PCR.BIT.B2=1;		// P32 プルアップ設定 
    PORT2.PCR.BIT.B7=1;		// P27 プルアップ設定 

  // ===== バッテリー電圧計測 =====
  // ===== A/D 設定 =====
  SYSTEM.PRCR.WORD = 0xA502;
  MSTP(S12AD) = 0;				//12bitAD変換スタンバイ解除
  SYSTEM.PRCR.WORD = 0xA500;	
  S12AD.ADCER.BIT.ADRFMT = 0;	//右づめ
  S12AD.ADCSR.BIT.ADCS = 0;		//シングルスキャンモード
  S12AD.ADCSR.BIT.ADST = 0;	//AD変換停止
  
	// バッテリー電圧読取
  S12AD.ADANSA.WORD = 0x0200;		//AN009
  S12AD.ADCSR.BIT.ADST=1;			//AD変換開始
  while(S12AD.ADCSR.BIT.ADST == 1);	//AD変換終了まで待つ
  Batt = S12AD.ADDR9 >> 3;             // 測定データAN9を取り込む 10bitにして H8も最下位bitを切っているようだ
  
  
  // ===== タイマーの初期化 =====   7/5
  // CMT タイマ割込み設定
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP( CMT0 ) = 0;					// Wakeup CMT0,CMT1
   	SYSTEM.PRCR.WORD = 0xA500;	

	//CMT0は制御割り込み用タイマとして使用[timerc_200us]
	CMT0.CMCR.BIT.CKS=0;				// 20MHz/8 2.5MHz PCLK/8:0 /32:1 /128:2 /512:3
	CMT0.CMCR.BIT.CMIE=1;				//コンペアマッチ割込み許可
	CMT0.CMCNT=0;			//カウンターのクリア  無くても動作する影響は最初の１回だから
	CMT0.CMCOR=500-1;		//2.5MHz/500 =5kHz:200us

	IEN( CMT0, CMI0 ) = 1;				// CMI0 Enable 割込み要求許可
	IPR( CMT0, CMI0 ) = 15;				// CMI0 Interrupt Level is 1 割込み優先度 Pico:15
	IR(CMT0,CMI0)=0;				//割り込みステータフラグをクリア
	CMT.CMSTR0.BIT.STR0 = 1;			// Start CMT0

  // MTU タイマ割込み設定      
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(MTU) = 0;			//MTUモジュールON
	SYSTEM.PRCR.WORD = 0xA500;	
	
	MTU.TSTR.BYTE=0;		//タイマ動作ストップ

	// I/Oの設定
	MPC.PWPR.BIT.B0WI=0;		//PFSWEビットへの書き込みを許可
	MPC.PWPR.BIT.PFSWE=1;		//PFSレジスタへの書き込みを許可
	MPC.P14PFS.BIT.PSEL = 1;	//P14(L_MOTOR_STEP)をMTIOC0Aに設定
	MPC.PB3PFS.BIT.PSEL = 2;	//PB3(R_MOTOR_STEP)をMTIOC0Cに設定
	MPC.P15PFS.BIT.PSEL = 1;	//P15をMTIOC0Bとして使用する 7/20
	PORT1.PMR.BIT.B4 = 1;		//周辺モジュールとして使用
	PORTB.PMR.BIT.B3 = 1;		//周辺モジュールとして使用
	PORT1.PMR.BIT.B5 = 1;		//周辺モジュールとして使用出力 7/20

	//スピーカー用MTU MTIOC0B(P15) 7/20 21
	MSTP_MTU0 = 0;					//MTU0スタンバイ解除
	MTU0.TCR.BIT.CCLR=2;	//PWM TGRBのコンペアマッチでTCNTクリア 
	MTU0.TCR.BIT.TPSC=3;	//PCLK/64 20/64=0.3125MHz=312.5kHz
	MTU0.TMDR.BIT.MD = 0;		// ノーマルモードに設定
	MTU0.TIORH.BIT.IOB = 3;		//初期出力Lコンペアマッチでトグル
	MTU0.TGRB = 0;			// 周期(音程)の設定レジスタ(BUZZER_TGR) : 0(最初は休符)

	//右モータ用MTU設定 MTICA4A(PB3)
	MTU.TOER.BIT.OE4A = 1;		//MTU端子出力許可 MTU4では必要
	MTU4.TCR.BIT.TPSC=2;	//PCLK/16 20/16=1.25MHz CMT0の20/8の半分 0.8μS

	MTU4.TCR.BIT.CCLR=1;	//PWM TGRAのコンペアマッチでTCNTクリア
	MTU4.TMDR.BIT.MD=2;		//PWM1
	MTU4.TIORH.BIT.IOA=1;	//初期出力LンペアマッチL出力
	MTU4.TIORH.BIT.IOB=2;	//初期出力LコンペアマッチH出力
	MTU4.TGRA = 2500;		// 1/(0.8e-6x2500) = 500Hz
	MTU4.TGRB = 50;
	MTU4.TGRC = 2500;
	MTU4.TMDR.BIT.BFA = 1;	//TGRA,TGRCをバッファーモードに設定
	MTU4.TIER.BIT.TGIEB = 1;//GRBコンペアマッチでの割り込み許可
	IEN(MTU4,TGIB4) = 1;	//割り込み要求を許可 
	IPR(MTU4,TGIB4) = 12;	//割り込み優先度を次点に設定
	IR(MTU4,TGIB4)=0;		//割り込みステータフラグをクリア

	//左モータ用MTU設定 MTIOCA3A(P14)
	MTU3.TCR.BIT.TPSC=2;	//PCLK/16 20/16=1.25MHz CMT0の20/8の半分 0.8μS

	MTU3.TCR.BIT.CCLR=1;	//PWM TGRAのコンペアマッチでTCNTクリア
	MTU3.TMDR.BIT.MD=2;		//PWM1
	MTU3.TIORH.BIT.IOA=1;	//初期出力LコンペアマッチL出力
	MTU3.TIORH.BIT.IOB=2;	//初期出力LコンペアマッチH出力
//	MTU3.TGRA = 5000;		// 1/(0.8e-6x5000) = 250Hz
//	MTU3.TGRA = 1250;		// 1/(0.8e-6x1250) = 1kHz
	MTU3.TGRA = 2500;		// 1/(0.8e-6x2500) = 500Hz
	MTU3.TGRB = 50;
	MTU3.TGRC = 2500;
	MTU3.TMDR.BIT.BFA = 1;	//TGRA,TGRCをバッファーモードに設定
	MTU3.TIER.BIT.TGIEB = 1;//GRBコンペアマッチでの割り込み許可
	IEN(MTU3,TGIB3) = 1;	//割り込み要求を許可 
	IPR(MTU3,TGIB3) = 13;	//割り込み優先度を次点に設定
	IR(MTU3,TGIB3)=0;		//割り込みステータフラグをクリア

	MTU.TSTR.BIT.CST0 = 0;	//タイマストップ SP 7/20
	MTU.TSTR.BIT.CST3 = 0;	//タイマストップ
	MTU.TSTR.BIT.CST4 = 0;	//タイマストップ


  R_SW = LED_ON;             // 右センサON
  L_SW = LED_ON;             // 左センサON
  F_SW = LED_ON;             // 前センサON

}

//---------------------------------------------------------------
//  パラメータ読み込み
//---------------------------------------------------------------
void load_param( void ) 
{
  // センサしきい値の決め打ち
  R_REF   = 490;    // 区画中央での右センサ値 11/6[147-459-537,317] 400
  L_REF   = 640;    // 区画中央での左センサ値 11/6[387-612-587,478] 550
  // 壁の有無判定用しきい値:各センサ壁あり最小値と壁なし値の中間値
  R_LIM   =  150;    // 右 11/6[147-459-537,317] 350
  L_LIM   = 150;    // 左 11/6[387-612-587,478] 500
  F_LIM   = 190;    // 前 11/6[71-340-925] 100 150
  // 走行パラメータ  // 1-2相励磁
    GO_STEP   = 1640; // 1区間前進ステップ数  
    TURN_STEP = 550;  // 90度旋回ステップ数  
     GSPEEDvar = GSPEED;		// 目標速度設定

}

//---------------------------------------------------------------
//  Timer  CMT0 割り込み(200us毎にこの関数が勝手に優先して実行される) [int_timerw]の代わり
//---------------------------------------------------------------
// Pico3に合わせる。「#pragma interrupt」を使わず、intprg.c内に関数を書いて、呼び出させる。」
void timerc_200us( void )
{
  int err_l, err_r;
  ushort acc_num, lspeed, rspeed;

  // 左モータ割り込み
    MTU3.TGRC = timerL;                     // 次の速度をセット
    if( speed != 0 ){ 
	MTU.TSTR.BIT.CST3 = 1;	//カウントスタート
    }else{      // 停止ならパルスをださない
	MTU.TSTR.BIT.CST3 = 0;	//タイマストップ
    } 
    if( ldir == 0 ){  L_MOT_MODE = LeftGo;    // 正転
    }else{             L_MOT_MODE = LeftBack;  // 反転
    }

  // 右モータ割り込み
    MTU4.TGRC = timerR;                     // 次の速度をセット
    if( speed != 0 ){ 
	MTU.TSTR.BIT.CST4 = 1;	//カウントスタート
    }else{      // 停止ならパルスをださない
	MTU.TSTR.BIT.CST4 = 0;	//タイマストップ
    } 
    if( rdir == 0 ){ R_MOT_MODE = RightGo;   // 正転
    }else{             R_MOT_MODE = RightBack; // 反転
    }

  // モータスピード割り込み 
  if((stepf_r == 1) || (stepf_l == 1)){
    stepf_l = 0;
    stepf_r = 0;
    // モータの加速処理
    if( speed == 0 ){                         // モータ停止中の処理
      speed_now = 0;                         // 速度を0にする
      timerL = 2500;                        // 左 割り込み周期2ms 1/(0.8e-6x2500) = 500Hz
      MTU3.TGRC = timerL;
      timerR = 2500;                        // 右
      MTU4.TGRC = timerR;

//      CPU_LEDB = 1;  // CPU層LEDを消灯 青
    }else{
      if( speed > speed_now )       speed_now++;  // 加速
      else if( speed < speed_now )  speed_now--;  // 減速
      if( speed_now >= 2000 ) speed_now = 1999;     // 最高速度
      if( speed_now < 0     ) speed_now = 0;      // 最低速度

      acc_num = AccTable[ speed_now ];     // 加速度テーブルから値取得

      // 姿勢制御
      if( control_mode == 1 )
      {
        // 偏差を計算
        err_l = L_SEN - L_REF;  // 左偏差を計算
        err_r = R_SEN - R_REF;  // 右偏差を計算
        // 壁情報から偏差を加工
        if( L_SEN > L_LIM || R_SEN > R_LIM )
        {
          // どちらかに壁がある:偏差が大きい側を優先して補正
          if( err_l > err_r )
            err_r = -1 * err_l;
          else
            err_l = -1 * err_r;
        }else
        {
          // 両方壁なし:補正なし
          err_l = 0;
          err_r = 0;
        }
        // 偏差を用いて補正
          lspeed = acc_num + err_l;    // ここをどうするかはテストが必要 7/14
          rspeed = acc_num + err_r;   // 
      }else{  // control_mode = 0 
        lspeed = acc_num ;
        rspeed = acc_num ;
      }
//      timerL =  10000000L / lspeed; 元の値
//      timerR =  10000000L / rspeed;
      timerL =  1500000L / lspeed;			// 前回の速いと一応の間 
      timerR =  1500000L / rspeed;			// 
    }
  }


    SENSOR_PT++;                 // タスクポインタの更新
    if( SENSOR_PT == 5 ) SENSOR_PT = 0;  // 0-4の5カウント:200us*5=1ms
                                 // 各処理は1ms周期で実行される
    switch( SENSOR_PT )          // タスクポインタに従って処理を行う
    {
      case 0:  // 1msecタイマー&LCDの更新
               wait_timer++;     // wait関数用カウンタ
               LCD();            // LCD更新処理
               break;

      case 1:  // 右センサ消灯時の測定 AN0
               if ( R_SW == LED_OFF ) break;         // センサON/OFFの確認
               S12AD.ADANSA.WORD = 0x0001;		//AN000
               S12AD.ADCSR.BIT.ADST=1;			//AD変換開始
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD変換終了まで待つ
//               R_PRE = S12AD.ADDR0 >> 2;       // 測定データを取り込む 0 - 1023(max) 10bit
               R_PRE = S12AD.ADDR0 >> 1;       // 測定データを取り込む 11bit化 
//               R_PRE = S12AD.ADDR0 ;       // 測定データを取り込む 12bit 
               // 右センサ点灯時の測定 AN0
               LED = LED_ON;                         // LEDを点灯
//               LCD_wait(10);                         // しばらく待つ   
               LCD_wait(20);                         // しばらく待つ 2倍に 11/5
               S12AD.ADANSA.WORD = 0x0001;		//AN000
               S12AD.ADCSR.BIT.ADST=1;			//AD変換開始
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD変換終了まで待つ
               LED = LED_OFF;                        // LEDを消灯
//               R_PRE = (S12AD.ADDR0 >> 2) - R_PRE;       // 測定データを取り込む 10bit
               R_PRE = (S12AD.ADDR0 >> 1) - R_PRE;       // 測定データを取り込む 11bit化 
//               R_PRE = S12AD.ADDR0  - R_PRE;       // 測定データを取り込む 12bit
                                                     // 事前計測値との差分を取る(ノイズ処理)
               if( R_PRE <= 999 )  R_SEN = R_PRE;    // 表示上限処理
               else                R_SEN = 999; 
               break;

      case 2:  // 左センサ消灯時の測定 AN1
               if ( L_SW == LED_OFF ) break;         // センサON/OFFの確認
               S12AD.ADANSA.WORD = 0x0002;		//AN001
               S12AD.ADCSR.BIT.ADST=1;			//AD変換開始
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD変換終了まで待つ
//               L_PRE = S12AD.ADDR1 >> 2;       // 測定データを取り込む 0 - 1023(max) 10bit
               L_PRE = S12AD.ADDR1 >> 1;       // 測定データを取り込む 11bit化
//               L_PRE = S12AD.ADDR1 ;       // 測定データを取り込む 12bit 
               // 左センサ点灯時の測定 AN1
               LED = LED_ON;                         // LEDを点灯
//               LCD_wait(10);                         // しばらく待つ
               LCD_wait(20);                         // しばらく待つ 2倍に 11/5
               S12AD.ADANSA.WORD = 0x0002;		//AN001
               S12AD.ADCSR.BIT.ADST=1;			//AD変換開始
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD変換終了まで待つ
               LED = LED_OFF;                        // LEDを消灯
//               L_PRE = (S12AD.ADDR1 >> 2) - L_PRE;       // 測定データを取り込む 10bit
               L_PRE = (S12AD.ADDR1 >> 1) - L_PRE;       // 測定データを取り込む 11bit化
//               L_PRE = S12AD.ADDR1 - L_PRE;       // 測定データを取り込む 12bit
                                                     // 事前計測値との差分を取る(ノイズ処理)
               if( L_PRE <= 999 )  L_SEN = L_PRE;    // 表示上限処理
               else                L_SEN = 999;
               break;

      case 3:  // 前センサ消灯時の測定 ,AN2
               if ( F_SW == LED_OFF ) break;         // センサON/OFFの確認
               S12AD.ADANSA.WORD = 0x0004;		//AN002
               S12AD.ADCSR.BIT.ADST=1;			//AD変換開始
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD変換終了まで待つ
//               F_PRE = S12AD.ADDR2 >> 2;       // 測定データを取り込む 0 - 1023(max) 10bit
               F_PRE = S12AD.ADDR2 >> 1;       // 測定データを取り込む 11bit化
//               F_PRE = S12AD.ADDR2 ;       // 測定データを取り込む 12bit
               // 前センサ点灯時の測定 AN2
               LED = LED_ON;                         // LEDを点灯
//               LCD_wait(10);                         // しばらく待つ
               LCD_wait(20);                         // しばらく待つ 2倍に 11/5
               S12AD.ADANSA.WORD = 0x0004;		//AN002
               S12AD.ADCSR.BIT.ADST=1;			//AD変換開始
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD変換終了まで待つ
               LED = LED_OFF;                        // LEDを消灯
//               F_PRE = (S12AD.ADDR2 >> 2) - F_PRE;       // 測定データを取り込む 10bit
               F_PRE = (S12AD.ADDR2 >> 1) - F_PRE;       // 測定データを取り込む 11bit化
//               F_PRE = S12AD.ADDR2  - F_PRE;       // 測定データを取り込む 12bit オーバフローする
                                                     // 事前計測値との差分を取る(ノイズ処理)
               if( F_PRE <= 999 )  F_SEN = F_PRE;
               else                F_SEN = 999;        // 表示上限処理
               break;

      case 4:  // モータ用電源コントロール
               if( speed != 0 ) MotorTimer = 3000;   // モータ動作時はタイマーセット
               else             MotorTimer--;        // モータ停止時はカウントダウン
               if( MotorTimer < 0 )  MotorTimer =  0;
               // モータを動かさない時は電源をOFF(モータ停止から3秒後)
               if( MotorTimer == 0 )  MOTOR_EN   =  0;  // OFF
               else                   MOTOR_EN   =  1;  // ON
               break;

      default: break;
    }
  
}

//---------------------------------------------------------------
//  モータステップ数カウント関数   RX追加
//---------------------------------------------------------------
void int_mot_r(void)	//右モータが１ステップ進む毎の割り込み
{
	step_r++;			//ステップ数をカウント
       stepf_r = 1;			// 
       STEP++;                     // 距離カウンタ更新 
}

void int_mot_l(void)	//左モータが１ステップ進む毎の割り込み
{
	step_l++;			//ステップ数をカウント
       stepf_l = 1;			//  
       STEP++;                    // 距離カウンタ更新 
}

//---------------------------------------------------------------
//  wait関数(1msタイマー)
//---------------------------------------------------------------
void pause( int x )
{
  wait_timer = 0;
  while( wait_timer != x ); // 終了時間まで待つ
}

//-------------------------------------------------------------------------
//  キーオフ処理
//-------------------------------------------------------------------------
void WaitKeyOff( void )
{
  // チャタリング防止処理
  pause( KEY_OFF );             // 設定した時間([ms])待つ
  // 全てのスイッチがOFFになるまでループして待つ
  while(( SW_UP == SW_ON )||( SW_DOWN == SW_ON )||( SW_EXEC == SW_ON ));
}

//------------------------------------------------------------------------
/// ビープ音  タイマVがないので、対応が必要 7/6 LEDで呼び出し確認可能に MTU0で作成 
// ビープ音  タイマVがないので、LEDで呼び出し確認可能に MTU0で作成 
//------------------------------------------------------------------------
void beep(unsigned char tone,int value)
{

  BUZZER_TGR = beep_data[ tone ];  // 音程の設定 20MHz/64 ように値を2倍に修正 7/22
  MTU.TSTR.BIT.CST0 = 1;			//Beep動作開始 タイマスタート SP 7/20
  pause( value );                         // Beep音の長さ
  MTU.TSTR.BIT.CST0 = 0;			//Beep動作停止 タイマストップ SP 7/20

}

//-------------------------------------------------------------------------
//  モード表示
//-------------------------------------------------------------------------
void change_mode( int x )
{
  MODE += x;                            // モード更新
  if( MODE >= ModeMax ) MODE = 0;       // モードが超えている場合は0に戻す
  if( MODE < 0 )  MODE = ModeMax - 1;   // モードが負の場合はモードを最大値に設定

  if     ( MODE == 0 ) mode0( DISP );   // Mode0:
  else if( MODE == 1 ) mode1( DISP );   // Mode1:
  else if( MODE == 2 ) mode2( DISP );   // Mode2:
  else if( MODE == 3 ) mode3( DISP );   // Mode3:
  else if( MODE == 4 ) mode4( DISP );   // Mode4:
  else if( MODE == 5 ) mode5( DISP );   // Mode5:
  else if( MODE == 6 ) mode6( DISP );   // Mode6:
  else if( MODE == 7 ) mode7( DISP );   // Mode7:
}

//-------------------------------------------------------------------------
//  モード処理
//-------------------------------------------------------------------------
void exec_mode( void )
{
  if     ( MODE == 0 ) mode0( EXEC );   // Mode0:
  else if( MODE == 1 ) mode1( EXEC );   // Mode1:
  else if( MODE == 2 ) mode2( EXEC );   // Mode2:
  else if( MODE == 3 ) mode3( EXEC );   // Mode3:
  else if( MODE == 4 ) mode4( EXEC );   // Mode4:
  else if( MODE == 5 ) mode5( EXEC );   // Mode5:
  else if( MODE == 6 ) mode6( EXEC );   // Mode6:
  else if( MODE == 7 ) mode7( EXEC );   // Mode7:
}

//-------------------------------------------------------------------------
//  Mode0 : センサチェック
//-------------------------------------------------------------------------
void mode0( int x ) 
{
  if( x == DISP )  // DISPモードの場合
  {
    // モード内容表示
    LCD_print( 0, "0:Sensor" );
    LCD_print( 8, "        " );
    pause( 1000 );
    LCD_print( 0, "  F     " );
    LCD_print( 8, "L   R   " );
    return;                     // 以下の実行処理をしないで戻る
  }

  // 実行モードの場合
  L_REF = 0; R_REF = 0;         // データ初期化

  for( x = 0; x < 32; x++ )     // データ測定(64ポイント)
  {
    L_REF += L_SEN;
    R_REF += R_SEN;
    pause(1);
  }

  R_REF = R_REF / 32;           // 測定データを平均化
  L_REF = L_REF / 32;

  LCD_print( 0, " L    R " );
  LCD_print( 8, "        " );
  LCD_dec_out(  8, L_REF, 3 );  // 左センサ値をLCDに表示
  LCD_dec_out( 13, R_REF, 3 );  // 右センサ値をLCDに表示

  pause( 2000 );                // 2秒間表示
}

//-------------------------------------------------------------------------
//  Mode1 : モータテスト
//-------------------------------------------------------------------------
void mode1(int x)
{

  if( x == DISP )  // DISPモードの場合
  {
    // モード内容表示
    LCD_print( 0, "1:M-TEST" );
    LCD_print( 8, "        " );
    return;                     // 以下の実行処理をしないで戻る
  }

  // 実行モードの場合
  LCD_print( 8,"SPD=     ");
  rdir = 0; ldir = 0;           // 回転方向を直進
  control_mode = 1;             // 直線走行用姿勢制御あり
  STEP = 0;                               // 距離カウンタクリア ☆

  while(1){
    LCD_dec_out( 12, speed, 4 );
    if( SW_UP   == 0 ) { speed += 100; WaitKeyOff(); }
    if( SW_DOWN == 0 ) { speed -= 100; WaitKeyOff(); }
    if( SW_EXEC == 0 ) { speed = 0; return; }

    if( speed > 500 )    speed = 500;
    else if( speed < 0 )  speed = 0;
  }
}

//-------------------------------------------------------------------------
//  Mode2 : 1区間前進
//-------------------------------------------------------------------------
void mode2(int x)
{

  if( x == DISP )  // DISPモードの場合
  {
    // モード内容表示
    LCD_print( 0, "2: 1 GO " );
    LCD_print( 8, "STEP    " );
    return;                     // 以下の実行処理をしないで戻る
  }

  // 実行モードの場合
  while(1){
    LCD_dec_out( 12, GO_STEP, 4 );
    if( SW_UP   == 0 ) { GO_STEP += 10; WaitKeyOff(); }
    if( SW_DOWN == 0 ) { GO_STEP -= 10; WaitKeyOff(); }
//    if( SW_EXEC == 0 ) { WaitKeyOff();  com_go( 1 );  com_stop(); }
    if( SW_EXEC == 0 ) { WaitKeyOff();  com_go( 1 );  com_stop(); break; }
  }

}

//-------------------------------------------------------------------------
//  Mode3 : N区間前進
//-------------------------------------------------------------------------
void mode3(int x)
{
  int n = 5;                    // 前進区間数：初期値 5
  if( x == DISP )  // DISPモードの場合
  {
    // モード内容表示
    LCD_print( 0, "3: N GO " );
    LCD_print( 8, "     N  " );
    return;                     // 以下の実行処理をしないで戻る
  }

  // 実行モードの場合
  LCD_dec_out( 8, GO_STEP, 4 );
  while(1){
    LCD_dec_out( 14, n, 2 );
    if( SW_UP   == 0 ) { n++; WaitKeyOff(); }
    if( SW_DOWN == 0 ) { n--; WaitKeyOff(); }
    if( SW_EXEC == 0 ) { WaitKeyOff();  com_go( n );  com_stop(); }
  }
}

//-------------------------------------------------------------------------
//  Mode4 : 180ターンR
//-------------------------------------------------------------------------
void mode4( int x )
{
  if( x == DISP )  // DISPモードの場合
  {
    // モード内容表示
    LCD_print( 0, "4: TURN " );
    LCD_print( 8, "        " );
    return;                     // 以下の実行処理をしないで戻る
  }

  // 実行モードの場合
  while(1){
    LCD_dec_out( 10, TURN_STEP, 4 );
    if( SW_UP   == 0 ) { TURN_STEP += 10; WaitKeyOff(); }
    if( SW_DOWN == 0 ) { TURN_STEP -= 10; WaitKeyOff(); }
    if( SW_EXEC == 0 ) { com_turn(2); com_stop(); }
  }
}

//-------------------------------------------------------------------------
//  Mode5 : 探索走行 
//-------------------------------------------------------------------------
void mode5( int x )
{
  if( x == DISP )  // DISPモードの場合
  {
    // モード内容表示
    LCD_print( 0, "5:Search" );
    LCD_print( 8, "Spd " );
    LCD_dec_out( 12, GSPEEDvar, 3 );   //現在の設定スピード
    return;                     // 以下の実行処理をしないで戻る
  }

  // 実行モードの場合
  pos_x = 0; pos_y = 0; head = 0;
  // 往復探索
  mouse_search( GOAL_X, GOAL_Y, GSPEEDvar, S_MODE );  // 行きの探索
  mouse_search( 0, 0, GSPEEDvar, S_MODE );            // 帰りの探索

}

//-------------------------------------------------------------------------
//  Mode6 : 二次走行
//-------------------------------------------------------------------------
void mode6( int x )
{
  if( x == DISP )  // DISPモードの場合
  {
    // モード内容表示
    LCD_print( 0, "6:Try   " );
    LCD_print( 8, "Spd " );
    LCD_dec_out( 12, GSPEEDvar, 3 );   //現在の設定スピード
    return;                     // 以下の実行処理をしないで戻る
  }

  // 実行モードの場合
  // 二次走行
  pos_x = 0; pos_y = 0; head = 0;
  mouse_search( GOAL_X, GOAL_Y, GSPEEDvar, T_MODE );	// 二次走行

}

//-------------------------------------------------------------------------
// Mode7 :探索走行 帰りの探索無し 
//-------------------------------------------------------------------------
void mode7( int x )
{
///short sp = 50;	// 速度変更用
  if( x == DISP )  // DISPモードの場合
  {
    // モード内容表示
    LCD_print( 0, "Sear+-:7" );
    LCD_print( 8, "Sear  x+-" );
    return;                     // 以下の実行処理をしないで戻る
  }

  // 実行モードの場合
  pos_x = 0; pos_y = 0; head = 0;
  // 探索
  mouse_search( GOAL_X, GOAL_Y, GSPEEDvar, S_MODE );  // 行きの探索
}

//-------------------------------------------------------------------------
//  探索関数    コンパイル最適化を外し元に戻す★ 7/22
//-------------------------------------------------------------------------
void mouse_search( int goal_x, int goal_y, int spd, int mode )
{
  short motion;
  countdown();                  // カウントダウン

  while( 1 ){
    // １つのループは区間中心から次の区間中心まで
    // 最初に半区画直進
    control_mode = 1;             // 姿勢制御ON
    rdir = 0; ldir = 0;           // 回転方向を直進
    step_r = 0;                        //右ステップ数をリセット
    step_l = 0;                        //左ステップ数をリセット
    STEP = 0;                     // 距離カウンタリセット
    speed = spd;                  // 速度設定
    CPU_LED = 1;  // CPU層LEDを消灯 赤 9/23
 
    // 座標更新
    if     ( head == 0 ) pos_y++; // 北向き y+1
    else if( head == 1 ) pos_x++; // 東向き x+1
    else if( head == 2 ) pos_y--; // 南向き y-1
    else if( head == 3 ) pos_x--; // 西向き x-1
    
    // ポテンシャルMAP計算
    make_potential( goal_x, goal_y, mode );
 
    while( STEP < GO_STEP / 2 );  // 半区間進む 

    // 柱まで進んだら
    // 壁情報取得＆MAPデータ上書き
    if( mode == S_MODE )
    make_map_data();

    // 足立法で行動決定
    motion = search_adachi();
    
    // ゴール時の例外処理（上で決めた行動が上書きされる）
    if( pos_x == goal_x && pos_y == goal_y )
      motion = 4;                       // ゴール到達：反転停止

    // 行動を実行
    switch( motion ){
      // 直進
      case  0 : while( STEP < GO_STEP );  // 残り半区間進む 
                head_change = 0;          // 進行方向更新変数を前に設定
                break;
      // 右折
      case  1 : while( STEP < GO_STEP - speed_now * 2 );  // 減速域を残して直進 
                speed = 1;
                while( STEP < GO_STEP );  // 残りステップ数で減速 
                com_turn( 0 );            // 右90度旋回
                head_change = 1;          // 進行方向更新変数を右に設定
                break;
      // 反転
      case  2 : while( STEP < GO_STEP - speed_now * 2 );  // 減速域を残して直進 
                speed = 1;
                while( STEP < GO_STEP );  // 残りステップ数で減速 
                com_turn( 2 );            // 反転
                head_change = 2;          // 進行方向更新変数を後に設定
                break;
      // 左折
      case  3 : while( STEP < GO_STEP - speed_now * 2 );  // 減速域を残して直進 
                speed = 1;
                while( STEP < GO_STEP );  // 残りステップ数で減速 
                com_turn( 1 );            // 左90度旋回
                head_change = 3;          // 進行方向更新変数を左に設定
                break;
      // 反転停止
      case  4 : while( STEP < GO_STEP - speed_now * 2 );  // 減速域を残して直進 
                speed = 1;
                while( STEP < GO_STEP );  // 残りステップ数で減速 //
                com_turn( 2 );            // 反転
                com_stop();               // 停止
                head_change = 2;          // 進行方向更新変数を後に設定
                head = ( head + head_change ) & 0x03; // 詳細は下を参照
                finish();                 // ゴール音
                return;                   // ループ終了
                break;
      // その他
      default : com_stop();               // 停止
                head_change = 0;          // 進行方向更新変数を前に設定
                head = ( head + head_change ) & 0x03; // 詳細は下を参照
                return;                   // ループ終了
                break;
    }
    
    // 進行方向更新変数head_changeを用いて現在の進行方向headを更新
    head = ( head + head_change ) & 0x03; // 更新数値を加算して2進数下2桁でマスク
                                          // 00 -> 01 -> 10 -> 11 -(マスク)-> 00
  }
}

//-------------------------------------------------------------------------
//  直進モジュール (N区間前進) 
//-------------------------------------------------------------------------
void com_go( int n )
{
  control_mode = 1;                       // 直線走行用姿勢制御
  step_r = 0;                               //右ステップ数をリセット
  step_l = 0;                               //左ステップ数をリセット
  STEP = 0;                               // 距離カウンタクリア
  rdir = 0; ldir = 0;                     // 回転方向を直進

  // 加速モード
  speed = GSPEED;        // 目標速度設定
  while( speed > speed_now );                   // 目標速度になるまで加速 

  // 定速モード
  speed = speed_now;  // 加速後の速度
  while( STEP < GO_STEP * n - speed_now * 2 );  // 減速ステップ数を残して定速移動
                                                // 全体ステップ数-減速用ステップ数

  // 減速モード
  speed = 1;          // 最低速度設定
  while( STEP < GO_STEP * n );                  // 残りのステップ数で減速 
}

//-------------------------------------------------------------------------
//  停止モジュール
//-------------------------------------------------------------------------
void com_stop( void )
{
  control_mode = 0;           // 姿勢制御無し
  rdir = 0; ldir = 0;         // モータの回転方向を前進
  step_r = 0;                               //右ステップ数をリセット
  step_l = 0;                               //左ステップ数をリセット
  STEP = 0;                   // 距離カウンタをリセット
  speed = 0;  speed_now = 0;  // モータの制御用の変数をリセット

  pause(100);                 // 0.1秒モータを停止
}

//-------------------------------------------------------------------------
//  旋回モジュール (0:R90 1:L90 2:R180 3:L180) 
//-------------------------------------------------------------------------
void com_turn( int t_mode )
{
  short T_STEP;

  com_stop();                                             // 停止
  control_mode = 0;                                       // 姿勢制御なし
  if     ( t_mode == 0 ) { T_STEP = TURN_STEP; rdir = 1; ldir = 0; } // 右９０度
  else if( t_mode == 1 ) { T_STEP = TURN_STEP; rdir = 0; ldir = 1; } // 左９０度
  else if( t_mode == 2 ) { T_STEP = TURN_STEP * 2; rdir = 1; ldir = 0; } // 右反転
  else if( t_mode == 3 ) { T_STEP = TURN_STEP * 2; rdir = 0; ldir = 1; } // 左反転

  // 加速モード
  speed = 100;        // 目標速度設定
  while( speed > speed_now );                   // 目標速度になるまで加速 ★
  // 定速モード
  speed = speed_now;  // 加速後の速度
  while( STEP < T_STEP - speed_now * 2 );       // 減速ステップ数を残して定速移動 
                                                // 全体ステップ数-減速用ステップ数
  // 減速モード
  speed = 1;          // 最低速度設定
  while( STEP < T_STEP );                       // 残りのステップ数で減速 
}

//-------------------------------------------------------------------------
//  カウントダウン 
//-------------------------------------------------------------------------
void countdown( void )
{
  beep( 0, 850 );
  beep( 1, 150 );
  beep( 0, 850 );
  
  R_SW = LED_OFF;        // 右センサOFF
  L_SW = LED_OFF;        // 左センサOFF
  F_SW = LED_OFF;        // 前センサOFF
  beep( 1, 150 );
  beep( 0, 850 );

  R_SW = LED_ON;         // 右センサON
  L_SW = LED_ON;         // 左センサON
  F_SW = LED_ON;         // 前センサON
  beep( 13, 1000 );
}

//-------------------------------------------------------------------------
//  ゴール音 
//-------------------------------------------------------------------------
void finish( void )
{
  beep( 8 , 150 );
  beep( 0 , 150 );
  beep( 8 , 150 );
  beep( 0 , 50 );
  beep( 13 , 500);
}

//-------------------------------------------------------------------------
//  壁のセンシング
//-------------------------------------------------------------------------
int get_wall_data( void )
{
  short wall;

  // センサデータを入力，閾値と比較して壁の有無を判定
  wall = 0;
  if( F_SEN > F_LIM )  wall |= 0x01; // 前壁あり
  if( R_SEN > R_LIM )  wall |= 0x02; // 右壁あり
  if( L_SEN > L_LIM )  wall |= 0x08; // 左壁あり
  // 後壁はあるわけないので見ない

  return( wall );
}

//-------------------------------------------------------------------------
// MAPデータの見方
// 探索記録 bit 7 6 5 4 = 西 南 東 北 / 値 = 1:既探索 0:未探索
// 壁情報   bit 3 2 1 0 = 西 南 東 北 / 値 = 1:壁有り 0:壁無し
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//  MAPデータ初期化
//-------------------------------------------------------------------------
void clear_map( void )
{
  int x, y;
  // 全ての区間を壁なし＆未探索に初期化
  for( y = 0 ; y < 16 ; y++ )
    for( x = 0 ; x < 16 ; x++ )
      map[ x ][ y ] = 0x00;

  // 西側の外壁（x=0，y=0～15）を上書き
  for( y = 0 ; y < 16 ; y++ )
    map[ 0 ][ y ] = 0x88;  // 西のみ既探索(8)＆西のみ壁あり(8)
  // 南側の外壁（x=0～15，y=0）を上書き
  for( x = 0 ; x < 16 ; x++ )
    map[ x ][ 0 ] = 0x44;  // 南のみ既探索(4)＆南のみ壁あり(4)
  // 東側の外壁（x=15，y=0～15）を上書き
  for( y = 0 ; y < 16 ; y++ )
    map[ 15 ][ y ] = 0x22; // 東のみ既探索(2)＆東のみ壁あり(2)
  // 北側の外壁（x=0～15，y=15）を上書き
  for( x = 0 ; x < 16 ; x++ )
    map[ x ][ 15 ] = 0x11; // 北のみ既探索(1)＆北のみ壁あり(1)

  // スタート区間（x=0，y=0）の上書き
  map[ 0 ][ 0 ] = 0xfe;  // 西南東北既探索(8+4+2+1=f)＆西南東壁あり(8+4+2=e)
  // スタート区間1つ右（x=1，y=0）の上書き
  map[ 1 ][ 0 ] = 0xcc;  // 西南既探索(8+4=c)＆西南壁あり(8+4=c)

  // 左上角（x=0，y=15）の上書き
  map[ 0 ][ 15 ] = 0x99; // 西北既探索(8+1=9)＆西北壁あり(8+1=9)
  // 右下角（x=15，y=0）の上書き
  map[ 15 ][ 0 ] = 0x66; // 南東既探索(4+2=6)＆南東壁あり(4+2=6)
  // 右上角（x=15，y=15）の上書き
  map[ 15 ][ 15 ] = 0x33;// 東北既探索(2+1=3)＆東北壁あり(2+1=3)
}

//-------------------------------------------------------------------------
//  センサ情報から探索記録＆壁情報をMAPデータに更新
//-------------------------------------------------------------------------
void make_map_data( void )
{
  uchar wall;

  // 壁情報取得
  wall = get_wall_data();
  // 方向合わせ処理のために上位4bitに下位4bitの壁情報をコピー
  wall = ( wall & 0x0f ) | ( wall << 4 );
  // マウスの進行方向にあわせて壁データを加工
  if     ( head == 1 ) wall = wall >> 3; // 北が前の情報を東が前に加工
  else if( head == 2 ) wall = wall >> 2; // 北が前の情報を南が前に加工
  else if( head == 3 ) wall = wall >> 1; // 北が前の情報を西が前に加工
  // 西南東北を探索済みにする
  wall |= 0xf0;
  // 壁情報をMAPデータに上書き
  map[ pos_x ][ pos_y ] = wall;

  // 西南東北の隣区画のMAPデータを上書き

  // 現在区画の東壁情報を1つ右区画の西壁情報として上書きする処理
  // ここだけ詳細に説明．残り3つ（下，左，上）はまとめて記述
  if( pos_x != 15 ){  // 一番東側の区画の時以外
    // 右区画の西側情報（探索記録＆壁情報）を消去
    map[ pos_x + 1 ][ pos_y ] &= 0x77;
    // 右区画の西側探索記録を既探索とする
    map[ pos_x + 1 ][ pos_y ] |= 0x80;
    // 現在区画の東側情報を西側情報に変換して右区画の西側壁情報に上書き
    map[ pos_x + 1 ][ pos_y ] |= ( map[ pos_x ][ pos_y ] << 2 ) & 0x08;
  }
  
  // 現在区画の南壁情報を1つ下区画の北壁情報として上書きする処理
  if(pos_y!=0) map[pos_x][pos_y-1]=(map[pos_x][pos_y-1]&0xee)|0x10|((wall>>2)&0x01);
  // 現在区画の西壁情報を1つ左区画の東壁情報として上書きする処理
  if(pos_x!=0) map[pos_x-1][pos_y]=(map[pos_x-1][pos_y]&0xdd)|0x20|((wall>>2)&0x02);
  // 現在区画の北壁情報を1つ上区画の南壁情報として上書きする処理
  if(pos_y!=15)map[pos_x][pos_y+1]=(map[pos_x][pos_y+1]&0xbb)|0x40|((wall<<2)&0x04);
}

//-------------------------------------------------------------------------
//  等高線（ポテンシャル場）作成
//-------------------------------------------------------------------------
void make_potential( int gx, int gy, int mode )
{
  uchar check_num, flg;
  uchar x,y;

  // ポテンシャルMAP初期化(全て最大値255にする)
  for( y = 0 ; y < 16 ; y++ )
    for( x = 0 ; x < 16 ; x++ )
      p_map[ x ][ y ] = 255;

  // ゴール座標にポテンシャル0を書き込む
  p_map[ gx ][ gy ] = 0;

  check_num = 0;
  do{
    flg = 0;  // 変更フラグ初期化
    for( y = 0 ; y < 16 ; y++ ){
      for( x = 0 ; x < 16 ; x++ ){
        if( p_map[ x ][ y ] == check_num ){  // 今回対象区画とするポテンシャル
          if( mode == S_MODE ){

            // 探索走行(Search Mode)
            // 北側の壁がない場合：北側のポテンシャルを対象区画のポテンシャルより+1
            if((( map[ x ][ y ] & 0x01 ) == 0 ) && ( y != 15 )){
              if( p_map[ x ][ y + 1 ] == 255 ){// まだポテンシャルを書いてなければ
                p_map[ x ][ y + 1 ] = check_num + 1;
                flg = 1;  // 変更したのでフラグON
              }
            }
            // 東側の壁も同様に処理
            if((( map[ x ][ y ] & 0x02 ) == 0 ) && ( x != 15 ))
              if(p_map[x+1][y]==255){p_map[x+1][y]=check_num+1;flg=1;}
            // 南側の壁も同様に処理
            if((( map[ x ][ y ] & 0x04 ) == 0 ) && ( y != 0 ))
              if(p_map[x][y-1]==255){p_map[x][y-1]=check_num+1;flg=1;}
            // 西側の壁も同様に処理
            if((( map[ x ][ y ] & 0x08 ) == 0 ) && ( x != 0 ))
              if(p_map[x-1][y]==255){p_map[x-1][y]=check_num+1;flg=1;}

          }else{

           // 二次走行(Try Mode)
           // 北側が壁なし＆既探索の場合(壁なしでも未探索はポテンシャル255のまま)
            // 北側のポテンシャルを対象区画のポテンシャルより+1
            if((( map[ x ][ y ] & 0x11 ) == 0x10 ) && ( y != 15 )){
              if( p_map[ x ][ y + 1 ] == 255 ){// まだポテンシャルを書いてなければ
                p_map[ x ][ y + 1 ] = check_num + 1;
                flg = 1;  // 変更したのでフラグON
              }
            }
            // 東側の壁も同様に処理
            if((( map[ x ][ y ] & 0x22 ) == 0x20 ) && ( x != 15 ))
              if(p_map[x+1][y]==255){p_map[x+1][y]=check_num+1;flg=1;}
            // 南側の壁も同様に処理
            if((( map[ x ][ y ] & 0x44 ) == 0x40 ) && ( y != 0 ))
              if(p_map[x][y-1]==255){p_map[x][y-1]=check_num+1;flg=1;}
            // 西側の壁も同様に処理
            if((( map[ x ][ y ] & 0x88 ) == 0x80 ) && ( x != 0 ))
              if(p_map[x-1][y]==255){p_map[x-1][y]=check_num+1;flg=1;}

          }
        }
      }
    }
    check_num++;      // 次のループのために対象ポテンシャルを+1
  }while( flg != 0 ); // 今回のループで変更箇所が無ければ作成完了
}


//-------------------------------------------------------------------------
//  探索：左手法
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//  探索：拡張左手法
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//  探索：足立法
//-------------------------------------------------------------------------
int search_adachi( void )
{
  uchar wall_data, motion;
  short val, min_val;

  // 現在区画の壁情報取得
  wall_data = map[ pos_x ][ pos_y ];

  // 計算される優先度の最大値を初期値に設定
  min_val = 1025;  // 区画ポテンシャル最大値+1 255*4+4 +1 =1025

  // 周囲４つの方向に対して優先度を計算し，
  // 一番優先度が高い（値が小さい）区画に移動する．
  // 優先度はポテンシャル，未／既探索，直進方向の順．
  // 例：ポテンシャルが0の場合＝基本優先度は0*4+4=4
  // ※未探索なら-2，直進なら-1の減算方式
  // 4:既探索＆直進以外
  // 3:既探索＆直進
  // 2:未探索＆直進以外
  // 1:未探索＆直進
  // 優先度が同じ結果の場合は北東南西の順に優先される

  // 北方向の優先度の計算
  if(( wall_data & 0x01 ) == 0 ){     // 北方向に壁が無いとき
    // 1.ポテンシャルを元に基本優先度を計算
    val = p_map[ pos_x ][ pos_y + 1 ] * 4 + 4;
    // 2.方向による優先度の計算
    // 北方向が進行方向だった場合：-1(優先度を1上げる)
    if( head == 0 )  val -= 1;
    // 3.未探索／既探索による優先度の計算
    // 未探索:-2(優先度を2上げる)，既探索:0
    if(( map[ pos_x ][ pos_y + 1 ] & 0xf0 ) != 0xf0 )  val -= 2;
    // 最小値の更新
    if( val < min_val ){
      min_val = val;
      motion = 0;  // 移動すべき方向を北に設定
    }
  }

  // 東方向の優先度の計算
  if(( wall_data & 0x02 ) == 0 ){     // 東方向に壁が無いとき
    val = p_map[ pos_x + 1 ][ pos_y ] * 4 + 4;
    if( head == 1 )  val -= 1;
    if(( map[ pos_x + 1 ][ pos_y ] & 0xf0 ) != 0xf0 )  val -= 2;
    if( val < min_val ){
      min_val = val;
      motion = 1;  // 移動すべき方向を東に設定
    }
  }

  // 南方向の優先度の計算
  if(( wall_data & 0x04 ) == 0 ){     // 南方向に壁が無いとき
    val = p_map[ pos_x ][ pos_y - 1 ] * 4 + 4;
    if( head == 2 )  val -= 1;
    if(( map[ pos_x ][ pos_y - 1 ] & 0xf0 ) != 0xf0 )  val -= 2;
    if( val < min_val ){
      min_val = val;
      motion = 2;  // 移動すべき方向を南に設定
    }
  }

  // 西方向の優先度の計算
  if(( wall_data & 0x08 ) == 0 ){     // 西方向に壁が無いとき
    val = p_map[ pos_x - 1 ][ pos_y ] * 4 + 4;
    if( head == 3 )  val -= 1;
    if(( map[ pos_x - 1 ][ pos_y ] & 0xf0 ) != 0xf0 )  val -= 2;
    if( val < min_val ){
      min_val = val;
      motion = 3;  // 移動すべき方向を西に設定
    }
  }

  // 移動すべき方向から行動を決定
  motion = ( motion - head ) & 0x03;

  return( motion );
}



#ifdef __cplusplus
void abort(void)
{

}
#endif

