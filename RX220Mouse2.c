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
// LED(1•b)“_–Å ƒƒCƒ“ƒNƒƒbƒN20MHz
// RX220—p LCD×²ÌŞ×ØƒeƒXƒg 2022/6/30
// ƒ^ƒCƒ}[Š„‚İ 2022/7/1 4 5 6
// ƒXƒCƒbƒ`‘€ì 7/6  ƒ‚[ƒhØ‘Ö 7/6 ƒoƒbƒeƒŠ[A/D 7/6  BeepŠÖ”‘Î‰ 7/6
// ƒZƒ“ƒTæ‚è‚İ 7/6 7 8
// ƒ‚[ƒ^“®ìƒeƒXƒg 7/8
// ƒ‚[ƒ^‹ì“®ƒ^ƒCƒ} 7/11 12  p¨§Œä 7/12 1&N‹æŠÔ‘Oi 7/12 13 ƒ^[ƒ“ 7/13 ’TõŠÖ” 7/13 
// ‘«—§–@À‘• À•W‚ğ“ü‚ê‚æ‚¤‚Æ‚µ‚½‚ªA¶è–@‚È‚Ç‚ÌƒR[ƒh‚à‚ ‚Á‚½‚Ì‚Å”ò‚Î‚µ‚ÄÀ‘•‚·‚é 7/13 “ñŸ‘–s 713
// ƒZƒ“ƒT’l’²® 7/13  ƒtƒ‹–À˜H‚Å’Tõ‚ÍƒS[ƒ‹‚µ‚½ 7/13
// 2022/7/14 RX220ƒ}ƒEƒX—p‚Æ‚µ‚Äƒ\[ƒXì¬ 
// 2022/7/20 ƒuƒU[•”•ª‚Ìì¬ 7/21 ƒuƒU[•”Š®¬
// 2022/7/21 I/Oİ’è‚ğ®—  7/22 ƒ‹[ƒv•”‚È‚Ç®—
// 2022/7/22 ƒRƒ“ƒpƒCƒ‹ƒIƒvƒVƒ‡ƒ“Å“K‰» ƒfƒBƒtƒHƒ‹ƒg‚Ì2‚Í‚m‚f 1,0 ‚Í‹¤‚É“®ìAÅ“K‰»‚È‚µ‚Ì0‚Ås‚¤‚±‚Æ‚É‚·‚é
// 2022/9/16 ƒ^ƒCƒ}[‚Ìİ’è’l‚ğ•ÏX
// 2022/9/21 ƒZƒ“ƒT’l‚ğC³  –Ú•W‘¬“x‚ğ‰º‚°‚é
// 2022/9/23 ‘O•ÇC³—p‚ÌŠÖ”A‘O•ÇC³ˆ—‚ğ“ü‚ê‚é
// H8‚æ‚èRX220ƒ}ƒEƒX—p‚Æ‚µ‚Äƒ\[ƒXì¬ 
// 2025/10/2 ƒ\[ƒX®— ->10/31
// 2025/11/5 ƒ~ƒX‚ÌC³Aƒpƒ‰ƒ[ƒ^ì‹@‚É‡‚í‚¹‚éBƒrƒ‹ƒhOK ƒ‚[ƒ^ON.OFF‚ª‹t‚¾‚Á‚½
// 2025/11/6 AD•ÏŠ·ƒ^ƒCƒ}[C³ƒeƒXƒg ƒZƒ“ƒT’²®
// 2025\11/7 ƒRƒƒ“ƒg®—
//#include "typedefine.h"
#include "iodefine.h"
#include "LCDrx220.h"			// LCD×²ÌŞ×Ø
#include "160926AccTable.h"
#include <math.h>
#include "RX-I2C.h"
#include "RX-I2C.c"
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
//  Œ^éŒ¾
//---------------------------------------------------------------
#define  uchar    unsigned char
#define  ushort   unsigned short
#define  vshort   volatile short
#define  vushort  volatile unsigned short
//-------------------------------------------------------------------------
//  ƒ|[ƒg’è‹`
//-------------------------------------------------------------------------
#define   CPU_LED      PORTB.PODR.BIT.B0    // CPU‘wLED Ô
#define   LED               PORT5.PODR.BIT.B4    // ƒZƒ“ƒTLEDƒXƒCƒbƒ`
#define   SW_EXEC      PORT3.PIDR.BIT.B2    // ÀsƒXƒCƒbƒ` ’†
#define   SW_UP         PORT3.PIDR.BIT.B1    // ƒ‚[ƒh‘I‘ğƒXƒCƒbƒ`+ ‰E
#define   SW_DOWN    PORT2.PIDR.BIT.B7    // ƒ‚[ƒh‘I‘ğƒXƒCƒbƒ`- ¶
#define   MOTOR_EN    PORTH.PODR.BIT.B2    // ƒ‚[ƒ^ƒhƒ‰ƒCƒoƒXƒCƒbƒ` OFF:0, ON:1  SLA7078 11/6
#define   L_MOT_MODE  PORTH.PODR.BIT.B3    // ¶ƒ‚[ƒ^‚Ì‰ñ“]•ûŒü
#define   R_MOT_MODE  PORTB.PODR.BIT.B5    // ‰Eƒ‚[ƒ^‚Ì‰ñ“]•ûŒü
#define   BUZZER_TGR   MTU0.TGRB                // üŠú(‰¹’ö)‚Ìİ’èƒŒƒWƒXƒ^ 7/20
//-------------------------------------------------------------------------
//  ƒ}ƒNƒ’è‹`
//-------------------------------------------------------------------------
// ƒXƒCƒbƒ`ŠÖ˜A
#define   SW_ON       0    // ƒXƒCƒbƒ`ON (Active Low)
#define   SW_OFF      1    // ƒXƒCƒbƒ`OFF
#define   KEY_OFF   200    // ƒXƒCƒbƒ`—pƒ`ƒƒƒ^ƒŠƒ“ƒOƒLƒƒƒ“ƒZƒ‹ŠÔ
// ƒ‚[ƒhŠÖ˜A
#define   ModeMax     14   // “®ìƒ‚[ƒh”
#define   DISP        0    // ƒ‚[ƒh•\¦
#define   EXEC        1    // ƒ‚[ƒhÀs

#define CLK400

// ƒS[ƒ‹À•WŒó•âˆê——
typedef struct {
  uchar x;
  uchar y;
  const char *label;
} goal_choice_t;

static const goal_choice_t goal_choices[] = {
  { 3, 3, "(3,3)" },
  { 7, 7, "(7,7)" },
  { 7, 8, "(7,8)" },
  { 8, 7, "(8,7)" },
  { 8, 8, "(8,8)" }
};
#define   GOAL_CHOICE_COUNT ((int)(sizeof(goal_choices) / sizeof(goal_choices[0])))

// ƒZƒ“ƒTŠÖ˜A
#define   LED_ON      1    // ƒZƒ“ƒT—pLED“_“•
#define   LED_OFF     0    // ƒZƒ“ƒT—pLEDÁ“”
// ƒ‚[ƒ^ŠÖ˜A
#define   LeftGo      1    // ¶ƒ‚[ƒ^‘Oi
#define   LeftBack    0    // ¶ƒ‚[ƒ^Œãi
#define   RightGo     0    // ‰Eƒ‚[ƒ^‘Oi
#define   RightBack   1    // ‰Eƒ‚[ƒ^Œãi
// ’TõŠÖ˜A
#define   S_MODE      0    // Search Mode : –¢’Tõ‹æŠÔ‚Í•Ç–³‚µ‚Æ‚µ‚Äˆµ‚¤
#define   T_MODE      1    // Try Mode    : –¢’Tõ‹æŠÔ‚Í•Ç—L‚è‚Æ‚µ‚Äˆµ‚¤
#define   KBAT_BACK_SPEED 80
#define   KBAT_HALF_SPEED 100
#define   KBAT_BACK_STEP  1000
#define   KBAT_HALF_STEP  600
static const short GSSPEED[] = { 300, 400, 500, 600, 700, 800, 900, 1000 };  // preset target speeds
#define   GSPEED_LEVELS        ((int)(sizeof(GSSPEED) / sizeof(GSSPEED[0])))
#define   GSPEED_DEFAULT_INDEX (GSPEED_LEVELS - 1)
// ?????x?Z???T?l???????????~Z???T?????W?X?g?^
#define   WALL_SAMPLE_MAX 256
// ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…ŠÖ˜A 1/30 31 2/1
#define CLOCK            20     // ƒNƒƒbƒNƒ\[ƒX‚Ì‘I‘ğ ‚É‡‚í‚¹‚é‚±‚Æ [MHz]
#define FDATA_A			(0x0100000)	//ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…‚Ìæ“ª
#define SDATA_BK	0	//ƒZƒ“ƒT[ƒf[ƒ^•Û‘¶—pƒuƒƒbƒN(0~1)
#define SLALOMDATA_BK 1   // ??????????????
#define MDATA_BK1	2	//ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…ƒ}ƒbƒv•Û‘¶—pƒuƒƒbƒN1(2~3)
#define MDATA_BK2	4	//ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…ƒ}ƒbƒv•Û‘¶—pƒuƒƒbƒN2(4~5)
#define GOALDATA_BK 6    // ????????????

#define SENSOR_DATA_MAGIC 0xA5A5  // sensor reference validity marker
#define SENSOR_DATA_VERSION 0x0001 // format version for sensor data
#define SLALOM_DATA_MAGIC 0x5A5A  // slalom step validity marker
#define SLALOM_DATA_VERSION 0x0003 // format version for slalom step data
#define GOAL_DATA_MAGIC 0xC33C    // goal selection validity marker
#define GOAL_DATA_VERSION 0x0001  // format version for goal selection
#define GO_STEPDATA_BK 7          // GO_STEP??????
#define GO_STEP_DATA_MAGIC 0x3CC3 // GO_STEP validity marker
#define GO_STEP_DATA_VERSION 0x0001 // format version for GO_STEP data
//---------------------------------------------------------------
//  ƒOƒ[ƒoƒ‹•Ï”’è‹`
//---------------------------------------------------------------
vushort  wait_timer = 0;   // “à•”Œv( msec ) : waitŠÖ”—pƒJƒEƒ“ƒ^
ushort   SENSOR_PT;        // Š„‚è‚İ‰ñ”ƒJƒEƒ“ƒg—pƒ|ƒCƒ“ƒ^
int      MODE = 0;         // Œ»İƒ‚[ƒhŠi”[—p
vshort   Batt;             // “d’r‚Ì“dˆ³
//ƒuƒU[ŠÖ˜A : ‹x•„,ƒh,ƒh#,ƒŒ,ƒŒ#,ƒ~,ƒtƒ@,ƒtƒ@#,ƒ\,ƒ\#,ƒ‰,ƒ‰#,ƒV,ƒh
enum beep_tone {
  BEEP_MUTE = 0,
  BEEP_C4,
  BEEP_CS4,
  BEEP_D4,
  BEEP_DS4,
  BEEP_E4,
  BEEP_F4,
  BEEP_FS4,
  BEEP_G4,
  BEEP_GS4,
  BEEP_A4,
  BEEP_AS4,
  BEEP_B4,
  BEEP_C5,
  BEEP_CS5,
  BEEP_D5,
  BEEP_DS5,
  BEEP_E5,
  BEEP_F5,
  BEEP_FS5,
  BEEP_G5,
  BEEP_GS5,
  BEEP_A5,
  BEEP_AS5,
  BEEP_B5,
  BEEP_C6,
  BEEP_CS6,
  BEEP_D6,
  BEEP_DS6,
  BEEP_E6,
  BEEP_F6,
  BEEP_FS6,
  BEEP_G6,
  BEEP_GS6,
  BEEP_A6,
  BEEP_AS6,
  BEEP_B6,
  BEEP_C7,
  BEEP_TONE_COUNT
};

// MTU0 is driven from PCLK/64 (20MHz/64 = 312.5kHz). With toggle output on TGRB,
// the count is round((312500 / (2 * target_freq_hz)) - 1). Frequencies reference:
// https://inalesson.com/frequency_list/2417/
static const unsigned short beep_data[BEEP_TONE_COUNT] = {
  0,   // mute
  596, // C4 261.626 Hz
  563, // C#4 277.183 Hz
  531, // D4 293.665 Hz
  501, // D#4 311.127 Hz
  473, // E4 329.628 Hz
  446, // F4 349.228 Hz
  421, // F#4 369.994 Hz
  398, // G4 391.995 Hz
  375, // G#4 415.305 Hz
  354, // A4 440.000 Hz
  334, // A#4 466.164 Hz
  315, // B4 493.883 Hz
  298, // C5 523.251 Hz
  281, // C#5 554.365 Hz
  265, // D5 587.330 Hz
  250, // D#5 622.254 Hz
  236, // E5 659.255 Hz
  223, // F5 698.456 Hz
  210, // F#5 739.989 Hz
  198, // G5 783.991 Hz
  187, // G#5 830.609 Hz
  177, // A5 880.000 Hz
  167, // A#5 932.328 Hz
  157, // B5 987.767 Hz
  148, // C6 1046.502 Hz
  140, // C#6 1108.731 Hz
  132, // D6 1174.659 Hz
  125, // D#6 1244.508 Hz
  118, // E6 1318.510 Hz
  111, // F6 1396.913 Hz
  105, // F#6 1479.978 Hz
  99,  // G6 1567.982 Hz
  93,  // G#6 1661.219 Hz
  88,  // A6 1760.000 Hz
  83,  // A#6 1864.655 Hz
  78,  // B6 1975.533 Hz
  74   // C7 2093.005 Hz
};

typedef struct {
  unsigned char tone;
  unsigned short duration_ms;
} melody_step_t;

static const melody_step_t ccnt_melody[] = {
  { BEEP_D4, 150 }, { BEEP_MUTE, 100 },
  { BEEP_DS4, 150 }, { BEEP_MUTE, 100 },
  { BEEP_E4, 225 }, { BEEP_MUTE, 100 },
  { BEEP_D4, 75 },  { BEEP_MUTE, 50  },
  { BEEP_D4, 150 }, { BEEP_MUTE, 100 },
  { BEEP_E4, 75 },  { BEEP_MUTE, 50  },
  { BEEP_F4, 150 }, { BEEP_MUTE, 100 },
  { BEEP_C5, 150 }, { BEEP_MUTE, 100 },
  { BEEP_D5, 150 }, { BEEP_MUTE, 100 },
  { BEEP_C5, 150 }, { BEEP_MUTE, 100 },
  { BEEP_D5, 150 }, { BEEP_MUTE, 100 },
  { BEEP_C5, 150 }, { BEEP_MUTE, 100 },
  { BEEP_B4, 75 },  { BEEP_MUTE, 50  },
  { BEEP_A4, 75 },  { BEEP_MUTE, 50  },
  { BEEP_G4, 75 },  { BEEP_MUTE, 50  },
  { BEEP_F4, 75 },  { BEEP_MUTE, 50  }
};

#define CCNT_MELODY_LENGTH ((ushort)(sizeof(ccnt_melody) / sizeof(ccnt_melody[0])))

static volatile ushort ccnt_ms_left = 0;
static volatile ushort ccnt_step_index = 0;
static volatile uchar  ccnt_playing = 0;

static inline void buzzer_set_tone(unsigned char tone)
{
  if( tone >= BEEP_TONE_COUNT || tone == BEEP_MUTE ){
    MTU.TSTR.BIT.CST0 = 0;  // stop tone (mute or invalid)
    return;
  }

  BUZZER_TGR = beep_data[ tone ];  // set frequency
  MTU.TSTR.BIT.CST0 = 1;           // start Beep timer
}

static inline void ccnt_playback_tick(void)
{
  if( ccnt_playing == 0 )
    return;

  if( ccnt_ms_left > 0 ){
    ccnt_ms_left--;
    return;
  }

  if( ccnt_step_index >= CCNT_MELODY_LENGTH ){
    buzzer_set_tone( BEEP_MUTE );
    ccnt_playing = 0;
    return;
  }

  buzzer_set_tone( ccnt_melody[ ccnt_step_index ].tone );
  ccnt_ms_left = ccnt_melody[ ccnt_step_index ].duration_ms;
  ccnt_step_index++;
}

void init_riic0(void){
	SYSTEM.PRCR.WORD = 0xA50a;		// æ¶ˆè²»é›»åŠ›ä½æ¸›æ©Ÿè?½è¨­å®šãƒ¬ã‚¸ã‚¹ã‚¿æ›¸ãè¾¼ã¿è¨±å¯
	MSTP(RIIC0)=0;
	SYSTEM.PRCR.WORD = 0xA500;		// æ¶ˆè²»é›»åŠ›ä½æ¸›æ©Ÿè?½è¨­å®šãƒ¬ã‚¸ã‚¹ã‚¿æ›¸ãè¾¼ã¿ç¦æ­¢	
	RIIC0.ICCR1.BIT.ICE	= 0;
	while( RIIC0.ICCR1.BIT.ICE != 0 );
	RIIC0.ICCR1.BIT.IICRST 	= 1;
	RIIC0.ICCR1.BIT.IICRST 	= 0;
	
#ifdef CLK100
	//100kbps 
	RIIC0.ICMR1.BIT.CKS 		= 2;	//2  CKS = 1
	RIIC0.ICBRH.BYTE		= 10;	//2  ICBRH=8
	RIIC0.ICBRL.BYTE		= 12;	//3  ICBRL=19
#endif

#ifdef CLK400
	//400kbps 	
	RIIC0.ICMR1.BIT.CKS	= 1;
	RIIC0.ICBRH.BYTE		= 9;	
	RIIC0.ICBRL.BYTE		= 9;
#endif	
	RIIC0.ICIER.BIT.ALIE	= 0;
	RIIC0.ICIER.BYTE 		= 0x00;
	IEN(RIIC0,EEI0)			= 1;
	IEN(RIIC0,RXI0)		= 1;
	IEN(RIIC0,TXI0)			= 1;
	IEN(RIIC0,TEI0)			= 1;
	IPR(RIIC0,EEI0)			= 14;
	IPR(RIIC0,RXI0)			= 14;
	IPR(RIIC0,TXI0)			= 14;
	IPR(RIIC0,TEI0)			= 14;	
	RIIC0.ICSER.BYTE = 0x00;
	RIIC0.ICMR2.BIT.TMOL=1;
	RIIC0.ICMR3.BIT.NF=2;
	RIIC0.ICMR3.BIT.ACKWP = 0;        // disable protect for ACKBT 
	PORT1.PMR.BIT.B6 = 1;
	PORT1.PMR.BIT.B7 = 1;
	RIIC0.ICCR1.BIT.ICE =1;
	RIIC0.ICFER.BIT.TMOE =1;
	RIIC0.ICFER.BIT.MALE =0;
	RIIC0.ICFER.BIT.NALE =0;
	RIIC0.ICFER.BIT.SALE =1;
	RIIC0.ICFER.BIT.NACKE =0;
	RIIC0.ICFER.BIT.NFE =1;
	RIIC0.ICFER.BIT.SCLE =1;
	
	MPC.PWPR.BIT.B0WI = 0;		//PFSWEã¸ã®æ›¸ãè¾¼ã¿è¨±å¯	
	MPC.PWPR.BIT.PFSWE = 1;		//PFCãƒ¬ã‚¸ã‚¹ã‚¿ã¸æ›¸ãè¾¼ã¿è¨±å¯
	MPC.P16PFS.BIT.PSEL = 15;	// SCL
	MPC.P17PFS.BIT.PSEL = 15;	// SDA
	MPC.PWPR.BIT.PFSWE = 0;		//PFCãƒ¬ã‚¸ã‚¹ã‚¿ã¸æ›¸ãè¾¼ã¿ç¦æ­¢	
	MPC.PWPR.BIT.B0WI = 1;		//PFSWEã¸ã®æ›¸ãè¾¼ã¿ç¦æ­¢	
}
void int_iic0_eei(void){
	if( RIIC0.ICSR2.BIT.TMOF==1 ){
		RIIC0.ICCR2.BIT.SP			= 1;	//ã‚¹ãƒˆãƒƒãƒ—ã‚³ãƒ³ãƒ?ã‚£ã‚·ãƒ§ãƒ³ã®è¦æ±‚ã‚’ã™ã‚‹
	}
	if(RIIC0.ICSR2.BIT.NACKF==1){
		RIIC0.ICCR2.BIT.SP			= 1;	//ã‚¹ãƒˆãƒƒãƒ—ã‚³ãƒ³ãƒ?ã‚£ã‚·ãƒ§ãƒ³ã®è¦æ±‚ã‚’ã™ã‚‹
	}
	if(RIIC0.ICSR2.BIT.AL==1){
		RIIC0.ICCR2.BIT.SP			= 1;	//ã‚¹ãƒˆãƒƒãƒ—ã‚³ãƒ³ãƒ?ã‚£ã‚·ãƒ§ãƒ³ã®è¦æ±‚ã‚’ã™ã‚‹
	}
	RIIC0.ICCR1.BIT.IICRST=1;
	RIIC0.ICCR1.BIT.ICE=0;
	RIIC0.ICSR2.BIT.NACKF=0;
	RIIC0.ICSR2.BIT.TMOF=0;
	RIIC0.ICSR2.BIT.AL=0;	
}
void int_iic0_rxi(void){
	static int num;
	int i;
	//RIIC0.ICMR3.BIT.RDRFS=1;
	receve_data[num++]=RIIC0.ICDRR;
	if(num>=50){
		num=0;	
	}
	if(receve_num==num){
			RIIC0.ICMR3.BIT.ACKWP=1;
			RIIC0.ICMR3.BIT.ACKBT=1;	
	}else if(receve_num<num){
			num=0;
			for(i=0;i<=receve_num;i++){
				receve_data_out[i]=receve_data[i+1];
			}
			
			for(i=0;i<sizeof(receve_data);i++){
				receve_data[i]=0;
			}
			receve_fin_flag=1;
			stop_disen_flag=0;
			receve_flag=0;
			RIIC0.ICIER.BIT.TIE 			= 0;	//ã€€é€ä¿¡ãƒ?ãƒ¼ã‚¿ã‚¨ãƒ³ãƒ—ãƒ†ã‚£å‰²è¾¼ã¿
			IEN(RIIC0,TXI0)				= 1;
			RIIC0.ICIER.BIT.TEIE 		= 1;	//ã€€é€ä¿¡çµ‚äº?å‰²è¾¼ã¿ã€€
			IEN(RIIC0,TEI0)				= 1;
			RIIC0.ICIER.BIT.RIE 			= 0;	//ã€€å‰²è¾¼ã¿
			RIIC0.ICSR2.BIT.STOP 		= 0;
			RIIC0.ICCR2.BIT.SP			= 1;	//ã‚¹ãƒˆãƒƒãƒ—ã‚³ãƒ³ãƒ?ã‚£ã‚·ãƒ§ãƒ³ã®è¦æ±‚ã‚’ã™ã‚‹
			RIIC0.ICMR3.BIT.ACKWP=1;
			RIIC0.ICMR3.BIT.ACKBT=1;	
	}else{
		RIIC0.ICMR3.BIT.ACKWP=1;
		RIIC0.ICMR3.BIT.ACKBT=0;	
	}
			
}
void int_iic0_txi(void){
	static int n=0 ;
	
	if(receve_flag==1){
		RIIC0.ICDRT	=  (send_data[0] | 0x01);//R/W#ãƒ“ãƒƒãƒˆã‚’?¼‘ã«ã—ã¦çªã£è¾¼ã‚€
		
		
	}else{
		if( n < send_data_num ){
				RIIC0.ICDRT = send_data[n++];
		}else{
				n=0;
				RIIC0.ICIER.BIT.TIE 			= 0;	//ã€€é€ä¿¡ãƒ?ãƒ¼ã‚¿ã‚¨ãƒ³ãƒ—ãƒ†ã‚£å‰²è¾¼ã¿
				IEN(RIIC0,TXI0)				= 0;
				RIIC0.ICIER.BIT.TEIE 		= 1;	//ã€€é€ä¿¡çµ‚äº?å‰²è¾¼ã¿ã€€
				IEN(RIIC0,TEI0)				= 1;	
		}
	}
}
void int_iic0_tei(void){
		RIIC0.ICSR2.BIT.AL			= 0;	//ã‚¢ãƒ¼ãƒ“ãƒˆãƒ¬ãƒ¼ã‚·ãƒ§ãƒ³ãƒ­ã‚¹ãƒˆãƒ•ãƒ©ã‚°ã‚’ã‚¯ãƒªã‚¢
		RIIC0.ICCR2.BIT.SP			= 0;	//ã‚¹ãƒˆãƒƒãƒ—ã‚³ãƒ³ãƒ?ã‚£ã‚·ãƒ§ãƒ³ã®ç™ºè¡Œã‚’è¦æ±‚ã—ãªã?
		RIIC0.ICSR2.BIT.NACKF		= 0;	//NACKãƒ•ãƒ©ã‚°ã‚’ã‚¯ãƒªã‚¢	
		RIIC0.ICSR2.BIT.STOP 		= 0;
		RIIC0.ICCR2.BIT.SP			= 1;	//ã‚¹ãƒˆãƒƒãƒ—ã‚³ãƒ³ãƒ?ã‚£ã‚·ãƒ§ãƒ³ã®è¦æ±‚ã‚’ã™ã‚‹
		RIIC0.ICIER.BIT.TEIE 		= 1;	//ã€€é€ä¿¡çµ‚äº?å‰²è¾¼ã¿ã€€
		IEN(RIIC0,TEI0)				= 1;
			
		while(RIIC0.ICSR2.BIT.STOP != 1);			
		RIIC0.ICMR2.BIT.TMWE		= 1;	//ã‚¿ã‚¤ãƒå?”åå†?éƒ¨ã‚«ã‚¦ãƒ³ã‚¿æ›¸è¾¼ã¿è¨±å¯
		RIIC0.TMOCNTL.BYTE 		= 0;	//ã‚¿ã‚¤ãƒ?ã‚¢ã‚¦ãƒ?
		RIIC0.TMOCNTU.BYTE		= 0;	//
		RIIC0.ICSR2.BIT.TMOF		= 0;	//ã‚¿ã‚¤ãƒ?ã‚¢ã‚¦ãƒˆæ¤œå?ºãƒ•ãƒ©ã‚°ã‚¯ãƒªã‚¢
		RIIC0.ICSR2.BIT.AL			= 0;	//
		RIIC0.ICCR2.BIT.SP			= 0;	//
		RIIC0.ICSR2.BIT.NACKF		= 0;	//
		RIIC0.ICSR2.BIT.STOP		= 0;	//
		RIIC0.ICIER.BIT.TIE 			= 0;	//ã€€é€ä¿¡ãƒ?ãƒ¼ã‚¿ã‚¨ãƒ³ãƒ—ãƒ†ã‚£å‰²è¾¼ã¿
		RIIC0.ICIER.BIT.SPIE 		= 1;	//ã€€é€ä¿¡ãƒ?ãƒ¼ã‚¿ã‚¨ãƒ³ãƒ—ãƒ†ã‚£å‰²è¾¼ã¿
		IEN(RIIC0,TXI0)				= 0;
		RIIC0.ICIER.BIT.TEIE 		= 0;	//ã€€é€ä¿¡çµ‚äº?å‰²è¾¼ã¿ã€€
		IEN(RIIC0,TEI0)				= 0;
		RIIC0.ICIER.BIT.SPIE 		= 0;	//ã€€é€ä¿¡ãƒ?ãƒ¼ã‚¿ã‚¨ãƒ³ãƒ—ãƒ†ã‚£å‰²è¾¼ã¿
		if(stop_disen_flag==1){
			RIIC0.ICCR1.BIT.IICRST=1;
			RIIC0.ICCR1.BIT.ICE=1;
			init_riic0();			
			RIIC0.ICIER.BIT.TIE 			= 1;	//ã€€é€ä¿¡ãƒ?ãƒ¼ã‚¿ã‚¨ãƒ³ãƒ—ãƒ†ã‚£å‰²è¾¼ã¿
			RIIC0.ICIER.BIT.TEIE 		= 0;	//ã€€é€ä¿¡çµ‚äº?å‰²è¾¼ã¿ã€€
			IEN(RIIC0,TXI0)				= 1;
			IEN(RIIC0,TEI0)				= 0;
			IEN(RIIC0,RXI0)			= 1;
			RIIC0.ICIER.BIT.RIE 			= 1;	//ã€€å‰²è¾¼ã¿
			RIIC0.ICCR2.BIT.ST = 1;
			receve_flag=1;	
		}
}
int iic0_send(char* string , int data_num,int address){
	int i,r_data;
		 
	if( RIIC0.ICSR2.BIT.TEND==1 || RIIC0.ICCR2.BIT.BBSY==1){
		r_data=-1;
	}else{
		RIIC0.ICCR1.BIT.IICRST=1;
		RIIC0.ICCR1.BIT.ICE=0;
		init_riic0();
		for(i=0;i<data_num;i++){
			send_data[i+1]= *(string + i);
		}
		receve_flag=0;
		stop_disen_flag=0;
		send_data_num	 			= data_num;	
		RIIC0.ICMR2.BIT.TMWE		= 1;
		RIIC0.TMOCNTL.BYTE		= 0x0f;
		RIIC0.TMOCNTU.BYTE		= 0x00;
		RIIC0.ICMR2.BIT.TMWE		= 0;
		RIIC0.ICIER.BIT.TMOIE 		= 1;	//ã‚¿ã‚¤ãƒ?ã‚¢ã‚¦ãƒˆå‰²è¾¼ã¿
		RIIC0.ICIER.BIT.NAKIE		= 1;
		RIIC0.ICIER.BIT.TIE 			= 1;	//ã€€é€ä¿¡ãƒ?ãƒ¼ã‚¿ã‚¨ãƒ³ãƒ—ãƒ†ã‚£å‰²è¾¼ã¿
		RIIC0.ICIER.BIT.TEIE 		= 0;	//ã€€é€ä¿¡çµ‚äº?å‰²è¾¼ã¿ã€€
		IEN(RIIC0,TXI0)				= 1;
		IEN(RIIC0,TEI0)				= 0;
		RIIC0.ICCR2.BIT.ST = 1;	
		send_data[0]				= (address<<1);
	}
	return r_data;
}
char* iic0_gets(){ 
	 receve_fin_flag=0;
	return receve_data_out;
}

int iic0_reqest_send( char* data , int r_num,int addr){
	int out=1;
	int i;
	receve_fin_flag=0;
		
	if( RIIC0.ICSR2.BIT.TEND==1 || RIIC0.ICCR2.BIT.BBSY==1){
		out=-1;
	}else{
		receve_flag=0;
		stop_disen_flag=1;
		///// å†?éƒ¨ãƒªã‚»ãƒ?ãƒ?  ///
		RIIC0.ICCR1.BIT.ICE=0;
		RIIC0.ICCR1.BIT.IICRST=1;
		RIIC0.ICCR1.BIT.ICE=0;
		init_riic0();
		RIIC0.ICSR2.BIT.NACKF=0;
		RIIC0.ICSR2.BIT.TMOF=0;
		RIIC0.ICSR2.BIT.AL=0;	
		///////////////////
		for(i=0;i<sizeof(send_data);i++ ){
			send_data[i]=0x00;
		}
		for(i=0;i<2;i++){
			send_data[i+1]= *(data + i);
		}
		send_data_num				=2;	//é€ä¿¡ãƒ?ãƒ¼ã‚¿ã¯1ãƒã‚¤ãƒ?	
		send_data[send_data_num]	=  ((addr<<1) | 0x01);//R/W#ãƒ“ãƒƒãƒˆã‚’?¼‘ã«ã—ã¦çªã£è¾¼ã‚€
		for(i=3;i<9;i++){
			send_data[i]= 0x00;
		}
		receve_num=r_num;
		RIIC0.ICMR2.BIT.TMWE		= 1;
		RIIC0.TMOCNTL.BYTE		= 0x0f;
		RIIC0.TMOCNTU.BYTE		= 0x00;
		RIIC0.ICMR2.BIT.TMWE		= 0;
		
		RIIC0.ICIER.BIT.STIE			= 0;
		RIIC0.ICIER.BIT.ALIE 		= 1;	
		RIIC0.ICIER.BIT.TMOIE 		=1 ;	//ã‚¿ã‚¤ãƒ?ã‚¢ã‚¦ãƒˆå‰²è¾¼ã¿
		RIIC0.ICIER.BIT.NAKIE		= 1;
		RIIC0.ICIER.BIT.TIE 			= 1;	//ã€€é€ä¿¡ãƒ?ãƒ¼ã‚¿ã‚¨ãƒ³ãƒ—ãƒ†ã‚£å‰²è¾¼ã¿
		IEN(RIIC0,TXI0)				= 1;
		RIIC0.ICIER.BIT.TEIE 		= 0;	//ã€€é€ä¿¡çµ‚äº?å‰²è¾¼ã¿ã€€
		IEN(RIIC0,TEI0)				= 0;
		RIIC0.ICCR2.BIT.ST = 1;	
		receve_flag=0;
		RIIC0.ICDRT=send_data[0]				= (addr<<1);
	} 
	return out;
}

int iic0_set_addr(int addr, int num){
	int out=1;
	switch(num){
		case 0:
			RIIC0.SARL0.BIT.SVA = addr;
			break;
		case 1:
			RIIC0.SARL1.BIT.SVA = addr;
			break;
		case 2:
			RIIC0.SARL2.BIT.SVA = addr;
			break;
		default:
			out = -1;
			break;
	}
	return out;
}
int  iic0_receve(char* p_data,int n){ 
	int i,out;
	if(receve_fin_flag==1){
		receve_fin_flag=0;
		for(i=0; i<=n ;i++){
			*(p_data+i) = receve_data_out[i] ;	
		}
		for(i=0;i<sizeof(receve_data_out);i++){
			receve_data_out[i]=0;
		}
		out=1;
	}else {
		out=-1;	
	}
	return out;
}




// ƒZƒ“ƒT‚Ì–‘O’lŠi”[—p
vushort  R_PRE;           // ‰EƒZƒ“ƒT‚Ì’l
vushort  L_PRE;           // ¶ƒZƒ“ƒT‚Ì’l
vushort  F_PRE;           // ‘OƒZƒ“ƒT‚Ì’l
// ƒZƒ“ƒT‚ÌŒ»İ’lŠi”[—p
vushort  R_SEN;           // ‰EƒZƒ“ƒT‚Ì’l
vushort  L_SEN;           // ¶ƒZƒ“ƒT‚Ì’l
vushort  F_SEN;           // ‘OƒZƒ“ƒT‚Ì’l
// ƒZƒ“ƒT‚ÌON/OFF—p
short    R_SW;            // ‰EƒZƒ“ƒT‚ÌƒXƒCƒbƒ`
short    L_SW;            // ¶ƒZƒ“ƒT‚ÌƒXƒCƒbƒ`
short    F_SW;            // ‘OƒZƒ“ƒT‚ÌƒXƒCƒbƒ`
// ƒZƒ“ƒT‚Ì‚µ‚«‚¢’l
short    R_REF;            // ‰EƒZƒ“ƒT‚µ‚«‚¢’l
short    L_REF;            // ¶ƒZƒ“ƒT‚µ‚«‚¢’l
short    F_REF;            // ‘OƒZƒ“ƒT‚µ‚«‚¢’l  ‘O•ÇˆÊ’u‡‚í‚¹‚È‚µ
// •Ç‚Ì—L–³”»’è—p‚µ‚«‚¢’l
short    R_LIM;            // ‰E•Ç—L–³‚µ‚«‚¢’l
short    L_LIM;            // ¶•Ç—L–³‚µ‚«‚¢’l
short    F_LIM;            // ‘O•Ç—L–³‚µ‚«‚¢’l
short    F_LIM2;           // 2ƒ}ƒXæ‘O•Ç—L–³‚µ‚«‚¢’l
// ƒ‚[ƒ^ŠÖ˜A
ushort   timerL;           // ¶ƒ^ƒCƒ}[İ’è’l
ushort   timerR;           // ‰Eƒ^ƒCƒ}[İ’è’l
short    ldir;             // ¶ƒ‚[ƒ^‰ñ“]•ûŒü
short    rdir;             // ‰Eƒ‚[ƒ^‰ñ“]•ûŒü
short    speed;            // –Ú•W‘¬“x
short    speed_now;        // Œ»İ‘¬“x
short    MotorTimer;       // ƒ‚[ƒ^“dŒ¹ƒRƒ“ƒgƒ[ƒ‹ƒ^ƒCƒ}[
short    control_mode;     // p¨§Œäƒ‚[ƒh  0:‚È‚µ  1:‚ ‚è
	//ƒXƒeƒbƒv”(Š„‚è‚İ“à‚ÅƒJƒEƒ“ƒgƒAƒbƒv) 
volatile unsigned int step_r;		//‰Eƒ‚[ƒ^—p
volatile unsigned int step_l;			//¶ƒ‚[ƒ^—p
short stepf_r = 1;
short stepf_l = 1;
// ‘–sŠÖ˜A
short    STEP;             // ƒ‚[ƒ^‚ÌƒXƒeƒbƒv”
short    GO_STEP;          // 1‹æŠÔ‚ÌƒXƒeƒbƒv”
short    TURN_STEP;        // ’´Mù‰ñƒXƒeƒbƒv”
short    SLALOM_STEP_FORWARD;   // ƒXƒ‰ƒ[ƒ€ù‰ñƒXƒeƒbƒv”i“à‘¤j
short    SLALOM_STEP_OUT;  // ƒXƒ‰ƒ[ƒ€ù‰ñƒXƒeƒbƒv”iŠO‘¤j
short    SLALOM_INNER_SPEED;  // ?????????
short    BACK_STEP;        // 1‹æŠÔ‚ÌŒã‘ŞƒXƒeƒbƒv”
short    HALF_STEP;        // ”¼‹æŠÔ‚Ì‘OiƒXƒeƒbƒv”
uchar    gspeed_index;      // selected preset speed index
short GSPEEDvar ;		// –Ú•W‘¬“x  -----> ‚±‚ê‚ÍRX—p‚Æ‚µ‚Äc‚·
static short slalom_step_forward_table[ GSPEED_LEVELS ];
static short slalom_step_out_table[ GSPEED_LEVELS ];
static short slalom_inner_speed_table[ GSPEED_LEVELS ];
// ’TõŠÖ˜A
uchar    head;             // ƒ}ƒEƒX‚Ìis•ûŒü 0:–k 1:“Œ 2:“ì 3:¼
uchar    head_change;      // is•ûŒüXV—p•Ï” 0:‘O 1:‰E 2:Œã 3:¶
uchar    pos_x;            // ƒ}ƒEƒX‚ÌŒ»İÀ•W x
uchar    pos_y;            // ƒ}ƒEƒX‚ÌŒ»İÀ•W y
uchar    map[16][16];      // MAPƒf[ƒ^
uchar    p_map[16][16];    // ?|?e???V????MAP?f?[?^
int      goal_choice_index = GOAL_CHOICE_COUNT - 1;  // default goal = (8,8)
uchar    goal_x;           // current goal x coordinate
uchar    goal_y;           // current goal y coordinate
// •ÇƒTƒ“ƒvƒ‹ƒf[ƒ^
short    wall_sample_left[ WALL_SAMPLE_MAX ];
short    wall_sample_right[ WALL_SAMPLE_MAX ];
ushort   wall_sample_count;    // ƒ|ƒeƒ“ƒVƒƒƒ‹MAPƒf[ƒ^
typedef struct {
  char label;
  short *value;
  int digits;
} center_ref_t;

static const center_ref_t center_refs[] = {
  { 'L', &L_REF, 3 },
  { 'R', &R_REF, 3 },
  { 'F', &F_REF, 4 }
};

#define CENTER_REF_COUNT ((int)(sizeof(center_refs) / sizeof(center_refs[0])))
#define CENTER_REF_MIN   0
#define CENTER_REF_MAX   4095

//---------------------------------------------------------------
//  ŠÖ”ƒvƒƒgƒ^ƒCƒvéŒ¾
//---------------------------------------------------------------
void IO_init( void );
void load_param( void );
void pause( int x );
void timerc_200us( void );	//RX
void int_mot_r(void);		//RX
void int_mot_l(void); 		//RX
void WaitKeyOff( void );
void beep(unsigned char tone,int value);
void ccnt( int x );
void change_mode( int x );
void exec_mode( void );
void modeB1( int x );
void mode0( int x );
void mode1( int x );
void mode2( int x );
void mode3( int x );
void mode4( int x );
void mode5( int x );
void mode6( int x );
void mode7( int x );
void mode8( int x );
void mode9( int x );
void mode10( int x );
void mode11( int x );
void mode12( int x );
void mode13( int x );
void mouse_search( int goal_x, int goal_y, int speed, int mode );
void slalom_search( int goal_x, int goal_y, int speed, int mode );
void com_go( int n );
void com_stop( void );
void com_turn( int t_mode );
void com_slalom_turn( int t_mode );
void com_back( int n );
void com_go_half( int n );
void kbat_r( void );
void kbat_lf_turn( void );
void goal_kbat_turn( void );
void countdown( void );
void finish( void );
static void start_back_wall_contact( void );
int get_wall_data( void );
void clear_map( void );
void make_map_data( void );
void make_potential( int gx, int gy, int mode );
int search_left_hand( void );
int search_adachi( void );
void map_writeDF(short);	// MAPƒf[ƒ^‚ğDataFlash‚Ö‘‚İ   
void map_DFread(short);	// MAPƒf[ƒ^‚ğDataFlash‚©‚ç“Ço‚µ   
void sensor_ref_writeDF(void);	// store sensor reference data in DataFlash
void sensor_ref_readDF(void);	// load sensor references from DataFlash
void slalom_step_writeDF(void);	// store slalom step data in DataFlash
void slalom_step_readDF(void);	// load slalom step data from DataFlash
void goal_choice_writeDF(void);	// store goal selection in DataFlash
void goal_choice_readDF(void);	// load goal selection from DataFlash
void go_step_writeDF(void);	// store GO_STEP in DataFlash
void go_step_readDF(void);	// load GO_STEP from DataFlash
void fcu_reset(void);		// FCU‚ğƒŠƒZƒbƒg 
void fcu_tope(void) ;		//  FCU‚ğP/Eƒ‚[ƒh‚É‚·‚é  
void fcu_toread(void);		//  FCU‚ğ“Ç‚İ‚İƒ‚[ƒh‚É‚·‚é  
void error_check(void);	//  ƒGƒ‰[‚ğŠm”F‚µAƒGƒ‰[‚ª‚ ‚ê‚ÎC³‚·‚é  
void clear_flash(unsigned short);	//  ƒuƒƒbƒNÁ‹  
void wait_frdy(int);		//  FCUˆ—‘Ò‚¿  
void DFlash_init(void);		//  ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…‰Šú‰» (ü•ÓƒNƒƒbƒN‚ğFCU‚É’Ê’m‚·‚éŠÖ”)   
void DFlash_bread(unsigned short ,unsigned short *);	// DataFlashƒƒ‚ƒŠ1ƒuƒƒbƒN(128byte)“Ço‚µ  
void DFlash_bprog(unsigned short ,unsigned short *);    // DataFlash??????1?u???b?N(128byte)??????  
void reset_wall_samples( void );
void log_wall_samples( void );
void update_wall_ref_from_log( void );
static void set_slalom_steps_for_speed( int index );
static void store_slalom_steps_for_speed( int index );
static void set_goal_choice_index( int index )
{
  if( index < 0 )
    index = GOAL_CHOICE_COUNT - 1;
  else if( index >= GOAL_CHOICE_COUNT )
    index = 0;
  goal_choice_index = index;
  goal_x = goal_choices[ index ].x;
  goal_y = goal_choices[ index ].y;
}

static void advance_goal_choice( int delta )
{
  set_goal_choice_index( goal_choice_index + delta );
}
//---------------------------------------------------------------
//  ƒƒCƒ“ƒvƒƒOƒ‰ƒ€
//---------------------------------------------------------------
void main(void)
{
  IO_init();    // IO‚Ì‰Šú‰»
  LCD_init();   // LCD‚Ì‰Šú‰»
  CPU_LED = 1;  // CPU‘wLED‚ğÁ“” Ô
  LED = LED_OFF;                        // LED‚ğÁ“”
  MOTOR_EN =0;  // ƒ‚[ƒ^OFF
  // ‹N“®‰¹
  beep( BEEP_C5, 150 );
  beep( BEEP_G5, 150 );
  beep( BEEP_C5, 150 );
  beep( BEEP_G5, 150 );
  // ƒ^ƒCƒgƒ‹•\¦
  LCD_print( 0, "LE-S200P" );
  // “dˆ³•\¦
  LCD_print( 8, "   .  v " );
  LCD_dec_out( 9, Batt/100, 1);    // \‚ÌˆÊ‚ğ•\¦
  Batt %= 100;                     // \‚ÌˆÊ‚ğíœ
  LCD_dec_out(10, Batt/10 , 1);    // ˆê‚ÌˆÊ‚ğ•\¦
  Batt %= 10;                      // ˆê‚ÌˆÊ‚ğíœ
  LCD_dec_out(12, Batt    , 1);    // c‚Á‚½¬”’l‚ğ•\¦
  pause( 2000 );
  clear_map();                     // MAPƒf[ƒ^‰Šú‰»
  load_param();                    // Šeíƒpƒ‰ƒ[ƒ^‚ğ“Ç‚İ‚İ
  set_goal_choice_index( goal_choice_index );  // initialize goal selection
  change_mode( 0 );                // ‚Ü‚¸‰Šú‰æ–Ê‚É‚·‚é = Mode0
  // ƒƒCƒ“ƒ‹[ƒv
  while( 1 ){
    if( SW_UP == SW_ON ){          // ãSW‚ª‰Ÿ‚³‚ê‚Ä‚¢‚éê‡
      WaitKeyOff();                // ƒ`ƒƒƒ^ƒŠƒ“ƒO–h~ˆ—
      change_mode(+1);             // ƒ‚[ƒh+1
    }else if( SW_DOWN == SW_ON ){  // ‰ºSW‚ª‰Ÿ‚³‚ê‚Ä‚¢‚éê‡
      WaitKeyOff();                // ƒ`ƒƒƒ^ƒŠƒ“ƒO–h~ˆ—
      change_mode(-1);             // ƒ‚[ƒh-1
    }else if( SW_EXEC == SW_ON ){  // ÀsSW‚ª‰Ÿ‚³‚ê‚Ä‚¢‚éê‡
      beep( BEEP_D5, 150 );              // Às‰¹ : ƒh
      WaitKeyOff();                // ƒ`ƒƒƒ^ƒŠƒ“ƒO–h~ˆ—
      exec_mode();                 // ƒ‚[ƒhÀs
      MODE = 0;
      change_mode( 0 );            // ÀsŒã‚Í‰Šú‰æ–Ê‚É–ß‚·
    }
    // ƒ‚[ƒh‚ª0‚È‚çƒZƒ“ƒTƒf[ƒ^‚ğLCD•\¦
    if( MODE == 0 )
    {
      LCD_dec_out(  3, F_SEN, 4 ); // ‘OƒZƒ“ƒT’l‚ğLCDã’†‰›‚É•\¦
      LCD_dec_out(  9, L_SEN, 3 ); // ¶ƒZƒ“ƒT’l‚ğLCD¶‰º‚É•\¦
      LCD_dec_out( 13, R_SEN, 3 ); // ‰EƒZƒ“ƒT’l‚ğLCD‰E‰º‚É•\¦
      
    }
  }
}
//---------------------------------------------------------------
//  RX220‰Šú‰» (‚±‚±‚ÍŒã‚Å®—7/14)
//---------------------------------------------------------------
void IO_init( void )
{
  // ===== ƒNƒƒbƒNİ’è =====           
    SYSTEM.PRCR.WORD = 0xa50b;		// ƒNƒƒbƒNƒ\[ƒX‘I‘ğ‚Ì•ÛŒì‰ğœ
    
    SYSTEM.SCKCR.BIT.PCKB = 0x00;	// PCLKB 1•ªü  7/6
    SYSTEM.SCKCR.BIT.ICK = 0x00;		// ICLK 1•ªü
    // ƒNƒƒbƒNƒ\[ƒX‚Ì‘I‘ğ
    SYSTEM.SCKCR3.WORD = 0x0200;	//‘åŒ³‚ÌƒNƒƒbƒN‚ğƒƒCƒ“ƒNƒƒbƒN(20MHz)‚ğg—p
    //ƒNƒƒbƒN‚ÌŒ³ğ‚Ìİ’è
    SYSTEM.MOSCCR.BYTE = 0;		// ƒƒCƒ“ƒNƒƒbƒN”­UŠí “®ì:0 ’â~:1
    SYSTEM.SOSCCR.BYTE = 1;		// ƒTƒuƒNƒƒbƒN”­UŠí “®ì:0 ’â~:1
  // ===== I/O ƒ|[ƒg‚Ì‰Šú‰» =====           ƒsƒ“”Ô†  7654 3210
//    -------İ’è‚Ü‚Æ‚ß‚½Œ`‚É----- 7/21
    PORT0.PODR.BYTE=0x00;
    PORT0.PDR.BYTE=0x28;		// 03,05‚ğo—Íİ’è 0010 1000
    PORT1.PDR.BYTE=0x30;		// 14,15‚ğo—Íİ’è 0011 0000
    PORT5.PDR.BIT.B4=1;		// ƒ|[ƒg54 o—Íİ’è
    PORTA.PODR.BYTE=0x00;
    PORTA.PDR.BYTE=0x5b;	// ƒ|[ƒgAo—Íİ’è 0101 1011 ‘¶İƒsƒ“:0,1,3,4,6 
    PORTB.PODR.BYTE=0x00;
    PORTB.PDR.BYTE=0xeb;	// ƒ|[ƒgBo—Íİ’è 1110 1011 ‘¶İƒsƒ“:0,1,3,5,6,7
    PORTC.PODR.BYTE=0x00;
    PORTH.PODR.BYTE=0x00;
    PORTH.PDR.BYTE=0x0f;		// ƒ|[ƒgHo—Íİ’è 0000 1111 ‘¶İƒsƒ“:0,1,2,3
    PORT3.PDR.BIT.B1=0;		// P31 “ü—Íİ’è 
    PORT3.PDR.BIT.B2=0;		// P32 “ü—Íİ’è 
    PORT2.PDR.BIT.B7=0;		// P27 “ü—Íİ’è 
    PORT3.PCR.BIT.B1=1;		// P31 ƒvƒ‹ƒAƒbƒvİ’è 
    PORT3.PCR.BIT.B2=1;		// P32 ƒvƒ‹ƒAƒbƒvİ’è 
    PORT2.PCR.BIT.B7=1;		// P27 ƒvƒ‹ƒAƒbƒvİ’è 
  // ===== ƒoƒbƒeƒŠ[“dˆ³Œv‘ª =====
  // ===== A/D İ’è =====
  SYSTEM.PRCR.WORD = 0xA502;
  MSTP(S12AD) = 0;				//12bitAD•ÏŠ·ƒXƒ^ƒ“ƒoƒC‰ğœ
  SYSTEM.PRCR.WORD = 0xA500;	
  S12AD.ADCER.BIT.ADRFMT = 0;	//‰E‚Ã‚ß
  S12AD.ADCSR.BIT.ADCS = 0;		//ƒVƒ“ƒOƒ‹ƒXƒLƒƒƒ“ƒ‚[ƒh
  S12AD.ADCSR.BIT.ADST = 0;	//AD•ÏŠ·’â~
  
	// ƒoƒbƒeƒŠ[“dˆ³“Çæ
  S12AD.ADANSA.WORD = 0x0200;		//AN009
  S12AD.ADCSR.BIT.ADST=1;			//AD•ÏŠ·ŠJn
  while(S12AD.ADCSR.BIT.ADST == 1);	//AD•ÏŠ·I—¹‚Ü‚Å‘Ò‚Â
  Batt = S12AD.ADDR9 >> 3;             // ‘ª’èƒf[ƒ^AN9‚ğæ‚è‚Ş 10bit‚É‚µ‚Ä H8‚àÅ‰ºˆÊbit‚ğØ‚Á‚Ä‚¢‚é‚æ‚¤‚¾
  
  
  // ===== ƒ^ƒCƒ}[‚Ì‰Šú‰» =====   7/5
  // CMT ƒ^ƒCƒ}Š„‚İİ’è
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP( CMT0 ) = 0;					// Wakeup CMT0,CMT1
   	SYSTEM.PRCR.WORD = 0xA500;	
	//CMT0‚Í§ŒäŠ„‚è‚İ—pƒ^ƒCƒ}‚Æ‚µ‚Äg—p[timerc_200us]
	CMT0.CMCR.BIT.CKS=0;				// 20MHz/8 2.5MHz PCLK/8:0 /32:1 /128:2 /512:3
	CMT0.CMCR.BIT.CMIE=1;				//ƒRƒ“ƒyƒAƒ}ƒbƒ`Š„‚İ‹–‰Â
	CMT0.CMCNT=0;			//ƒJƒEƒ“ƒ^[‚ÌƒNƒŠƒA  –³‚­‚Ä‚à“®ì‚·‚é‰e‹¿‚ÍÅ‰‚Ì‚P‰ñ‚¾‚©‚ç
	CMT0.CMCOR=500-1;		//2.5MHz/500 =5kHz:200us
	IEN( CMT0, CMI0 ) = 1;				// CMI0 Enable Š„‚İ—v‹‹–‰Â
	IPR( CMT0, CMI0 ) = 15;				// CMI0 Interrupt Level is 1 Š„‚İ—Dæ“x Pico:15
	IR(CMT0,CMI0)=0;				//Š„‚è‚İƒXƒe[ƒ^ƒtƒ‰ƒO‚ğƒNƒŠƒA
	CMT.CMSTR0.BIT.STR0 = 1;			// Start CMT0
  // MTU ƒ^ƒCƒ}Š„‚İİ’è      
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(MTU) = 0;			//MTUƒ‚ƒWƒ…[ƒ‹ON
	SYSTEM.PRCR.WORD = 0xA500;	
	
	MTU.TSTR.BYTE=0;		//ƒ^ƒCƒ}“®ìƒXƒgƒbƒv
	// I/O‚Ìİ’è
	MPC.PWPR.BIT.B0WI=0;		//PFSWEƒrƒbƒg‚Ö‚Ì‘‚«‚İ‚ğ‹–‰Â
	MPC.PWPR.BIT.PFSWE=1;		//PFSƒŒƒWƒXƒ^‚Ö‚Ì‘‚«‚İ‚ğ‹–‰Â
	MPC.P14PFS.BIT.PSEL = 1;	//P14(L_MOTOR_STEP)‚ğMTIOC0A‚Éİ’è
	MPC.PB3PFS.BIT.PSEL = 2;	//PB3(R_MOTOR_STEP)‚ğMTIOC0C‚Éİ’è
	MPC.P15PFS.BIT.PSEL = 1;	//P15‚ğMTIOC0B‚Æ‚µ‚Äg—p‚·‚é 7/20
	PORT1.PMR.BIT.B4 = 1;		//ü•Óƒ‚ƒWƒ…[ƒ‹‚Æ‚µ‚Äg—p
	PORTB.PMR.BIT.B3 = 1;		//ü•Óƒ‚ƒWƒ…[ƒ‹‚Æ‚µ‚Äg—p
	PORT1.PMR.BIT.B5 = 1;		//ü•Óƒ‚ƒWƒ…[ƒ‹‚Æ‚µ‚Äg—po—Í 7/20
	//ƒXƒs[ƒJ[—pMTU MTIOC0B(P15) 7/20 21
	MSTP_MTU0 = 0;					//MTU0ƒXƒ^ƒ“ƒoƒC‰ğœ
	MTU0.TCR.BIT.CCLR=2;	//PWM TGRB‚ÌƒRƒ“ƒyƒAƒ}ƒbƒ`‚ÅTCNTƒNƒŠƒA 
	MTU0.TCR.BIT.TPSC=3;	//PCLK/64 20/64=0.3125MHz=312.5kHz
	MTU0.TMDR.BIT.MD = 0;		// ƒm[ƒ}ƒ‹ƒ‚[ƒh‚Éİ’è
	MTU0.TIORH.BIT.IOB = 3;		//‰Šúo—ÍLƒRƒ“ƒyƒAƒ}ƒbƒ`‚ÅƒgƒOƒ‹
	MTU0.TGRB = 0;			// üŠú(‰¹’ö)‚Ìİ’èƒŒƒWƒXƒ^(BUZZER_TGR) : 0(Å‰‚Í‹x•„)
	//‰Eƒ‚[ƒ^—pMTUİ’è MTICA4A(PB3)
	MTU.TOER.BIT.OE4A = 1;		//MTU’[qo—Í‹–‰Â MTU4‚Å‚Í•K—v
	MTU4.TCR.BIT.TPSC=2;	//PCLK/16 20/16=1.25MHz CMT0‚Ì20/8‚Ì”¼•ª 0.8ƒÊS
	MTU4.TCR.BIT.CCLR=1;	//PWM TGRA‚ÌƒRƒ“ƒyƒAƒ}ƒbƒ`‚ÅTCNTƒNƒŠƒA
	MTU4.TMDR.BIT.MD=2;		//PWM1
	MTU4.TIORH.BIT.IOA=1;	//‰Šúo—ÍLƒ“ƒyƒAƒ}ƒbƒ`Lo—Í
	MTU4.TIORH.BIT.IOB=2;	//‰Šúo—ÍLƒRƒ“ƒyƒAƒ}ƒbƒ`Ho—Í
	MTU4.TGRA = 2500;		// 1/(0.8e-6x2500) = 500Hz
	MTU4.TGRB = 50;
	MTU4.TGRC = 2500;
	MTU4.TMDR.BIT.BFA = 1;	//TGRA,TGRC‚ğƒoƒbƒtƒ@[ƒ‚[ƒh‚Éİ’è
	MTU4.TIER.BIT.TGIEB = 1;//GRBƒRƒ“ƒyƒAƒ}ƒbƒ`‚Å‚ÌŠ„‚è‚İ‹–‰Â
	IEN(MTU4,TGIB4) = 1;	//Š„‚è‚İ—v‹‚ğ‹–‰Â 
	IPR(MTU4,TGIB4) = 12;	//Š„‚è‚İ—Dæ“x‚ğŸ“_‚Éİ’è
	IR(MTU4,TGIB4)=0;		//Š„‚è‚İƒXƒe[ƒ^ƒtƒ‰ƒO‚ğƒNƒŠƒA
	//¶ƒ‚[ƒ^—pMTUİ’è MTIOCA3A(P14)
	MTU3.TCR.BIT.TPSC=2;	//PCLK/16 20/16=1.25MHz CMT0‚Ì20/8‚Ì”¼•ª 0.8ƒÊS
	MTU3.TCR.BIT.CCLR=1;	//PWM TGRA‚ÌƒRƒ“ƒyƒAƒ}ƒbƒ`‚ÅTCNTƒNƒŠƒA
	MTU3.TMDR.BIT.MD=2;		//PWM1
	MTU3.TIORH.BIT.IOA=1;	//‰Šúo—ÍLƒRƒ“ƒyƒAƒ}ƒbƒ`Lo—Í
	MTU3.TIORH.BIT.IOB=2;	//‰Šúo—ÍLƒRƒ“ƒyƒAƒ}ƒbƒ`Ho—Í
//	MTU3.TGRA = 5000;		// 1/(0.8e-6x5000) = 250Hz
//	MTU3.TGRA = 1250;		// 1/(0.8e-6x1250) = 1kHz
	MTU3.TGRA = 2500;		// 1/(0.8e-6x2500) = 500Hz
	MTU3.TGRB = 50;
	MTU3.TGRC = 2500;
	MTU3.TMDR.BIT.BFA = 1;	//TGRA,TGRC‚ğƒoƒbƒtƒ@[ƒ‚[ƒh‚Éİ’è
	MTU3.TIER.BIT.TGIEB = 1;//GRBƒRƒ“ƒyƒAƒ}ƒbƒ`‚Å‚ÌŠ„‚è‚İ‹–‰Â
	IEN(MTU3,TGIB3) = 1;	//Š„‚è‚İ—v‹‚ğ‹–‰Â 
	IPR(MTU3,TGIB3) = 13;	//Š„‚è‚İ—Dæ“x‚ğŸ“_‚Éİ’è
	IR(MTU3,TGIB3)=0;		//Š„‚è‚İƒXƒe[ƒ^ƒtƒ‰ƒO‚ğƒNƒŠƒA
	MTU.TSTR.BIT.CST0 = 0;	//ƒ^ƒCƒ}ƒXƒgƒbƒv SP 7/20
	MTU.TSTR.BIT.CST3 = 0;	//ƒ^ƒCƒ}ƒXƒgƒbƒv
	MTU.TSTR.BIT.CST4 = 0;	//ƒ^ƒCƒ}ƒXƒgƒbƒv
  R_SW = LED_ON;             // ‰EƒZƒ“ƒTON
  L_SW = LED_ON;             // ¶ƒZƒ“ƒTON
  F_SW = LED_ON;             // ‘OƒZƒ“ƒTON
    // ===== DataFlash‚Ì‰Šú‰» =====
  DFlash_init();
}
//---------------------------------------------------------------
//  ƒpƒ‰ƒ[ƒ^“Ç‚İ‚İ
//---------------------------------------------------------------
void load_param( void ) 
{
  int i;
  // ƒZƒ“ƒT‚µ‚«‚¢’l‚ÌŒˆ‚ß‘Å‚¿
  R_REF   = 506;    // ‹æ‰æ’†‰›‚Å‚Ì‰EƒZƒ“ƒT’l 11/6[147-459-537,317] 400
  L_REF   = 580;    // ‹æ‰æ’†‰›‚Å‚Ì¶ƒZƒ“ƒT’l 11/6[387-612-587,478] 550
  F_REF   = 1500;    // ‹æ‰æ’†‰›‚Å‚Ì‘OƒZƒ“ƒT’l 11/6[71-340-925] 250
  // •Ç‚Ì—L–³”»’è—p‚µ‚«‚¢’l:ŠeƒZƒ“ƒT•Ç‚ ‚èÅ¬’l‚Æ•Ç‚È‚µ’l‚Ì’†ŠÔ’l
  R_LIM   =  180;    // ‰E 11/6[147-459-537,317] 350
  L_LIM   = 150;    // ¶ 11/6[387-612-587,478] 500
  F_LIM   = 150;    // ‘O 11/6[71-340-925] 100 150
  F_LIM2  =100;    // 2ƒ}ƒXæ‘O•Ç
  // ‘–sƒpƒ‰ƒ[ƒ^  // 1-2‘Š—ã¥
    GO_STEP   = 1620; // 1‹æŠÔ‘OiƒXƒeƒbƒv”  
    TURN_STEP = 550;  // 90“xù‰ñƒXƒeƒbƒv”  
    SLALOM_STEP_FORWARD = 20;  // ƒXƒ‰ƒ[ƒ€ù‰ñƒXƒeƒbƒv”i“à‘¤j
    SLALOM_STEP_OUT = 40; // ƒXƒ‰ƒ[ƒ€ù‰ñƒXƒeƒbƒv
    BACK_STEP = KBAT_BACK_STEP; // 1‹æŠÔŒã‘ŞƒXƒeƒbƒv”
    HALF_STEP = KBAT_HALF_STEP; // ”¼‹æŠÔ‘OiƒXƒeƒbƒv”
    for( i = 0; i < GSPEED_LEVELS; i++ ){
      slalom_step_forward_table[ i ] = SLALOM_STEP_FORWARD;
      slalom_step_out_table[ i ] = SLALOM_STEP_OUT;
      slalom_inner_speed_table[ i ] = 100;
    }
    for( i = gspeed_index_for_value(600); i < GSPEED_LEVELS; i++ ){
      slalom_inner_speed_table[ i ] = 50; // ‘¬“x600ˆÈã‚Í50‚ÉŒÅ’è
    }
    slalom_step_forward_table[gspeed_index_for_value(300)] = 110;  // ‘¬“x300—p
    slalom_step_out_table[gspeed_index_for_value(300)] = 40; // ‘¬“x300—p
    slalom_step_forward_table[gspeed_index_for_value(400)] = 34;  // ‘¬“x400—p
    slalom_step_out_table[gspeed_index_for_value(400)] = 34; // ‘¬“x400—p
    slalom_step_forward_table[gspeed_index_for_value(500)] = 8;  // ‘¬“x500—p
    slalom_step_out_table[gspeed_index_for_value(500)] = 30; // ‘¬“x500—p
    slalom_step_forward_table[gspeed_index_for_value(600)] = 2;  // ‘¬“x600—p
    slalom_step_out_table[gspeed_index_for_value(600)] = 18; // ‘¬“x600—p
    slalom_inner_speed_table[gspeed_index_for_value(300)] = 100; // ‘¬“x300—p
    slalom_inner_speed_table[gspeed_index_for_value(400)] = 100; // ‘¬“x400—p
    slalom_inner_speed_table[gspeed_index_for_value(500)] = 100; // ‘¬“x500—p

  // ‘¬“xİ’è“Ç‚İ‚İ
     gspeed_index = GSPEED_DEFAULT_INDEX;
     GSPEEDvar = GSSPEED[ gspeed_index ];		// –Ú•W‘¬“xİ’è
  slalom_step_readDF();
  set_slalom_steps_for_speed( gspeed_index );
  sensor_ref_readDF();
  goal_choice_readDF();
  go_step_readDF();
}
//---------------------------------------------------------------
//  ƒZƒ“ƒT’†‰›’lXV
//---------------------------------------------------------------
void reset_wall_samples( void )
{
  wall_sample_count = 0;
}

void log_wall_samples( void )
{
  if( wall_sample_count >= WALL_SAMPLE_MAX )
    return;
  if( control_mode == 0 || speed == 0 )
    return;
  if( L_SEN > L_LIM && R_SEN > R_LIM )
  {
    wall_sample_left[ wall_sample_count ] = L_SEN;
    wall_sample_right[ wall_sample_count ] = R_SEN;
    wall_sample_count++;
  }
}

void update_wall_ref_from_log( void )
{
  ushort i;
  long sum_l = 0;
  long sum_r = 0;

  if( wall_sample_count == 0 )
    return;

  for( i = 0; i < wall_sample_count; i++ ){
    sum_l += wall_sample_left[ i ];
    sum_r += wall_sample_right[ i ];
  }
  L_REF = (short)( sum_l / wall_sample_count );
  R_REF = (short)( sum_r / wall_sample_count );
  sensor_ref_writeDF();
}
//---------------------------------------------------------------
//  Timer  CMT0 Š„‚è‚İ(200us–ˆ‚É‚±‚ÌŠÖ”‚ªŸè‚É—Dæ‚µ‚ÄÀs‚³‚ê‚é) [int_timerw]‚Ì‘ã‚í‚è
//---------------------------------------------------------------
// Pico3‚É‡‚í‚¹‚éBu#pragma interruptv‚ğg‚í‚¸Aintprg.c“à‚ÉŠÖ”‚ğ‘‚¢‚ÄAŒÄ‚Ño‚³‚¹‚éBv
void timerc_200us( void )
{
  int err_l, err_r;
  ushort acc_num, lspeed, rspeed;
  // ¶ƒ‚[ƒ^Š„‚è‚İ
    MTU3.TGRC = timerL;                     // Ÿ‚Ì‘¬“x‚ğƒZƒbƒg
    if( speed != 0 ){ 
	MTU.TSTR.BIT.CST3 = 1;	//ƒJƒEƒ“ƒgƒXƒ^[ƒg
    }else{      // ’â~‚È‚çƒpƒ‹ƒX‚ğ‚¾‚³‚È‚¢
	MTU.TSTR.BIT.CST3 = 0;	//ƒ^ƒCƒ}ƒXƒgƒbƒv
    } 
    if( ldir == 0 ){  L_MOT_MODE = LeftGo;    // ³“]
    }else{             L_MOT_MODE = LeftBack;  // ”½“]
    }
  // ‰Eƒ‚[ƒ^Š„‚è‚İ
    MTU4.TGRC = timerR;                     // Ÿ‚Ì‘¬“x‚ğƒZƒbƒg
    if( speed != 0 ){ 
	MTU.TSTR.BIT.CST4 = 1;	//ƒJƒEƒ“ƒgƒXƒ^[ƒg
    }else{      // ’â~‚È‚çƒpƒ‹ƒX‚ğ‚¾‚³‚È‚¢
	MTU.TSTR.BIT.CST4 = 0;	//ƒ^ƒCƒ}ƒXƒgƒbƒv
    } 
    if( rdir == 0 ){ R_MOT_MODE = RightGo;   // ³“]
    }else{             R_MOT_MODE = RightBack; // ”½“]
    }
  // ƒ‚[ƒ^ƒXƒs[ƒhŠ„‚è‚İ 
  if((stepf_r == 1) || (stepf_l == 1)){
    stepf_l = 0;
    stepf_r = 0;
    // ƒ‚[ƒ^‚Ì‰Á‘¬ˆ—
    if( speed == 0 ){                         // ƒ‚[ƒ^’â~’†‚Ìˆ—
      speed_now = 0;                         // ‘¬“x‚ğ0‚É‚·‚é
      timerL = 2500;                        // ¶ Š„‚è‚İüŠú2ms 1/(0.8e-6x2500) = 500Hz
      MTU3.TGRC = timerL;
      timerR = 2500;                        // ‰E
      MTU4.TGRC = timerR;
//      CPU_LEDB = 1;  // CPU‘wLED‚ğÁ“” Â
    }else{
      if( speed > speed_now )       speed_now++;  // ‰Á‘¬
      else if( speed < speed_now )  speed_now--;  // Œ¸‘¬
      if( speed_now >= 2000 ) speed_now = 1999;     // Å‚‘¬“x
      if( speed_now < 0     ) speed_now = 0;      // Å’á‘¬“x
      acc_num = AccTable[ speed_now ];     // ‰Á‘¬“xƒe[ƒuƒ‹‚©‚ç’læ“¾
      // p¨§Œä
      if( control_mode == 1 )
      {
        // •Î·‚ğŒvZ
        err_l = L_SEN - L_REF;  // ¶•Î·‚ğŒvZ
        err_r = R_SEN - R_REF;  // ‰E•Î·‚ğŒvZ
        // •Çî•ñ‚©‚ç•Î·‚ğ‰ÁH
        if( L_SEN > L_LIM || R_SEN > R_LIM )
        {
          // ‚Ç‚¿‚ç‚©‚É•Ç‚ª‚ ‚é:•Î·‚ª‘å‚«‚¢‘¤‚ğ—Dæ‚µ‚Ä•â³
          if( err_l > err_r )
            err_r = -1 * err_l;
          else
            err_l = -1 * err_r;
        }else
        {
          // —¼•û•Ç‚È‚µ:•â³‚È‚µ
          err_l = 0;
          err_r = 0;
        }
        // •Î·‚ğ—p‚¢‚Ä•â³
          lspeed = acc_num + err_l;    // ‚±‚±‚ğ‚Ç‚¤‚·‚é‚©‚ÍƒeƒXƒg‚ª•K—v 7/14
          rspeed = acc_num + err_r;   // 
      }else if( control_mode == 2 ){//‰Eù‰ñƒXƒ‰ƒ[ƒ€
        // •Î·‚ğ—p‚¢‚Ä•â³
          lspeed = acc_num;
          rspeed = SLALOM_INNER_SPEED;   // 
      }else if( control_mode == 3 ){//¶ù‰ñƒXƒ‰ƒ[ƒ€
        // •Î·‚ğ—p‚¢‚Ä•â³
          rspeed = acc_num;
          lspeed = SLALOM_INNER_SPEED;   // 
      }else{  // control_mode = 0 
        lspeed = acc_num ;
        rspeed = acc_num ;
      }
//      timerL =  10000000L / lspeed; Œ³‚Ì’l
//      timerR =  10000000L / rspeed;
      timerL =  1500000L / lspeed;			// ‘O‰ñ‚Ì‘¬‚¢‚Æˆê‰‚ÌŠÔ 
      timerR =  1500000L / rspeed;			// 
    }
  }
    SENSOR_PT++;                 // ƒ^ƒXƒNƒ|ƒCƒ“ƒ^‚ÌXV
    if( SENSOR_PT == 5 ) SENSOR_PT = 0;  // 0-4‚Ì5ƒJƒEƒ“ƒg:200us*5=1ms
                                 // Šeˆ—‚Í1msüŠú‚ÅÀs‚³‚ê‚é
    switch( SENSOR_PT )          // ƒ^ƒXƒNƒ|ƒCƒ“ƒ^‚É]‚Á‚Äˆ—‚ğs‚¤
    {
      case 0:  // 1msecƒ^ƒCƒ}[&LCD‚ÌXV
               wait_timer++;     // waitŠÖ”—pƒJƒEƒ“ƒ^
               ccnt_playback_tick();
               LCD();            // LCDXVˆ—
               break;
      case 1:  // ‰EƒZƒ“ƒTÁ“”‚Ì‘ª’è AN0
               if ( R_SW == LED_OFF ) break;         // ƒZƒ“ƒTON/OFF‚ÌŠm”F
               S12AD.ADANSA.WORD = 0x0001;		//AN000
               S12AD.ADCSR.BIT.ADST=1;			//AD•ÏŠ·ŠJn
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD•ÏŠ·I—¹‚Ü‚Å‘Ò‚Â
//               R_PRE = S12AD.ADDR0 >> 2;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 0 - 1023(max) 10bit
               R_PRE = S12AD.ADDR0 >> 1;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 11bit‰» 
//               R_PRE = S12AD.ADDR0 ;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 12bit 
               // ‰EƒZƒ“ƒT“_“”‚Ì‘ª’è AN0
               LED = LED_ON;                         // LED‚ğ“_“”
//               LCD_wait(10);                         // ‚µ‚Î‚ç‚­‘Ò‚Â   
               LCD_wait(20);                         // ‚µ‚Î‚ç‚­‘Ò‚Â 2”{‚É 11/5
               S12AD.ADANSA.WORD = 0x0001;		//AN000
               S12AD.ADCSR.BIT.ADST=1;			//AD•ÏŠ·ŠJn
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD•ÏŠ·I—¹‚Ü‚Å‘Ò‚Â
               LED = LED_OFF;                        // LED‚ğÁ“”
//               R_PRE = (S12AD.ADDR0 >> 2) - R_PRE;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 10bit
               R_PRE = (S12AD.ADDR0 >> 1) - R_PRE;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 11bit‰» 
//               R_PRE = S12AD.ADDR0  - R_PRE;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 12bit
                                                     // –‘OŒv‘ª’l‚Æ‚Ì·•ª‚ğæ‚é(ƒmƒCƒYˆ—)
               if( R_PRE <= 999 )  R_SEN = R_PRE;    // •\¦ãŒÀˆ—
               else                R_SEN = 999; 
               break;
      case 2:  // ¶ƒZƒ“ƒTÁ“”‚Ì‘ª’è AN1
               if ( L_SW == LED_OFF ) break;         // ƒZƒ“ƒTON/OFF‚ÌŠm”F
               S12AD.ADANSA.WORD = 0x0002;		//AN001
               S12AD.ADCSR.BIT.ADST=1;			//AD•ÏŠ·ŠJn
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD•ÏŠ·I—¹‚Ü‚Å‘Ò‚Â
//               L_PRE = S12AD.ADDR1 >> 2;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 0 - 1023(max) 10bit
               L_PRE = S12AD.ADDR1 >> 1;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 11bit‰»
//               L_PRE = S12AD.ADDR1 ;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 12bit 
               // ¶ƒZƒ“ƒT“_“”‚Ì‘ª’è AN1
               LED = LED_ON;                         // LED‚ğ“_“”
//               LCD_wait(10);                         // ‚µ‚Î‚ç‚­‘Ò‚Â
               LCD_wait(20);                         // ‚µ‚Î‚ç‚­‘Ò‚Â 2”{‚É 11/5
               S12AD.ADANSA.WORD = 0x0002;		//AN001
               S12AD.ADCSR.BIT.ADST=1;			//AD•ÏŠ·ŠJn
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD•ÏŠ·I—¹‚Ü‚Å‘Ò‚Â
               LED = LED_OFF;                        // LED‚ğÁ“”
//               L_PRE = (S12AD.ADDR1 >> 2) - L_PRE;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 10bit
               L_PRE = (S12AD.ADDR1 >> 1) - L_PRE;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 11bit‰»
//               L_PRE = S12AD.ADDR1 - L_PRE;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 12bit
                                                     // –‘OŒv‘ª’l‚Æ‚Ì·•ª‚ğæ‚é(ƒmƒCƒYˆ—)
               if( L_PRE <= 999 )  L_SEN = L_PRE;    // •\¦ãŒÀˆ—
               else                L_SEN = 999;
               break;
               log_wall_samples();                    // ????NZ???T?l?????
      case 3:  // ‘OƒZƒ“ƒTÁ“”‚Ì‘ª’è ,AN2
               if ( F_SW == LED_OFF ) break;         // ƒZƒ“ƒTON/OFF‚ÌŠm”F
               S12AD.ADANSA.WORD = 0x0004;		//AN002
               S12AD.ADCSR.BIT.ADST=1;			//AD•ÏŠ·ŠJn
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD•ÏŠ·I—¹‚Ü‚Å‘Ò‚Â
//               F_PRE = S12AD.ADDR2 >> 2;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 0 - 1023(max) 10bit
               F_PRE = S12AD.ADDR2 >> 1;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 11bit‰»
//               F_PRE = S12AD.ADDR2 ;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 12bit
               // ‘OƒZƒ“ƒT“_“”‚Ì‘ª’è AN2
               LED = LED_ON;                         // LED‚ğ“_“”
//               LCD_wait(10);                         // ‚µ‚Î‚ç‚­‘Ò‚Â
               LCD_wait(20);                         // ‚µ‚Î‚ç‚­‘Ò‚Â 2”{‚É 11/5
               S12AD.ADANSA.WORD = 0x0004;		//AN002
               S12AD.ADCSR.BIT.ADST=1;			//AD•ÏŠ·ŠJn
               while(S12AD.ADCSR.BIT.ADST == 1);	//AD•ÏŠ·I—¹‚Ü‚Å‘Ò‚Â
               LED = LED_OFF;                        // LED‚ğÁ“”
//               F_PRE = (S12AD.ADDR2 >> 2) - F_PRE;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 10bit
               F_PRE = (S12AD.ADDR2 >> 1) - F_PRE;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 11bit‰»
//               F_PRE = S12AD.ADDR2  - F_PRE;       // ‘ª’èƒf[ƒ^‚ğæ‚è‚Ş 12bit ƒI[ƒoƒtƒ[‚·‚é
                                                     // –‘OŒv‘ª’l‚Æ‚Ì·•ª‚ğæ‚é(ƒmƒCƒYˆ—)
               if( F_PRE <= 9999 )  F_SEN = F_PRE;
               else                F_SEN = 9999;        // •\¦ãŒÀˆ—
               break;
      case 4:  // ƒ‚[ƒ^—p“dŒ¹ƒRƒ“ƒgƒ[ƒ‹
               if( speed != 0 ) MotorTimer = 3000;   // ƒ‚[ƒ^“®ì‚Íƒ^ƒCƒ}[ƒZƒbƒg
               else             MotorTimer--;        // ƒ‚[ƒ^’â~‚ÍƒJƒEƒ“ƒgƒ_ƒEƒ“
               if( MotorTimer < 0 )  MotorTimer =  0;
               // ƒ‚[ƒ^‚ğ“®‚©‚³‚È‚¢‚Í“dŒ¹‚ğOFF(ƒ‚[ƒ^’â~‚©‚ç3•bŒã)
               if( MotorTimer == 0 )  MOTOR_EN   =  0;  // OFF
               else                   MOTOR_EN   =  1;  // ON
               break;
      default: break;
    }
  
}
//---------------------------------------------------------------
//  ƒ‚[ƒ^ƒXƒeƒbƒv”ƒJƒEƒ“ƒgŠÖ”   RX’Ç‰Á
//---------------------------------------------------------------
void int_mot_r(void)	//‰Eƒ‚[ƒ^‚ª‚PƒXƒeƒbƒvi‚Ş–ˆ‚ÌŠ„‚è‚İ
{
	step_r++;			//ƒXƒeƒbƒv”‚ğƒJƒEƒ“ƒg
       stepf_r = 1;			// 
       STEP++;                     // ‹——£ƒJƒEƒ“ƒ^XV 
}
void int_mot_l(void)	//¶ƒ‚[ƒ^‚ª‚PƒXƒeƒbƒvi‚Ş–ˆ‚ÌŠ„‚è‚İ
{
	step_l++;			//ƒXƒeƒbƒv”‚ğƒJƒEƒ“ƒg
       stepf_l = 1;			//  
       STEP++;                    // ‹——£ƒJƒEƒ“ƒ^XV 
}
//---------------------------------------------------------------
//  waitŠÖ”(1msƒ^ƒCƒ}[)
//---------------------------------------------------------------
void pause( int x )
{
  wait_timer = 0;
  while( wait_timer != x ); // I—¹ŠÔ‚Ü‚Å‘Ò‚Â
}
//-------------------------------------------------------------------------
//  ƒL[ƒIƒtˆ—
//-------------------------------------------------------------------------
void WaitKeyOff( void )
{
  // ƒ`ƒƒƒ^ƒŠƒ“ƒO–h~ˆ—
  pause( KEY_OFF );             // İ’è‚µ‚½ŠÔ([ms])‘Ò‚Â
  // ‘S‚Ä‚ÌƒXƒCƒbƒ`‚ªOFF‚É‚È‚é‚Ü‚Åƒ‹[ƒv‚µ‚Ä‘Ò‚Â
  while(( SW_UP == SW_ON )||( SW_DOWN == SW_ON )||( SW_EXEC == SW_ON ));
}
//------------------------------------------------------------------------
/// ƒr[ƒv‰¹  ƒ^ƒCƒ}V‚ª‚È‚¢‚Ì‚ÅA‘Î‰‚ª•K—v 7/6 LED‚ÅŒÄ‚Ño‚µŠm”F‰Â”\‚É MTU0‚Åì¬ 
// ƒr[ƒv‰¹  ƒ^ƒCƒ}V‚ª‚È‚¢‚Ì‚ÅALED‚ÅŒÄ‚Ño‚µŠm”F‰Â”\‚É MTU0‚Åì¬ 
//------------------------------------------------------------------------
void beep(unsigned char tone,int value)
{
  if( tone >= BEEP_TONE_COUNT )  return;

  if( tone == BEEP_MUTE ){
    MTU.TSTR.BIT.CST0 = 0;         // no tone
    pause( value );
    return;
  }

  BUZZER_TGR = beep_data[ tone ];  // set frequency
  MTU.TSTR.BIT.CST0 = 1;           // start Beep timer
  pause( value );                  // Beep duration
  MTU.TSTR.BIT.CST0 = 0;           // stop Beep timer
}
//-------------------------------------------------------------------------
//  ccnt melody (non-blocking playback)
//-------------------------------------------------------------------------
void ccnt( int x )
{
  if( x != 0 )  return;

  ccnt_step_index = 0;
  ccnt_ms_left = 0;
  ccnt_playing = 1;
  ccnt_playback_tick();  // start first note immediately

  while( ccnt_playing ){
    pause( 1 );
  }
}



//-------------------------------------------------------------------------
//  ƒ‚[ƒh•\¦
//-------------------------------------------------------------------------
void change_mode( int x )
{
  MODE += x;                            // ƒ‚[ƒhXV
  if( MODE >= ModeMax ) MODE = -1;       // ƒ‚[ƒh‚ª’´‚¦‚Ä‚¢‚éê‡‚Í0‚É–ß‚·
  if( MODE < -1 )  MODE = ModeMax - 1;   // ƒ‚[ƒh‚ª•‰‚Ìê‡‚Íƒ‚[ƒh‚ğÅ‘å’l‚Éİ’è
  if     ( MODE == -1) modeB1( DISP );
  else if( MODE == 0 ) mode0( DISP );   // Mode0:
  else if( MODE == 1 ) mode1( DISP );   // Mode1:
  else if( MODE == 2 ) mode2( DISP );   // Mode2:
  else if( MODE == 3 ) mode3( DISP );   // Mode3:
  else if( MODE == 4 ) mode4( DISP );   // Mode4:
  else if( MODE == 5 ) mode5( DISP );   // Mode5:
  else if( MODE == 6 ) mode6( DISP );   // Mode6:
  else if( MODE == 7 ) mode7( DISP );   // Mode7:
  else if( MODE == 8 ) mode8( DISP );   // Mode8:
  else if( MODE == 9 ) mode9( DISP );   // Mode9:
  else if( MODE == 10 ) mode10( DISP );   // Mode10:
  else if( MODE == 11 ) mode11( DISP );   // Mode11:
  else if( MODE == 12 ) mode12( DISP );   // Mode12:
  else if( MODE == 13 ) mode13( DISP );   // Mode13:
}
//-------------------------------------------------------------------------
//  ƒ‚[ƒhˆ—
//-------------------------------------------------------------------------
void exec_mode( void )
{
  if     ( MODE == -1 ) modeB1( EXEC );
  else if( MODE == 0 ) mode0( EXEC );   // Mode0:
  else if( MODE == 1 ) mode1( EXEC );   // Mode1:
  else if( MODE == 2 ) mode2( EXEC );   // Mode2:
  else if( MODE == 3 ) mode3( EXEC );   // Mode3:
  else if( MODE == 4 ) mode4( EXEC );   // Mode4:
  else if( MODE == 5 ) mode5( EXEC );   // Mode5:
  else if( MODE == 6 ) mode6( EXEC );   // Mode6:
  else if( MODE == 7 ) mode7( EXEC );   // Mode7:
  else if( MODE == 8 ) mode8( EXEC );   // Mode8:
  else if( MODE == 9 ) mode9( EXEC );   // Mode9:
  else if( MODE == 10 ) mode10( EXEC );   // Mode10:
  else if( MODE == 11 ) mode11( EXEC );   // Mode11:
  else if( MODE == 12 ) mode12( EXEC );   // Mode12:
  else if( MODE == 13 ) mode13( EXEC );   // Mode13:
}

//-------------------------------------------------------------------------
//  ModeB1 : ƒ}ƒbƒvíœ
//-------------------------------------------------------------------------
void modeB1(int x)
{
  int yes = 0;  // 0:No, 1:Yes  (éŒ¾‚ÍƒuƒƒbƒNæ“ª‚É’u‚­)

  if( x == DISP )
  {
    LCD_print( 0, "B1:MPDEL" );
    LCD_print( 8, "        " );
    return;
  }

  LCD_print( 0, "B1:MPDEL" );
  LCD_print( 8, "Really? " );

  while( 1 ){
    if( yes ) LCD_print( 8, "     Yes" );
    else      LCD_print( 8, "      No" );

    if( SW_UP == SW_ON ){
      yes = 1;
      WaitKeyOff();
    }else if( SW_DOWN == SW_ON ){
      yes = 0;
      WaitKeyOff();
    }else if( SW_EXEC == SW_ON ){
      WaitKeyOff();
      if( yes ){
        DFlash_init();
      }
      return;
    }
  }
}


//-------------------------------------------------------------------------
//  Mode0 : ƒZƒ“ƒTƒ`ƒFƒbƒN
//-------------------------------------------------------------------------
void mode0( int x ) 
{
  if( x == DISP )  // DISPƒ‚[ƒh‚Ìê‡
  {
    // ƒ‚[ƒh“à—e•\¦
    LCD_print( 0, "0:Sensor" );
    LCD_print( 8, "        " );
    pause( 1000 );
    LCD_print( 0, "  F     " );
    LCD_print( 8, "L   R   " );
    return;                     // ˆÈ‰º‚ÌÀsˆ—‚ğ‚µ‚È‚¢‚Å–ß‚é
  }
  // Àsƒ‚[ƒh‚Ìê‡
  L_REF = 0; R_REF = 0;         // ƒf[ƒ^‰Šú‰»
  for( x = 0; x < 32; x++ )     // ƒf[ƒ^‘ª’è(64ƒ|ƒCƒ“ƒg)
  {
    L_REF += L_SEN;
    R_REF += R_SEN;
    pause(1);
  }
  R_REF = R_REF / 32;           // ‘ª’èƒf[ƒ^‚ğ•½‹Ï‰»
  L_REF = L_REF / 32;
  LCD_print( 0, " L    R " );
  LCD_print( 8, "        " );
  LCD_dec_out(  8, L_REF, 3 );  // ¶ƒZƒ“ƒT’l‚ğLCD‚É•\¦
  LCD_dec_out( 13, R_REF, 3 );  // ‰EƒZƒ“ƒT’l‚ğLCD‚É•\¦
  sensor_ref_writeDF();
  pause( 2000 );                // 2•bŠÔ•\¦
}
//-------------------------------------------------------------------------
//  Mode1 : ƒ‚[ƒ^ƒeƒXƒg
//-------------------------------------------------------------------------
void mode1(int x)
{
  if( x == DISP )  // DISPƒ‚[ƒh‚Ìê‡
  {
    // ƒ‚[ƒh“à—e•\¦
    LCD_print( 0, "1:M-TEST" );
    LCD_print( 8, "        " );
    return;                     // ˆÈ‰º‚ÌÀsˆ—‚ğ‚µ‚È‚¢‚Å–ß‚é
  }
  // Àsƒ‚[ƒh‚Ìê‡
  LCD_print( 8,"SPD=     ");
  rdir = 0; ldir = 0;           // ‰ñ“]•ûŒü‚ğ’¼i
  control_mode = 1;             // ’¼ü‘–s—pp¨§Œä‚ ‚è
  STEP = 0;                               // ‹——£ƒJƒEƒ“ƒ^ƒNƒŠƒA ™
  while(1){
    LCD_dec_out( 12, speed, 4 );
    if( SW_UP   == 0 ) { speed += 100; WaitKeyOff(); }
    if( SW_DOWN == 0 ) { speed -= 100; WaitKeyOff(); }
    if( SW_EXEC == 0 ) { speed = 0; return; }
    if( speed > 2000 )    speed = 2000;
    else if( speed < 0 )  speed = 0;
  }
}
//-------------------------------------------------------------------------
//  Mode2 : 1‹æŠÔ‘Oi
//-------------------------------------------------------------------------
void mode2(int x)
{
  if( x == DISP )  // DISPƒ‚[ƒh‚Ìê‡
  {
    // ƒ‚[ƒh“à—e•\¦
    LCD_print( 0, "2: 1 GO " );
    LCD_print( 8, "STEP    " );
    return;                     // ˆÈ‰º‚ÌÀsˆ—‚ğ‚µ‚È‚¢‚Å–ß‚é
  }
  // Àsƒ‚[ƒh‚Ìê‡
  while(1){
    LCD_dec_out( 12, GO_STEP, 4 );
    if( SW_UP   == 0 ) { GO_STEP += 10; WaitKeyOff(); }
    if( SW_DOWN == 0 ) { GO_STEP -= 10; WaitKeyOff(); }
//  if( SW_EXEC == 0 ) { WaitKeyOff();  com_go( 1 );  com_stop(); }
    if( SW_EXEC == 0 ) {
      WaitKeyOff();
      go_step_writeDF();
      com_go(1 );
      com_stop();
      break;
    }
  }
}
//-------------------------------------------------------------------------
//  Mode3 : N‹æŠÔ‘Oi
//-------------------------------------------------------------------------
void mode3(int x)
{
  int n = 5;                    // ‘Oi‹æŠÔ”F‰Šú’l 5
  if( x == DISP )  // DISPƒ‚[ƒh‚Ìê‡
  {
    // ƒ‚[ƒh“à—e•\¦
    LCD_print( 0, "3: N GO " );
    LCD_print( 8, "     N  " );
    return;                     // ˆÈ‰º‚ÌÀsˆ—‚ğ‚µ‚È‚¢‚Å–ß‚é
  }
  // Àsƒ‚[ƒh‚Ìê‡
  LCD_dec_out( 8, GO_STEP, 4 );
  while(1){
    LCD_dec_out( 14, n, 2 );
    if( SW_UP   == 0 ) { n++; WaitKeyOff(); }
    if( SW_DOWN == 0 ) { n--; WaitKeyOff(); }
    if( SW_EXEC == 0 ) { WaitKeyOff();  com_go( n );  com_stop(); }
  }
}
//-------------------------------------------------------------------------
//  Mode4 : 180ƒ^[ƒ“R
//-------------------------------------------------------------------------
void mode4( int x )
{
  if( x == DISP )  // DISPƒ‚[ƒh‚Ìê‡
  {
    // ƒ‚[ƒh“à—e•\¦
    LCD_print( 0, "4: TURN " );
    LCD_print( 8, "        " );
    return;                     // ˆÈ‰º‚ÌÀsˆ—‚ğ‚µ‚È‚¢‚Å–ß‚é
  }
  // Àsƒ‚[ƒh‚Ìê‡
  while(1){
    LCD_dec_out( 10, TURN_STEP, 4 );
    if( SW_UP   == 0 ) { TURN_STEP += 10; WaitKeyOff(); }
    if( SW_DOWN == 0 ) { TURN_STEP -= 10; WaitKeyOff(); }
    if( SW_EXEC == 0 ) { com_turn(2); com_stop(); }
  }
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static void set_slalom_steps_for_speed( int index )
{
  if( index < 0 || index >= GSPEED_LEVELS )
    return;
  SLALOM_STEP_FORWARD = slalom_step_forward_table[ index ];
  SLALOM_STEP_OUT = slalom_step_out_table[ index ];
  SLALOM_INNER_SPEED = slalom_inner_speed_table[ index ];
}

static void store_slalom_steps_for_speed( int index )
{
  if( index < 0 || index >= GSPEED_LEVELS )
    return;
  slalom_step_forward_table[ index ] = SLALOM_STEP_FORWARD;
  slalom_step_out_table[ index ] = SLALOM_STEP_OUT;
  slalom_inner_speed_table[ index ] = SLALOM_INNER_SPEED;
}

//  Speed selection helpers
//-------------------------------------------------------------------------
static int gspeed_index_for_value( short speed )
{
  int i;
  for( i = 0; i < GSPEED_LEVELS; i++ ){
    if( GSSPEED[ i ] == speed )
      return i;
  }
  return -1;
}

static void update_gspeed_index( int delta )
{
  if( delta > 0 ){
    gspeed_index++;
    if( gspeed_index >= GSPEED_LEVELS ) gspeed_index = 0;
  }else{
    if( gspeed_index == 0 ) gspeed_index = GSPEED_LEVELS - 1;
    else gspeed_index--;
  }
  GSPEEDvar = GSSPEED[ gspeed_index ];
  set_slalom_steps_for_speed( gspeed_index );
}
static void select_gspeed( const char *title )
{
  if( GSPEED_LEVELS <= 1 )
    return;
  if( title != 0 )
    LCD_print( 0, title );
  LCD_print( 8, "Spd +/- " );
  LCD_dec_out( 12, GSPEEDvar, 3 );
  while( 1 ){
    if( SW_UP   == 0 ){
      update_gspeed_index( +1 );
      LCD_dec_out( 12, GSPEEDvar, 3 );
      WaitKeyOff();
    }else if( SW_DOWN == 0 ){
      update_gspeed_index( -1 );
      LCD_dec_out( 12, GSPEEDvar, 3 );
      WaitKeyOff();
    }else if( SW_EXEC == 0 ){
      WaitKeyOff();
      break;
    }
  }
}

//-------------------------------------------------------------------------
//  Mode5 : ’Tõ‘–s 
//-------------------------------------------------------------------------
void mode5( int x )
{
  if( x == DISP )
  {
    LCD_print( 0, "5:Search" );
    LCD_print( 8, "Spd " );
    LCD_dec_out( 12, GSPEEDvar, 3 );
    return;
  }

  select_gspeed( "5:Search" );
  pos_x = 0; pos_y = 0; head = 0;
  ccnt(0);
  mouse_search( goal_x, goal_y, GSPEEDvar, S_MODE );
  DFlash_init();
  map_writeDF(MDATA_BK1);
  ccnt(0);
  mouse_search( 0, 0, GSPEEDvar, S_MODE );
  DFlash_init();
  map_writeDF(MDATA_BK1);
}


//-------------------------------------------------------------------------
//  Mode6 : “ñŸ‘–s
//-------------------------------------------------------------------------
void mode6( int x )
{
  if( x == DISP )
  {
    LCD_print( 0, "6:Try   " );
    LCD_print( 8, "Spd " );
    LCD_dec_out( 12, GSPEEDvar, 3 );
    return;
  }

  select_gspeed( "6:Try   " );
  map_DFread(MDATA_BK1);
  pos_x = 0; pos_y = 0; head = 0;
  ccnt(0);
  mouse_search( goal_x, goal_y, GSPEEDvar, T_MODE );
}


//-------------------------------------------------------------------------
// Mode7 :’Tõ‘–s ‹A‚è‚Ì’Tõ–³‚µ 
//-------------------------------------------------------------------------
void mode7( int x )
{
///short sp = 50;	// ‘¬“x•ÏX—p
  if( x == DISP )  // DISPƒ‚[ƒh‚Ìê‡
  {
    // ƒ‚[ƒh“à—e•\¦
    LCD_print( 0, "Sear+-:7" );
    LCD_print( 8, "Sear  x+-" );
    return;                     // ˆÈ‰º‚ÌÀsˆ—‚ğ‚µ‚È‚¢‚Å–ß‚é
  }
  // Àsƒ‚[ƒh‚Ìê‡
  select_gspeed( "Sear+-:7" );
  pos_x = 0; pos_y = 0; head = 0;
  // ’Tõ
  mouse_search( goal_x, goal_y, GSPEEDvar, S_MODE );  // s‚«‚Ì’Tõ
}
//-------------------------------------------------------------------------
// Mode8 : ƒS[ƒ‹À•W‘I‘ğ
//-------------------------------------------------------------------------
void mode8( int x )
{
  if( x == DISP )
  {
    LCD_print( 0, "8:GoalSel" );
    LCD_print( 8, goal_choices[ goal_choice_index ].label );
    return;
  }
  while( 1 ){
    LCD_print( 0, "8:GoalSel" );
    LCD_print( 8, goal_choices[ goal_choice_index ].label );
    if( SW_UP == 0 ){
      advance_goal_choice( +1 );
      WaitKeyOff();
    }else if( SW_DOWN == 0 ){
      advance_goal_choice( -1 );
      WaitKeyOff();
    }else if( SW_EXEC == 0 ){
      WaitKeyOff();
      goal_choice_writeDF();
      beep( BEEP_C5, 150 );
      return;
    }
  }
}

//-------------------------------------------------------------------------
//  Mode9 : Search 1 round trip + Try 4 round trips
//-------------------------------------------------------------------------
void mode9( int x )
{
  int round_trip;
  if( x == DISP )
  {
    LCD_print( 0, "9:S1/T4 " );
    LCD_print( 8, "Spd " );
    LCD_dec_out( 12, GSPEEDvar, 3 );
    return;
  }

  select_gspeed( "9:S1/T4 " );
  pos_x = 0; pos_y = 0; head = 0;
  ccnt(0);
  mouse_search( goal_x, goal_y, GSPEEDvar, S_MODE );
  DFlash_init();
  map_writeDF(MDATA_BK1);
  //ccnt(0);
  mouse_search( 0, 0, GSPEEDvar, S_MODE );
  DFlash_init();
  map_writeDF(MDATA_BK1);

  map_DFread(MDATA_BK1);
  pos_x = 0; pos_y = 0; head = 0;
  for( round_trip = 0; round_trip < 4; round_trip++ ){
    ccnt(0);
    mouse_search( goal_x, goal_y, GSPEEDvar, T_MODE );
    //ccnt(0);
    mouse_search( 0, 0, GSPEEDvar, T_MODE );
  }
}


static void render_center_ref_line( int base_pt, const center_ref_t *ref )
{
  char line[ 9 ];
  int i;
  line[ 0 ] = ref->label;
  line[ 1 ] = '=';
  for( i = 2; i < 8; i++ )
    line[ i ] = ' ';
  line[ 8 ] = 0;
  LCD_print( base_pt, line );
  LCD_dec_out( base_pt + 2, *ref->value, ref->digits );
}

void mode10( int x )
{
  int index = 0;
  if( x == DISP )
  {
    LCD_print( 0, "10:RefCh" );
    LCD_print( 8, "L R F   " );
    return;
  }
  while( 1 ){
    const center_ref_t *ref = &center_refs[ index ];
    LCD_print( 0, "10:RefCh" );
    render_center_ref_line( 8, ref );
    if( SW_UP == SW_ON ){
      index++;
      if( index >= CENTER_REF_COUNT ) index = 0;
      WaitKeyOff();
    }else if( SW_DOWN == SW_ON ){
      if( index == 0 ) index = CENTER_REF_COUNT - 1;
      else index--;
      WaitKeyOff();
    }else if( SW_EXEC == SW_ON ){
      WaitKeyOff();
      return;
    }else{
      pause( 100 );
    }
  }
}

void mode11( int x )
{
  int index = 0;
  if( x == DISP )
  {
    LCD_print( 0, "11:SetRef" );
    LCD_print( 8, "+/-Exec " );
    return;
  }
  while( 1 ){
    const center_ref_t *ref = &center_refs[ index ];
    LCD_print( 0, "11:SetRef" );
    render_center_ref_line( 0, ref );
    LCD_print( 8, "+/-Exec " );
    if( SW_UP == SW_ON ){
      int temp = *ref->value + 10;
      if( temp > CENTER_REF_MAX ) temp = CENTER_REF_MAX;
      *ref->value = (short)temp;
      WaitKeyOff();
    }else if( SW_DOWN == SW_ON ){
      int temp = *ref->value - 10;
      if( temp < CENTER_REF_MIN ) temp = CENTER_REF_MIN;
      *ref->value = (short)temp;
      WaitKeyOff();
    }else if( SW_EXEC == SW_ON ){
      WaitKeyOff();
      index++;
      if( index >= CENTER_REF_COUNT )
        break;
    }else{
      pause( 100 );
    }
  }
  sensor_ref_writeDF();
  LCD_print( 0, "RefSaved" );
  LCD_print( 8, "        " );
  pause( 1000 );
}

//-------------------------------------------------------------------------
//  Mode12 : 180ƒ^[ƒ“R
//-------------------------------------------------------------------------
void mode12( int x ){
  if( x == DISP )  // DISP??????
  {
    // ???????
    LCD_print( 0, "12:SLSTEP" );
    LCD_print( 8, "Spd     " );
    LCD_dec_out( 12, GSPEEDvar, 3 );
    return;                     // ??????????????
  }
  select_gspeed( "12:SLSTEP" );
  // ????????
  while(1){
    while(1){
      LCD_dec_out( 8, SLALOM_STEP_FORWARD, 4 );
      if( SW_UP   == 0 ) { SLALOM_STEP_FORWARD += 2; WaitKeyOff(); }
      if( SW_DOWN == 0 && SLALOM_STEP_FORWARD > 1 ) { SLALOM_STEP_FORWARD -= 2; WaitKeyOff(); }
      store_slalom_steps_for_speed( gspeed_index );
      if( SW_EXEC == 0 ) { WaitKeyOff(); break;}
    }
    while(1){
      LCD_dec_out( 12, SLALOM_STEP_OUT, 4 );
      if( SW_UP   == 0 ) { SLALOM_STEP_OUT += 2; WaitKeyOff(); }
      if( SW_DOWN == 0 && SLALOM_STEP_OUT > 1 ) { SLALOM_STEP_OUT -= 2; WaitKeyOff(); }
      store_slalom_steps_for_speed( gspeed_index );
      if( SW_EXEC == 0 ) {
        slalom_step_writeDF();
        control_mode = 1;
        rdir = 0; ldir = 0;
        step_r = 0;
        step_l = 0;
        STEP = 0;
        start_back_wall_contact();
        speed = GSPEEDvar;
        while( STEP < GO_STEP * 3 / 2 - 300 + HALF_STEP );
        com_slalom_turn(0);
        com_stop();
        break;
      }
    }
  }
}

//-------------------------------------------------------------------------
//  Mode13 : ƒXƒ‰ƒ[ƒ€‘–s
//-------------------------------------------------------------------------
void mode13( int x )
{
  if( x == DISP )
  {
    LCD_print( 0, "13:SLTry" );
    LCD_print( 8, "Spd " );
    LCD_dec_out( 12, GSPEEDvar, 3 );
    return;
  }

  select_gspeed( "13:Try   " );
  set_slalom_steps_for_speed(gspeed_index);
  map_DFread(MDATA_BK1);
  pos_x = 0; pos_y = 0; head = 0;
  ccnt(0);
  slalom_search( goal_x, goal_y, GSPEEDvar, T_MODE );
}


//-------------------------------------------------------------------------
//  ’TõŠÖ”    ƒRƒ“ƒpƒCƒ‹Å“K‰»‚ğŠO‚µŒ³‚É–ß‚·š 7/22
//-------------------------------------------------------------------------
void mouse_search( int goal_x, int goal_y, int spd, int mode )
{
  short motion, next_motion, zerozero;
  zerozero = 0;
  reset_wall_samples();
  if( pos_x == 0 && pos_y == 0 ){
    start_back_wall_contact();
    zerozero = 1;
  }
  //countdown();                  
  // ƒJƒEƒ“ƒgƒ_ƒEƒ“
  while( 1 ){
    // ‚P‚Â‚Ìƒ‹[ƒv‚Í‹æŠÔ’†S‚©‚çŸ‚Ì‹æŠÔ’†S‚Ü‚Å
    // Å‰‚É”¼‹æ‰æ’¼i
    control_mode = 1;             // p¨§ŒäON
    rdir = 0; ldir = 0;           // ‰ñ“]•ûŒü‚ğ’¼i
    step_r = 0;                        //‰EƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
    step_l = 0;                        //¶ƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
    STEP = 0;                     // ‹——£ƒJƒEƒ“ƒ^ƒŠƒZƒbƒg
    speed = spd;                  // ‘¬“xİ’è
    CPU_LED = 1;  // CPU‘wLED‚ğÁ“” Ô 9/23
 
    // À•WXV
    if     ( head == 0 ) pos_y++; // –kŒü‚« y+1
    else if( head == 1 ) pos_x++; // “ŒŒü‚« x+1
    else if( head == 2 ) pos_y--; // “ìŒü‚« y-1
    else if( head == 3 ) pos_x--; // ¼Œü‚« x-1
    
    // ƒ|ƒeƒ“ƒVƒƒƒ‹MAPŒvZ
    make_potential( goal_x, goal_y, mode );
    next_motion = search_adachi();  // Ÿ‚Ìs“®—\‘ª
    if ( (F_SEN > F_LIM2 || next_motion == 1 || next_motion == 3) && GSPEEDvar > 700 ) speed = 700; // 2ƒ}ƒXæ‚É•Ç‚ª‚ ‚éê‡‚Í‘¬“x§ŒÀ
    

    if( zerozero == 1 ){  // (0,0)ƒXƒ^[ƒg‚Ì‚İ
      while( STEP < HALF_STEP )  // ”¼‹æŠÔi‚Ş
        log_wall_samples();
      step_l = 0;                        //¶ƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
      step_r = 0;                        //‰EƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
      STEP = 0;                     // ‹——£ƒJƒEƒ“ƒ^ƒŠƒZƒbƒg
      zerozero = 0;
    }
    // ”¼‹æŠÔ’¼i
    while( STEP < GO_STEP / 2 )  // ”¼‹æŠÔi‚Ş 
      log_wall_samples();
    // ’Œ‚Ü‚Åi‚ñ‚¾‚ç
    // •Çî•ñæ“¾•MAPƒf[ƒ^ã‘‚«
    if( mode == S_MODE )
    make_map_data();
    // ‘«—§–@‚Ås“®Œˆ’è
    motion = search_adachi();
    
    // ƒS[ƒ‹‚Ì—áŠOˆ—iã‚ÅŒˆ‚ß‚½s“®‚ªã‘‚«‚³‚ê‚éj
    if( pos_x == goal_x && pos_y == goal_y )
      motion = 4;                       // ƒS[ƒ‹“’BF”½“]’â~
    // s“®‚ğÀs
    switch( motion ){
      // ’¼i
      case  0 : while( STEP < GO_STEP )  // c‚è”¼‹æŠÔi‚Ş 
                log_wall_samples();
                head_change = 0;          // is•ûŒüXV•Ï”‚ğ‘O‚Éİ’è
                break;
      // ‰EÜ
      case  1 : while( STEP < GO_STEP - speed_now * speed_now / 300 && F_SEN < F_REF)  // Œ¸‘¬ˆæ‚ğc‚µ‚Ä’¼i 
                log_wall_samples();
                speed = 1;
                while( STEP < GO_STEP && F_SEN < F_REF)  // c‚èƒXƒeƒbƒv”‚ÅŒ¸‘¬ 
                  log_wall_samples();
                com_turn( 0 );            // ‰E90“xù‰ñ
                head_change = 1;          // is•ûŒüXV•Ï”‚ğ‰E‚Éİ’è
                break;
      // ”½“]
      case  2 : while( STEP < GO_STEP - speed_now * speed_now / 300 && F_SEN < F_REF)  // Œ¸‘¬ˆæ‚ğc‚µ‚Ä’¼i 
                log_wall_samples();
                speed = 1;
                while( STEP < GO_STEP && F_SEN < F_REF)  // c‚èƒXƒeƒbƒv”‚ÅŒ¸‘¬ 
                  log_wall_samples();
                kbat_lf_turn();            // ”½“]
                head_change = 2;          // is•ûŒüXV•Ï”‚ğŒã‚Éİ’è
                break;
      // ¶Ü
      case  3 : while( STEP < GO_STEP - speed_now * speed_now / 300 && F_SEN < F_REF)  // Œ¸‘¬ˆæ‚ğc‚µ‚Ä’¼i 
                log_wall_samples();
                speed = 1;
                while( STEP < GO_STEP && F_SEN < F_REF)  // c‚èƒXƒeƒbƒv”‚ÅŒ¸‘¬ 
                  log_wall_samples();
                com_turn( 1 );            // ¶90“xù‰ñ
                head_change = 3;          // is•ûŒüXV•Ï”‚ğ¶‚Éİ’è
                break;
      // ”½“]’â~
      case  4 : while( STEP < GO_STEP - speed_now * speed_now / 300 && F_SEN < F_REF)  // Œ¸‘¬ˆæ‚ğc‚µ‚Ä’¼i 
                log_wall_samples();
                speed = 1;
                while( STEP < GO_STEP && F_SEN < F_REF)  // c‚èƒXƒeƒbƒv”‚ÅŒ¸‘¬ //
                  log_wall_samples();
                goal_kbat_turn();         // ”½“](ƒS[ƒ‹•Ç“–‚Ä)
                head_change = 2;          // is•ûŒüXV•Ï”‚ğŒã‚Éİ’è
                head = ( head + head_change ) & 0x03; // Ú×‚Í‰º‚ğQÆ
                finish();                 // ƒS[ƒ‹‰¹
                return;                   // ƒ‹[ƒvI—¹
                break;
      // ‚»‚Ì‘¼
      default : com_stop();               // ’â~
                head_change = 0;          // is•ûŒüXV•Ï”‚ğ‘O‚Éİ’è
                head = ( head + head_change ) & 0x03; // Ú×‚Í‰º‚ğQÆ
                return;                   // ƒ‹[ƒvI—¹
                break;
    }
    
    // is•ûŒüXV•Ï”head_change‚ğ—p‚¢‚ÄŒ»İ‚Ìis•ûŒühead‚ğXV
    head = ( head + head_change ) & 0x03; // XV”’l‚ğ‰ÁZ‚µ‚Ä2i”‰º2Œ…‚Åƒ}ƒXƒN
                                          // 00 -> 01 -> 10 -> 11 -(ƒ}ƒXƒN)-> 00
  }
}

//-------------------------------------------------------------------------
//  ’TõŠÖ”    ƒRƒ“ƒpƒCƒ‹Å“K‰»‚ğŠO‚µŒ³‚É–ß‚·š 7/22
//-------------------------------------------------------------------------
void slalom_search( int goal_x, int goal_y, int spd, int mode )
{
  short motion, next_motion, zerozero;
  zerozero = 0;
  reset_wall_samples();
  if( pos_x == 0 && pos_y == 0 ){
    start_back_wall_contact();
    zerozero = 1;
  }
  //countdown();                  
  // ƒJƒEƒ“ƒgƒ_ƒEƒ“
  while( 1 ){
    // ‚P‚Â‚Ìƒ‹[ƒv‚Í‹æŠÔ’†S‚©‚çŸ‚Ì‹æŠÔ’†S‚Ü‚Å
    // Å‰‚É”¼‹æ‰æ’¼i
    control_mode = 1;             // p¨§ŒäON
    rdir = 0; ldir = 0;           // ‰ñ“]•ûŒü‚ğ’¼i
    step_r = 0;                        //‰EƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
    step_l = 0;                        //¶ƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
    STEP = 0;                     // ‹——£ƒJƒEƒ“ƒ^ƒŠƒZƒbƒg
    speed = spd;                  // ‘¬“xİ’è
    CPU_LED = 1;  // CPU‘wLED‚ğÁ“” Ô 9/23
 
    // À•WXV
    if     ( head == 0 ) pos_y++; // –kŒü‚« y+1
    else if( head == 1 ) pos_x++; // “ŒŒü‚« x+1
    else if( head == 2 ) pos_y--; // “ìŒü‚« y-1
    else if( head == 3 ) pos_x--; // ¼Œü‚« x-1
    
    // ƒ|ƒeƒ“ƒVƒƒƒ‹MAPŒvZ
    make_potential( goal_x, goal_y, mode );
    next_motion = search_adachi(); // Ÿ‚Ìs“®‚ğ—\‘ª
    if( zerozero ==1 ){  // (0,0)ƒXƒ^[ƒg‚Ì‚İ
      while( STEP < HALF_STEP );  // ”¼‹æŠÔi‚Ş
      step_r = 0;                        //‰EƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
      step_l = 0;                        //¶ƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
      STEP = 0;                     // ‹——£ƒJƒEƒ“ƒ^ƒŠƒZƒbƒg
      zerozero = 0;
    }
    if(motion == 1 || motion ==3 ){
      // ‘O‚Ìs“®‚ª‰EÜor¶Ü‚Ìê‡A‹——£‚ğ­‚È‚­‚·‚éB
      while( STEP < GO_STEP / 2 - 100 );  // ­‚µi‚Ş
    }else if( (next_motion == 1 || next_motion == 3) && GSPEEDvar >= 600 ){ // ‘¬“x700ˆÈã‚ÅŸ‚Ìs“®‚ª‰EÜor¶Ü‚Ìê‡A‘Oi‚µ‚È‚¢
      control_mode = 0; // p¨§ŒäOFF
      while( STEP < 200 );  // ‚Ù‚Æ‚ñ‚Çi‚Ü‚È‚¢
    }else{
      while( STEP < GO_STEP / 2 );  // ”¼‹æŠÔi‚Ş 
    }
    // ’Œ‚Ü‚Åi‚ñ‚¾‚ç
    // •Çî•ñæ“¾•MAPƒf[ƒ^ã‘‚«
    if( mode == S_MODE )
    make_map_data();
    // ‘«—§–@‚Ås“®Œˆ’è
    motion = search_adachi();
    
    // ƒS[ƒ‹‚Ì—áŠOˆ—iã‚ÅŒˆ‚ß‚½s“®‚ªã‘‚«‚³‚ê‚éj
    if( pos_x == goal_x && pos_y == goal_y )
      motion = 4;                       // ƒS[ƒ‹“’BF”½“]’â~
    // s“®‚ğÀs
    switch( motion ){
      // ’¼i
      case  0 : while( STEP < GO_STEP );  // c‚è”¼‹æŠÔi‚Ş 
                head_change = 0;          // is•ûŒüXV•Ï”‚ğ‘O‚Éİ’è
                break;
      // ‰EÜ
      case  1 : com_slalom_turn(0);         // ‰E90“xù‰ñ
                head_change = 1;          // is•ûŒüXV•Ï”‚ğ‰E‚Éİ’è
                break;
      // ”½“]
      case  2 : while( STEP < GO_STEP - speed_now * speed_now / 300 && F_SEN < F_REF);  // Œ¸‘¬ˆæ‚ğc‚µ‚Ä’¼i 
                speed = 1;
                while( STEP < GO_STEP && F_SEN < F_REF);  // c‚èƒXƒeƒbƒv”‚ÅŒ¸‘¬ 
                kbat_lf_turn();            // ”½“]
                head_change = 2;          // is•ûŒüXV•Ï”‚ğŒã‚Éİ’è
                break;
      // ¶Ü
      case  3 : com_slalom_turn( 1 );            // ¶90“xù‰ñ
                head_change = 3;          // is•ûŒüXV•Ï”‚ğ¶‚Éİ’è
                break;
      // ”½“]’â~
      case  4 : while( STEP < GO_STEP - speed_now * speed_now / 300 && F_SEN < F_REF);  // Œ¸‘¬ˆæ‚ğc‚µ‚Ä’¼i 
                speed = 1;
                while( STEP < GO_STEP && F_SEN < F_REF);  // c‚èƒXƒeƒbƒv”‚ÅŒ¸‘¬ //
                goal_kbat_turn();         // ”½“](ƒS[ƒ‹•Ç“–‚Ä)
                head_change = 2;          // is•ûŒüXV•Ï”‚ğŒã‚Éİ’è
                head = ( head + head_change ) & 0x03; // Ú×‚Í‰º‚ğQÆ
                finish();                 // ƒS[ƒ‹‰¹
                return;                   // ƒ‹[ƒvI—¹
                break;
      // ‚»‚Ì‘¼
      default : com_stop();               // ’â~
                head_change = 0;          // is•ûŒüXV•Ï”‚ğ‘O‚Éİ’è
                head = ( head + head_change ) & 0x03; // Ú×‚Í‰º‚ğQÆ
                return;                   // ƒ‹[ƒvI—¹
                break;
    }
    
    // is•ûŒüXV•Ï”head_change‚ğ—p‚¢‚ÄŒ»İ‚Ìis•ûŒühead‚ğXV
    head = ( head + head_change ) & 0x03; // XV”’l‚ğ‰ÁZ‚µ‚Ä2i”‰º2Œ…‚Åƒ}ƒXƒN
                                          // 00 -> 01 -> 10 -> 11 -(ƒ}ƒXƒN)-> 00
  }
}

//-------------------------------------------------------------------------
//  ’¼iƒ‚ƒWƒ…[ƒ‹ (N‹æŠÔ‘Oi) 
//-------------------------------------------------------------------------
void com_go( int n )
{
  control_mode = 1;                       // ’¼ü‘–s—pp¨§Œä
  step_r = 0;                               //‰EƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
  step_l = 0;                               //¶ƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
  STEP = 0;                               // ‹——£ƒJƒEƒ“ƒ^ƒNƒŠƒA
  rdir = 0; ldir = 0;                     // ‰ñ“]•ûŒü‚ğ’¼i
  // ‰Á‘¬ƒ‚[ƒh
  speed = 100;        // –Ú•W‘¬“xİ’è
  while( speed > speed_now );                   // –Ú•W‘¬“x‚É‚È‚é‚Ü‚Å‰Á‘¬ 
  // ’è‘¬ƒ‚[ƒh
  speed = speed_now;  // ‰Á‘¬Œã‚Ì‘¬“x
  while( STEP < GO_STEP * n - speed_now * 2 );  // Œ¸‘¬ƒXƒeƒbƒv”‚ğc‚µ‚Ä’è‘¬ˆÚ“®
                                                // ‘S‘ÌƒXƒeƒbƒv”-Œ¸‘¬—pƒXƒeƒbƒv”
  // Œ¸‘¬ƒ‚[ƒh
  speed = 1;          // Å’á‘¬“xİ’è
  while( STEP < GO_STEP * n );                  // c‚è‚ÌƒXƒeƒbƒv”‚ÅŒ¸‘¬ 
}
//-------------------------------------------------------------------------
//  ’â~ƒ‚ƒWƒ…[ƒ‹
//-------------------------------------------------------------------------
void com_stop( void )
{
  control_mode = 0;           // p¨§Œä–³‚µ
  rdir = 0; ldir = 0;         // ƒ‚[ƒ^‚Ì‰ñ“]•ûŒü‚ğ‘Oi
  step_r = 0;                               //‰EƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
  step_l = 0;                               //¶ƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
  STEP = 0;                   // ‹——£ƒJƒEƒ“ƒ^‚ğƒŠƒZƒbƒg
  speed = 0;  speed_now = 0;  // ƒ‚[ƒ^‚Ì§Œä—p‚Ì•Ï”‚ğƒŠƒZƒbƒg
  pause(100);                 // 0.1•bƒ‚[ƒ^‚ğ’â~
}
//-------------------------------------------------------------------------
//  ù‰ñƒ‚ƒWƒ…[ƒ‹ (0:R90 1:L90 2:R180 3:L180) 
//-------------------------------------------------------------------------
void com_turn( int t_mode )
{
  short T_STEP;
  com_stop();                                             // ’â~
  control_mode = 0;                                       // p¨§Œä‚È‚µ
  if     ( t_mode == 0 ) { T_STEP = TURN_STEP; rdir = 1; ldir = 0; } // ‰E‚X‚O“x
  else if( t_mode == 1 ) { T_STEP = TURN_STEP; rdir = 0; ldir = 1; } // ¶‚X‚O“x
  else if( t_mode == 2 ) { T_STEP = TURN_STEP * 2; rdir = 1; ldir = 0; } // ‰E”½“]
  else if( t_mode == 3 ) { T_STEP = TURN_STEP * 2; rdir = 0; ldir = 1; } // ¶”½“]
  // ‰Á‘¬ƒ‚[ƒh
  speed = 100;        // –Ú•W‘¬“xİ’è
  while( speed > speed_now );                   // –Ú•W‘¬“x‚É‚È‚é‚Ü‚Å‰Á‘¬ š
  // ’è‘¬ƒ‚[ƒh
  speed = speed_now;  // ‰Á‘¬Œã‚Ì‘¬“x
  while( STEP < T_STEP - speed_now * 2 );       // Œ¸‘¬ƒXƒeƒbƒv”‚ğc‚µ‚Ä’è‘¬ˆÚ“® 
                                                // ‘S‘ÌƒXƒeƒbƒv”-Œ¸‘¬—pƒXƒeƒbƒv”
  // Œ¸‘¬ƒ‚[ƒh
  speed = 1;          // Å’á‘¬“xİ’è
  while( STEP < T_STEP );                       // c‚è‚ÌƒXƒeƒbƒv”‚ÅŒ¸‘¬ 
}

//-------------------------------------------------------------------------
//  ƒXƒ‰ƒ[ƒ€ƒ‚ƒWƒ…[ƒ‹ (0:R90 1:L90 2:R180 3:L180) 
//-------------------------------------------------------------------------
void com_slalom_turn( int t_mode ){
  control_mode = 0;                       // p¨§Œä–³‚µ
  step_r = 0;                               //‰EƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
  step_l = 0;                               //¶ƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
  STEP = 0;                               // ‹——£ƒJƒEƒ“ƒ^ƒNƒŠƒA
  rdir = 0; ldir = 0;                     // ‰ñ“]•ûŒü‚ğ’¼i
  if( t_mode == 0 ) {
    speed = GSPEEDvar;
    while( speed > speed_now );
    speed = speed_now;
    while( step_r < SLALOM_STEP_FORWARD && F_SEN < F_REF - 500 || R_SEN > R_LIM );
    control_mode = 2;           // ƒXƒ‰ƒ[ƒ€—pp¨§Œä
    step_r = 0;                               //‰EƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
    step_l = 0;                               //¶ƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
    STEP = 0;                               // ‹——£ƒJƒEƒ“ƒ^ƒNƒŠƒA
    while( step_l < SLALOM_STEP_OUT );
  }
  else if( t_mode == 1 ) {
    speed = GSPEEDvar;
    while( speed > speed_now );
    speed = speed_now;
    while( step_l < SLALOM_STEP_FORWARD && F_SEN < F_REF - 500 || L_SEN > L_LIM );
    control_mode = 3;           // ƒXƒ‰ƒ[ƒ€—pp¨§Œä
    step_r = 0;                               //‰EƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
    step_l = 0;                               //¶ƒXƒeƒbƒv”‚ğƒŠƒZƒbƒg
    STEP = 0;                               // ‹——£ƒJƒEƒ“ƒ^ƒNƒŠƒA
    while( step_r < SLALOM_STEP_OUT );
  }
  //else if( t_mode == 2 ) { T_STEP *= 2; rdir = 1; ldir = 0; }
  //else if( t_mode == 3 ) { T_STEP *= 2; rdir = 0; ldir = 1; }
}

void com_back( int n )
{
  control_mode = 0;
  STEP = 0;
  rdir = 1; ldir = 1;
  R_SW = LED_OFF;
  L_SW = LED_OFF;
  F_SW = LED_OFF;
  speed = KBAT_BACK_SPEED;
  while( speed > speed_now );
  speed = speed_now;
  while( STEP < BACK_STEP );
  speed = 10;
  while( STEP < BACK_STEP * n );
  R_SW = LED_ON;
  L_SW = LED_ON;
  F_SW = LED_ON;
}

void com_go_half( int n )
{
  control_mode = 0;
  STEP = 0;
  rdir = 0; ldir = 0;
  speed = KBAT_HALF_SPEED;
  while( speed > speed_now );
  speed = speed_now;
  while( STEP < HALF_STEP * n - speed_now * 2 );
  speed = 1;
  while( STEP < HALF_STEP * n );
}

void kbat_r( void )
{
  com_stop();
  com_back( 1 );
  com_stop();
  com_go_half( 1 );
}

void kbat_lf_turn( void )
{
  int kabe;
  kabe = search_left_hand();
  switch( kabe ){
    case 0:
    case 1:
      com_stop();
      com_turn( 0 );
      com_stop();
      com_back( 1 );
      com_stop();
      com_go_half( 1 );
      com_stop();
      com_turn( 0 );
      break;
    case 2:
      com_stop();
      com_turn( 0 );
      com_stop();
      com_back( 1 );
      com_stop();
      com_go_half( 1 );
      com_stop();
      com_turn( 0 );
      com_stop();
      com_back( 1 );
      com_stop();
      com_go_half( 1 );
      break;
    default :
      if( F_SEN > F_LIM ){
        com_turn( 2 );
        com_stop();
        com_back( 1 );
        com_stop();
        com_go_half( 1 );
        com_stop();
      }else{
        com_turn( 2 );
      }
  }
}

void goal_kbat_turn( void )
{
  if( F_SEN > F_LIM ){
    if( R_SEN > R_LIM ){
      com_stop();
      com_turn( 1 );
      com_stop();
      com_back( 1 );
      com_stop();
      com_go_half( 1 );
      com_stop();
      com_turn( 1 );
      com_stop();
      com_back( 1 );
      com_stop();
      com_go_half( 1 );
    }else if( L_SEN > L_LIM ){
      com_stop();
      com_turn( 0 );
      com_stop();
      com_back( 1 );
      com_stop();
      com_go_half( 1 );
      com_stop();
      com_turn( 0 );
      com_stop();
      com_back( 1 );
      com_stop();
      com_go_half( 1 );
    }else{
      com_turn( 3 );
      kbat_r();
    }
  }else{
    if( R_SEN > R_LIM ){
      com_stop();
      com_turn( 1 );
      com_stop();
      com_back( 1 );
      com_stop();
      com_go_half( 1 );
      com_stop();
      com_turn( 1 );
    }else if( L_SEN > L_LIM ){
      com_stop();
      com_turn( 0 );
      com_stop();
      com_back( 1 );
      com_stop();
      com_go_half( 1 );
      com_stop();
      com_turn( 0 );
    }else{
      com_turn( 3 );
    }
  }
  com_stop();
}


static void start_back_wall_contact( void )
{
  com_stop();
  com_back( 1 );
  com_stop();
  //com_go_half( 1 );
  //com_stop();
}
//-------------------------------------------------------------------------
//  ƒJƒEƒ“ƒgƒ_ƒEƒ“ 
//-------------------------------------------------------------------------
void countdown( void )
{
  beep( BEEP_MUTE, 850 );
  beep( BEEP_C5, 150 );
  beep( BEEP_MUTE, 850 );
  
  R_SW = LED_OFF;        // ‰EƒZƒ“ƒTOFF
  L_SW = LED_OFF;        // ¶ƒZƒ“ƒTOFF
  F_SW = LED_OFF;        // ‘OƒZƒ“ƒTOFF
  beep( BEEP_C5, 150 );
  beep( BEEP_MUTE, 850 );
  R_SW = LED_ON;         // ‰EƒZƒ“ƒTON
  L_SW = LED_ON;         // ¶ƒZƒ“ƒTON
  F_SW = LED_ON;         // ‘OƒZƒ“ƒTON
  beep( BEEP_C6, 1000 );
}
//-------------------------------------------------------------------------
//  ƒS[ƒ‹‰¹ 
//-------------------------------------------------------------------------
void finish( void )
{
  update_wall_ref_from_log();
  beep( BEEP_G5, 150 );
  beep( BEEP_MUTE, 150 );
  beep( BEEP_G5, 150 );
  beep( BEEP_MUTE, 50 );
  beep( BEEP_C6, 500);
}
//-------------------------------------------------------------------------
// MAPƒf[ƒ^‚ğDataFlash‚Ö‘‚İ   
// MAPƒf[ƒ^‚ÌŒ©•û:map[ pos_x ][ pos_y ] ‰½ŒÂ–Ú‚ÌMAP‚É‚·‚é‚©:no
//-------------------------------------------------------------------------
void map_writeDF(short no)
{
  int i, x, y;
  unsigned short sdata[128];		// map•Û‘¶—p
  
	// map‚©‚ç•Û‘¶—psdata‚Éƒf[ƒ^‚ğˆÚ“®
  i = 0;
  for(x = 0; x < 16; x++){
    for(y = 0; y < 16; y+=2){
      sdata[i] = ((map[x][y] << 8)&0xff00) | (map[x][y+1]&0x00ff);	// mapƒf[ƒ^‚ÌˆÚ“®
      i++;
    }
  }
	// mapƒf[ƒ^•Û‘¶ 128byte‚Ã‚Â 2byte(short)x64
  DFlash_bprog(no, &sdata[0]);
  DFlash_bprog(no+1, &sdata[64]);
}

//-------------------------------------------------------------------------
// MAPƒf[ƒ^‚ğDataFlash‚©‚ç“Ço‚µ   2/1
// MAPƒf[ƒ^‚ÌŒ©•û:map[ pos_x ][ pos_y ] ‰½ŒÂ–Ú‚ÌMAP‚©:no
//-------------------------------------------------------------------------
void map_DFread(short no)
{
  int i, x, y;
  unsigned short sdata[128];		// map•Û‘¶—p

	// mapƒf[ƒ^‚ğ“Ço‚µ
  DFlash_bread(no ,&sdata[0]) ;
  DFlash_bread(no+1 ,&sdata[64]);

	// “Ç‚İ‚¾‚µ‚½ƒf[ƒ^‚ğmap‚Ö–ß‚·
  i = 0;
  for(x = 0; x < 16; x++){
    for(y = 0; y < 16; y+=2){
      map[x][y]   = (sdata[i] >> 8)&0x00ff;
      map[x][y+1] = (sdata[i])&0x00ff;
      i++;
    }
  }

}

//-------------------------------------------------------------------------
//  Sensor reference persistence
//-------------------------------------------------------------------------
void sensor_ref_writeDF(void)
{
  unsigned short data[64] = {0};
  data[0] = SENSOR_DATA_MAGIC;
  data[1] = SENSOR_DATA_VERSION;
  data[2] = (unsigned short)L_REF;
  data[3] = (unsigned short)R_REF;
  data[4] = (unsigned short)F_REF;
  DFlash_bprog(SDATA_BK, data);
}

void sensor_ref_readDF(void)
{
  unsigned short data[64];
  DFlash_bread(SDATA_BK, data);
  if( data[0] != SENSOR_DATA_MAGIC || data[1] != SENSOR_DATA_VERSION )
    return;
  L_REF = (short)data[2];
  R_REF = (short)data[3];
  F_REF = (short)data[4];
}

//-------------------------------------------------------------------------
//  Slalom step persistence
//-------------------------------------------------------------------------
void slalom_step_writeDF(void)
{
  unsigned short data[64] = {0};
  int i;
  data[0] = SLALOM_DATA_MAGIC;
  data[1] = SLALOM_DATA_VERSION;
  data[2] = (unsigned short)GSPEED_LEVELS;
  for( i = 0; i < GSPEED_LEVELS; i++ ){
    data[3 + (i * 2)] = (unsigned short)slalom_step_forward_table[ i ];
    data[4 + (i * 2)] = (unsigned short)slalom_step_out_table[ i ];
  }
  for( i = 0; i < GSPEED_LEVELS; i++ ){
    data[3 + (GSPEED_LEVELS * 2) + i] = (unsigned short)slalom_inner_speed_table[ i ];
  }
  DFlash_bprog(SLALOMDATA_BK, data);
}

void slalom_step_readDF(void)
{
  unsigned short data[64];
  int i;
  DFlash_bread(SLALOMDATA_BK, data);
  if( data[0] != SLALOM_DATA_MAGIC )
    return;
  for( i = 0; i < GSPEED_LEVELS; i++ ){
    slalom_inner_speed_table[ i ] = 100;
  }
  if( data[1] == 0x0001 ){
    short in_val = (short)data[2];
    short out_val = (short)data[3];
    for( i = 0; i < GSPEED_LEVELS; i++ ){
      slalom_step_forward_table[ i ] = in_val;
      slalom_step_out_table[ i ] = out_val;
    }
    return;
  }
  if( data[1] != SLALOM_DATA_VERSION )
    return;
  {
    int count = (int)data[2];
    if( count < 0 ) count = 0;
    if( count > GSPEED_LEVELS ) count = GSPEED_LEVELS;
    for( i = 0; i < count; i++ ){
      slalom_step_forward_table[ i ] = (short)data[3 + (i * 2)];
      slalom_step_out_table[ i ] = (short)data[4 + (i * 2)];
    }
    for( i = 0; i < count; i++ ){
      slalom_inner_speed_table[ i ] = (short)data[3 + (GSPEED_LEVELS * 2) + i];
    }
  }
}


//-------------------------------------------------------------------------
//  Goal selection persistence
//-------------------------------------------------------------------------
void goal_choice_writeDF(void)
{
  unsigned short data[64] = {0};
  data[0] = GOAL_DATA_MAGIC;
  data[1] = GOAL_DATA_VERSION;
  data[2] = (unsigned short)goal_choice_index;
  data[3] = (unsigned short)goal_x;
  data[4] = (unsigned short)goal_y;
  DFlash_bprog(GOALDATA_BK, data);
}

void goal_choice_readDF(void)
{
  unsigned short data[64];
  DFlash_bread(GOALDATA_BK, data);
  if( data[0] != GOAL_DATA_MAGIC || data[1] != GOAL_DATA_VERSION )
    return;
  if( data[2] >= GOAL_CHOICE_COUNT )
    return;
  set_goal_choice_index( (int)data[2] );
}

//-------------------------------------------------------------------------
//  GO_STEP persistence
//-------------------------------------------------------------------------
void go_step_writeDF(void)
{
  unsigned short data[64] = {0};
  data[0] = GO_STEP_DATA_MAGIC;
  data[1] = GO_STEP_DATA_VERSION;
  data[2] = (unsigned short)GO_STEP;
  DFlash_bprog(GO_STEPDATA_BK, data);
}

void go_step_readDF(void)
{
  unsigned short data[64];
  DFlash_bread(GO_STEPDATA_BK, data);
  if( data[0] != GO_STEP_DATA_MAGIC || data[1] != GO_STEP_DATA_VERSION )
    return;
  GO_STEP = (short)data[2];
}
//-------------------------------------------------------------------------
//  FCUƒŠƒZƒbƒg  1/30
//-------------------------------------------------------------------------
void fcu_reset(void) 
{
  FLASH.FRESETR.BIT.FRESET = 1;
  pause( 2 );		// 2mS wait
  FLASH.FRESETR.BIT.FRESET = 0;
}

//-------------------------------------------------------------------------
//  FCU‚ğP/Eƒ‚[ƒh‚É‚·‚é  1/31
//-------------------------------------------------------------------------
void fcu_tope(void) 
{
  if((FLASH.FENTRYR.WORD & 0x00ff) != 0x0080){	//ƒtƒ‰ƒbƒVƒ…P/E ƒ‚[ƒhƒGƒ“ƒgƒŠƒŒƒWƒXƒ^
    FLASH.FENTRYR.WORD = 0xAA80;	//ƒL[ƒR[ƒh‚ÍAAh  P/Eƒ‚[ƒh‚É
  }
  error_check();
	//‘‚«‚İƒvƒƒeƒNƒg‰ğœ
  FLASH.FWEPROR.BYTE = 0x01;	//ƒtƒ‰ƒbƒVƒ…ƒ‰ƒCƒgƒCƒŒ[ƒYƒvƒƒeƒNƒgƒŒƒWƒXƒ^ 01FƒvƒƒOƒ‰ƒ€/ƒCƒŒ[ƒY‰Â”\
}

//-------------------------------------------------------------------------
//  FCU‚ğ“Ç‚İ‚İƒ‚[ƒh‚É‚·‚é  1/31
//-------------------------------------------------------------------------
void fcu_toread(void) 
{
  FLASH.FENTRYR.WORD = 0xAA00;		//ƒL[ƒR[ƒh‚ÍAAh  ƒŠ[ƒhƒ‚[ƒh‚É

  while(FLASH.FENTRYR.WORD & 0x00ff != 0x0000){
    FLASH.FWEPROR.BYTE = 0x02;	// 10FƒvƒƒOƒ‰ƒ€/ƒCƒŒ[ƒY•s‰Â”\
  }
}

//-------------------------------------------------------------------------
//  ƒGƒ‰[‚ğŠm”F‚µAƒGƒ‰[‚ª‚ ‚ê‚ÎC³‚·‚é  1/31
//-------------------------------------------------------------------------
void error_check(void) 
{
  int iserr = 0;
  unsigned char *addr_b;
  addr_b = (unsigned char *)(FDATA_A);	//ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…‚Ìæ“ª+Á‹ƒuƒƒbƒNƒAƒhƒŒƒX

  iserr |= FLASH.FSTATR0.BIT.ILGLERR;	//FCU‚Í•s³‚ÈƒRƒ}ƒ“ƒh‚â•s³‚âE2ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…ƒAƒNƒZƒX‚ğŒŸo
  iserr |= FLASH.FSTATR0.BIT.ERSERR;	//ƒCƒŒ[ƒX’†‚ÉƒGƒ‰[”­¶
  iserr |= FLASH.FSTATR0.BIT.PRGERR;	//ƒvƒƒOƒ‰ƒ€’†‚ÉƒGƒ‰[”­¶
  if(iserr == 0)
  {
    return;		//no error
  }

  if(FLASH.FSTATR0.BIT.ILGLERR == 1){
    if(FLASH.FASTAT.BYTE != 0x10){
      FLASH.FASTAT.BYTE = 0x10;	//ƒtƒ‰ƒO‚ğƒNƒŠƒA
    }
  }
	//ƒXƒe[ƒ^ƒXƒNƒŠƒAƒRƒ}ƒ“ƒh”­s
  *addr_b = 0x50;
}

//-------------------------------------------------------------------------
//  ƒuƒƒbƒNÁ‹ 1ƒuƒƒbƒN 128byte      1/31
//-------------------------------------------------------------------------
void clear_flash(unsigned short block) 
{
	unsigned char *addr_b;
  addr_b = (unsigned char *)(FDATA_A+block*0x80);	//ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…‚Ìæ“ª+Á‹ƒuƒƒbƒNƒAƒhƒŒƒX

  fcu_tope(); 
	//ƒuƒƒbƒN’PˆÊ‚Ì‘‚«‚İ‹–‰Â
  FLASH.DFLWE0.WORD = 0x1EFF;		//ƒL[ƒR[ƒh‚Í1Eh

  //ƒuƒƒbƒNÁ‹ƒRƒ}ƒ“ƒh”­s
  *addr_b = 0x20;
  *addr_b = 0xD0;

  wait_frdy(5);		// 5ms‘Ò‚¿‚ÍPicoƒvƒƒOƒ‰ƒ€‚©‚ç
  error_check();
  fcu_toread();
}

//-------------------------------------------------------------------------
//  FCUˆ—‘Ò‚¿  1/31
//-------------------------------------------------------------------------
void wait_frdy(int t) 
{
  int cn=0;
  while(FLASH.FSTATR0.BIT.FRDY==0){
    pause( 1 );		// 1mS wait
    cn++;
    if(cn==t){	//ƒ^ƒCƒ€ƒAƒEƒg‚¾‚Á‚½‚çƒŠƒZƒbƒg
      fcu_reset();
    }
  }
  return;
}

//-------------------------------------------------------------------------
//  ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…‰Šú‰» (ü•ÓƒNƒƒbƒN‚ğFCU‚É’Ê’m‚·‚éŠÖ”)   1/31
//-------------------------------------------------------------------------
void DFlash_init(void)
{
  short i;
  volatile unsigned char *addr_b = (unsigned char *)FDATA_A;
  volatile unsigned short *addr_w = (unsigned short *)FDATA_A;

      fcu_reset();
  //ƒNƒƒbƒN’Ê’m
  fcu_tope();		// FCU‚ğP/Eƒ‚[ƒh‚É‚·‚é
  //ü•ÓƒNƒƒbƒN‚ğİ’è
  FLASH.PCKAR.BIT.PCKA = CLOCK;

  for(i=0;i<64;i++){	//ƒuƒƒbƒN”‚Ì•ª‚¾‚¯ƒ‹[ƒv
		//ü•ÓƒNƒƒbƒN’Ê’mƒRƒ}ƒ“ƒh”­s
    *addr_b = 0xE9;
    *addr_b = 0x03;
    *addr_w = 0x0F0F;
    *addr_w = 0x0F0F;
    *addr_w = 0x0F0F;
    *addr_b = 0xD0;
    wait_frdy(2);		// 2ms‘Ò‚¿‚ÍPicoƒvƒƒOƒ‰ƒ€‚©‚ç
    fcu_reset();
    error_check();
    addr_b += 0x80;	//0x80F1BLOCK‚ÌƒTƒCƒY
    addr_w += 0x80;	//0x80F1BLOCK‚ÌƒTƒCƒY
  }

	//ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…“Ç‚İo‚µ‹–‰Â
  FLASH.DFLRE0.WORD = 0x2DFF;		//ƒL[ƒR[ƒh‚Í2Dh
  fcu_toread();		// “Ç‚İ‚İƒ‚[ƒh‚É
}

//-------------------------------------------------------------------------
//  ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…ƒƒ‚ƒŠ1ƒuƒƒbƒN(128byte)“Ço‚µ  1/31 2/1
//  “Ço‚µƒuƒƒbƒNæ“ª:block “Ço‚µƒf[ƒ^:data
//-------------------------------------------------------------------------
void DFlash_bread(unsigned short block,unsigned short *data) 
{
  short i;
  unsigned short *addr_w;
  addr_w = (unsigned short *)(FDATA_A+block*0x80);	//ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…‚Ìæ“ª+“Ço‚µƒuƒƒbƒNƒAƒhƒŒƒX
													//0x80F1BLOCK‚ÌƒTƒCƒY
	//ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…“Ç‚İo‚µ‹–‰Â
  FLASH.DFLRE0.WORD = 0x2DFF;		//ƒL[ƒR[ƒh‚Í2Dh
  fcu_toread();		// “Ç‚İ‚İƒ‚[ƒh‚É
	//ƒ}ƒbƒvƒf[ƒ^‚ğRAM‚ÉƒRƒs[
  for(i=0;i<64;i++){
    *data = *addr_w; 		// ƒf[ƒ^“Ço‚µ
    addr_w++;
    data++;
  }
}

//-------------------------------------------------------------------------
//  ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…ƒƒ‚ƒŠ1ƒuƒƒbƒN(128byte)‘‚İ  
//  ‘‚İƒuƒƒbƒNæ“ª:block ‘‚İƒf[ƒ^:data
//-------------------------------------------------------------------------
void DFlash_bprog(unsigned short block,unsigned short *data)
{
  short i;
  unsigned char *addr_b;
  unsigned short *addr_w;
  addr_b = (unsigned char *)(FDATA_A+block*0x80);	//ƒf[ƒ^ƒtƒ‰ƒbƒVƒ…‚Ìæ“ª+‘‚İƒuƒƒbƒNƒAƒhƒŒƒX
  addr_w = (unsigned short *)(FDATA_A+block*0x80);	//0x80F1BLOCK‚ÌƒTƒCƒY

	//DataFlashƒCƒŒ[ƒX
  clear_flash (block);
  fcu_tope(); 
	//DataFlash‚É‘‚İ(ƒvƒƒOƒ‰ƒ€ƒRƒ}ƒ“ƒh”­s)
  for(i=0;i<64;i++){
    *addr_b = 0xE8;
    *addr_b = 0x01;
    *addr_w = *data++;  	// ‘‚İƒf[ƒ^
    *addr_b = 0xD0;
    wait_frdy(3);		// 3ms‘Ò‚¿‚ÍPicoƒvƒƒOƒ‰ƒ€‚©‚ç
    error_check();
    addr_w++;		// ‚±‚ê‚ª”²‚¯‚Ä‚¢‚½ 2/1
  }
  fcu_toread();
}

//-------------------------------------------------------------------------
//  •Ç‚ÌƒZƒ“ƒVƒ“ƒO
//-------------------------------------------------------------------------
int get_wall_data( void )
{
  short wall;
  // ƒZƒ“ƒTƒf[ƒ^‚ğ“ü—ÍCè‡’l‚Æ”äŠr‚µ‚Ä•Ç‚Ì—L–³‚ğ”»’è
  wall = 0;
  if( F_SEN > F_LIM )  wall |= 0x01; // ‘O•Ç‚ ‚è
  if( R_SEN > R_LIM )  wall |= 0x02; // ‰E•Ç‚ ‚è
  if( L_SEN > L_LIM )  wall |= 0x08; // ¶•Ç‚ ‚è
  // Œã•Ç‚Í‚ ‚é‚í‚¯‚È‚¢‚Ì‚ÅŒ©‚È‚¢
  return( wall );
}
//-------------------------------------------------------------------------
// MAPƒf[ƒ^‚ÌŒ©•û
// ’Tõ‹L˜^ bit 7 6 5 4 = ¼ “ì “Œ –k / ’l = 1:Šù’Tõ 0:–¢’Tõ
// •Çî•ñ   bit 3 2 1 0 = ¼ “ì “Œ –k / ’l = 1:•Ç—L‚è 0:•Ç–³‚µ
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//  MAPƒf[ƒ^‰Šú‰»
//-------------------------------------------------------------------------
void clear_map( void )
{
  int x, y;
  // ‘S‚Ä‚Ì‹æŠÔ‚ğ•Ç‚È‚µ•–¢’Tõ‚É‰Šú‰»
  for( y = 0 ; y < 16 ; y++ )
    for( x = 0 ; x < 16 ; x++ )
      map[ x ][ y ] = 0x00;
  // ¼‘¤‚ÌŠO•Çix=0Cy=0`15j‚ğã‘‚«
  for( y = 0 ; y < 16 ; y++ )
    map[ 0 ][ y ] = 0x88;  // ¼‚Ì‚İŠù’Tõ(8)•¼‚Ì‚İ•Ç‚ ‚è(8)
  // “ì‘¤‚ÌŠO•Çix=0`15Cy=0j‚ğã‘‚«
  for( x = 0 ; x < 16 ; x++ )
    map[ x ][ 0 ] = 0x44;  // “ì‚Ì‚İŠù’Tõ(4)•“ì‚Ì‚İ•Ç‚ ‚è(4)
  // “Œ‘¤‚ÌŠO•Çix=15Cy=0`15j‚ğã‘‚«
  for( y = 0 ; y < 16 ; y++ )
    map[ 15 ][ y ] = 0x22; // “Œ‚Ì‚İŠù’Tõ(2)•“Œ‚Ì‚İ•Ç‚ ‚è(2)
  // –k‘¤‚ÌŠO•Çix=0`15Cy=15j‚ğã‘‚«
  for( x = 0 ; x < 16 ; x++ )
    map[ x ][ 15 ] = 0x11; // –k‚Ì‚İŠù’Tõ(1)•–k‚Ì‚İ•Ç‚ ‚è(1)
  // ƒXƒ^[ƒg‹æŠÔix=0Cy=0j‚Ìã‘‚«
  map[ 0 ][ 0 ] = 0xfe;  // ¼“ì“Œ–kŠù’Tõ(8+4+2+1=f)•¼“ì“Œ•Ç‚ ‚è(8+4+2=e)
  // ƒXƒ^[ƒg‹æŠÔ1‚Â‰Eix=1Cy=0j‚Ìã‘‚«
  map[ 1 ][ 0 ] = 0xcc;  // ¼“ìŠù’Tõ(8+4=c)•¼“ì•Ç‚ ‚è(8+4=c)
  // ¶ãŠpix=0Cy=15j‚Ìã‘‚«
  map[ 0 ][ 15 ] = 0x99; // ¼–kŠù’Tõ(8+1=9)•¼–k•Ç‚ ‚è(8+1=9)
  // ‰E‰ºŠpix=15Cy=0j‚Ìã‘‚«
  map[ 15 ][ 0 ] = 0x66; // “ì“ŒŠù’Tõ(4+2=6)•“ì“Œ•Ç‚ ‚è(4+2=6)
  // ‰EãŠpix=15Cy=15j‚Ìã‘‚«
  map[ 15 ][ 15 ] = 0x33;// “Œ–kŠù’Tõ(2+1=3)•“Œ–k•Ç‚ ‚è(2+1=3)
}
//-------------------------------------------------------------------------
//  ƒZƒ“ƒTî•ñ‚©‚ç’Tõ‹L˜^••Çî•ñ‚ğMAPƒf[ƒ^‚ÉXV
//-------------------------------------------------------------------------
void make_map_data( void )
{
  uchar wall;
  // •Çî•ñæ“¾
  wall = get_wall_data();
  // •ûŒü‡‚í‚¹ˆ—‚Ì‚½‚ß‚ÉãˆÊ4bit‚É‰ºˆÊ4bit‚Ì•Çî•ñ‚ğƒRƒs[
  wall = ( wall & 0x0f ) | ( wall << 4 );
  // ƒ}ƒEƒX‚Ìis•ûŒü‚É‚ ‚í‚¹‚Ä•Çƒf[ƒ^‚ğ‰ÁH
  if     ( head == 1 ) wall = wall >> 3; // –k‚ª‘O‚Ìî•ñ‚ğ“Œ‚ª‘O‚É‰ÁH
  else if( head == 2 ) wall = wall >> 2; // –k‚ª‘O‚Ìî•ñ‚ğ“ì‚ª‘O‚É‰ÁH
  else if( head == 3 ) wall = wall >> 1; // –k‚ª‘O‚Ìî•ñ‚ğ¼‚ª‘O‚É‰ÁH
  // ¼“ì“Œ–k‚ğ’TõÏ‚İ‚É‚·‚é
  wall |= 0xf0;
  // •Çî•ñ‚ğMAPƒf[ƒ^‚Éã‘‚«
  map[ pos_x ][ pos_y ] = wall;
  // ¼“ì“Œ–k‚Ì—×‹æ‰æ‚ÌMAPƒf[ƒ^‚ğã‘‚«
  // Œ»İ‹æ‰æ‚Ì“Œ•Çî•ñ‚ğ1‚Â‰E‹æ‰æ‚Ì¼•Çî•ñ‚Æ‚µ‚Äã‘‚«‚·‚éˆ—
  // ‚±‚±‚¾‚¯Ú×‚Éà–¾Dc‚è3‚Âi‰ºC¶Cãj‚Í‚Ü‚Æ‚ß‚Ä‹Lq
  if( pos_x != 15 ){  // ˆê”Ô“Œ‘¤‚Ì‹æ‰æ‚ÌˆÈŠO
    // ‰E‹æ‰æ‚Ì¼‘¤î•ñi’Tõ‹L˜^••Çî•ñj‚ğÁ‹
    map[ pos_x + 1 ][ pos_y ] &= 0x77;
    // ‰E‹æ‰æ‚Ì¼‘¤’Tõ‹L˜^‚ğŠù’Tõ‚Æ‚·‚é
    map[ pos_x + 1 ][ pos_y ] |= 0x80;
    // Œ»İ‹æ‰æ‚Ì“Œ‘¤î•ñ‚ğ¼‘¤î•ñ‚É•ÏŠ·‚µ‚Ä‰E‹æ‰æ‚Ì¼‘¤•Çî•ñ‚Éã‘‚«
    map[ pos_x + 1 ][ pos_y ] |= ( map[ pos_x ][ pos_y ] << 2 ) & 0x08;
  }
  
  // Œ»İ‹æ‰æ‚Ì“ì•Çî•ñ‚ğ1‚Â‰º‹æ‰æ‚Ì–k•Çî•ñ‚Æ‚µ‚Äã‘‚«‚·‚éˆ—
  if(pos_y!=0) map[pos_x][pos_y-1]=(map[pos_x][pos_y-1]&0xee)|0x10|((wall>>2)&0x01);
  // Œ»İ‹æ‰æ‚Ì¼•Çî•ñ‚ğ1‚Â¶‹æ‰æ‚Ì“Œ•Çî•ñ‚Æ‚µ‚Äã‘‚«‚·‚éˆ—
  if(pos_x!=0) map[pos_x-1][pos_y]=(map[pos_x-1][pos_y]&0xdd)|0x20|((wall>>2)&0x02);
  // Œ»İ‹æ‰æ‚Ì–k•Çî•ñ‚ğ1‚Âã‹æ‰æ‚Ì“ì•Çî•ñ‚Æ‚µ‚Äã‘‚«‚·‚éˆ—
  if(pos_y!=15)map[pos_x][pos_y+1]=(map[pos_x][pos_y+1]&0xbb)|0x40|((wall<<2)&0x04);
}
//-------------------------------------------------------------------------
//  “™‚üiƒ|ƒeƒ“ƒVƒƒƒ‹êjì¬
//-------------------------------------------------------------------------
void make_potential( int gx, int gy, int mode )
{
  uchar check_num, flg;
  uchar x,y;
  // ƒ|ƒeƒ“ƒVƒƒƒ‹MAP‰Šú‰»(‘S‚ÄÅ‘å’l255‚É‚·‚é)
  for( y = 0 ; y < 16 ; y++ )
    for( x = 0 ; x < 16 ; x++ )
      p_map[ x ][ y ] = 255;
  // ƒS[ƒ‹À•W‚Éƒ|ƒeƒ“ƒVƒƒƒ‹0‚ğ‘‚«‚Ş
  p_map[ gx ][ gy ] = 0;
  check_num = 0;
  do{
    flg = 0;  // •ÏXƒtƒ‰ƒO‰Šú‰»
    for( y = 0 ; y < 16 ; y++ ){
      for( x = 0 ; x < 16 ; x++ ){
        if( p_map[ x ][ y ] == check_num ){  // ¡‰ñ‘ÎÛ‹æ‰æ‚Æ‚·‚éƒ|ƒeƒ“ƒVƒƒƒ‹
          if( mode == S_MODE ){
            // ’Tõ‘–s(Search Mode)
            // –k‘¤‚Ì•Ç‚ª‚È‚¢ê‡F–k‘¤‚Ìƒ|ƒeƒ“ƒVƒƒƒ‹‚ğ‘ÎÛ‹æ‰æ‚Ìƒ|ƒeƒ“ƒVƒƒƒ‹‚æ‚è+1
            if((( map[ x ][ y ] & 0x01 ) == 0 ) && ( y != 15 )){
              if( p_map[ x ][ y + 1 ] == 255 ){// ‚Ü‚¾ƒ|ƒeƒ“ƒVƒƒƒ‹‚ğ‘‚¢‚Ä‚È‚¯‚ê‚Î
                p_map[ x ][ y + 1 ] = check_num + 1;
                flg = 1;  // •ÏX‚µ‚½‚Ì‚Åƒtƒ‰ƒOON
              }
            }
            // “Œ‘¤‚Ì•Ç‚à“¯—l‚Éˆ—
            if((( map[ x ][ y ] & 0x02 ) == 0 ) && ( x != 15 ))
              if(p_map[x+1][y]==255){p_map[x+1][y]=check_num+1;flg=1;}
            // “ì‘¤‚Ì•Ç‚à“¯—l‚Éˆ—
            if((( map[ x ][ y ] & 0x04 ) == 0 ) && ( y != 0 ))
              if(p_map[x][y-1]==255){p_map[x][y-1]=check_num+1;flg=1;}
            // ¼‘¤‚Ì•Ç‚à“¯—l‚Éˆ—
            if((( map[ x ][ y ] & 0x08 ) == 0 ) && ( x != 0 ))
              if(p_map[x-1][y]==255){p_map[x-1][y]=check_num+1;flg=1;}
          }else{
           // “ñŸ‘–s(Try Mode)
           // –k‘¤‚ª•Ç‚È‚µ•Šù’Tõ‚Ìê‡(•Ç‚È‚µ‚Å‚à–¢’Tõ‚Íƒ|ƒeƒ“ƒVƒƒƒ‹255‚Ì‚Ü‚Ü)
            // –k‘¤‚Ìƒ|ƒeƒ“ƒVƒƒƒ‹‚ğ‘ÎÛ‹æ‰æ‚Ìƒ|ƒeƒ“ƒVƒƒƒ‹‚æ‚è+1
            if((( map[ x ][ y ] & 0x11 ) == 0x10 ) && ( y != 15 )){
              if( p_map[ x ][ y + 1 ] == 255 ){// ‚Ü‚¾ƒ|ƒeƒ“ƒVƒƒƒ‹‚ğ‘‚¢‚Ä‚È‚¯‚ê‚Î
                p_map[ x ][ y + 1 ] = check_num + 1;
                flg = 1;  // •ÏX‚µ‚½‚Ì‚Åƒtƒ‰ƒOON
              }
            }
            // “Œ‘¤‚Ì•Ç‚à“¯—l‚Éˆ—
            if((( map[ x ][ y ] & 0x22 ) == 0x20 ) && ( x != 15 ))
              if(p_map[x+1][y]==255){p_map[x+1][y]=check_num+1;flg=1;}
            // “ì‘¤‚Ì•Ç‚à“¯—l‚Éˆ—
            if((( map[ x ][ y ] & 0x44 ) == 0x40 ) && ( y != 0 ))
              if(p_map[x][y-1]==255){p_map[x][y-1]=check_num+1;flg=1;}
            // ¼‘¤‚Ì•Ç‚à“¯—l‚Éˆ—
            if((( map[ x ][ y ] & 0x88 ) == 0x80 ) && ( x != 0 ))
              if(p_map[x-1][y]==255){p_map[x-1][y]=check_num+1;flg=1;}
          }
        }
      }
    }
    check_num++;      // Ÿ‚Ìƒ‹[ƒv‚Ì‚½‚ß‚É‘ÎÛƒ|ƒeƒ“ƒVƒƒƒ‹‚ğ+1
  }while( flg != 0 ); // ¡‰ñ‚Ìƒ‹[ƒv‚Å•ÏX‰ÓŠ‚ª–³‚¯‚ê‚Îì¬Š®—¹
}
//-------------------------------------------------------------------------
//  ’TõF¶è–@
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//  ’TõFŠg’£¶è–@
//-------------------------------------------------------------------------
int search_left_hand( void ){
  short wall_data, motion;

  wall_data = get_wall_data();  // •Çî•ñæ“¾

  switch( wall_data ){
    case  0x00  : motion = 3; break;  // ¶‚É•Ç‚È‚µ:¶Ü
    case  0x01  : motion = 3; break;  // ¶‚É•Ç‚È‚µ:¶Ü
    case  0x02  : motion = 3; break;  // ¶‚É•Ç‚È‚µ:¶Ü
    case  0x03  : motion = 3; break;  // ¶‚É•Ç‚È‚µ:¶Ü
    case  0x04  : motion = 3; break;  // ¶‚É•Ç‚È‚µ:¶Ü
    case  0x05  : motion = 3; break;  // ¶‚É•Ç‚È‚µ:¶Ü
    case  0x06  : motion = 3; break;  // ¶‚É•Ç‚È‚µ:¶Ü
    case  0x07  : motion = 3; break;  // ¶‚É•Ç‚È‚µ:¶Ü
    case  0x08  : motion = 0; break;  // ¶‚É•Ç,‘O‚É•Ç‚È‚µ:’¼i
    case  0x09  : motion = 1; break;  // ¶‚É•Ç,‘O‚É•Ç,‰E‚É•Ç‚È‚µ:‰EÜ
    case  0x0a  : motion = 0; break;  // ¶‚É•Ç,‘O‚É•Ç‚È‚µ:’¼i
    case  0x0b  : motion = 2; break;  // ¶‚É•Ç,‘O‚É•Ç,‰E‚É•Ç:”½“]
    default     : motion = 4; break;  // Œã‚ë‚É•Ç:‚ ‚è“¾‚È‚¢‚Ì‚Å’â~
  }
  return( motion );
}

//-------------------------------------------------------------------------
//  ’TõF‘«—§–@
//-------------------------------------------------------------------------
int search_adachi( void )
{
  uchar wall_data, motion;
  short val, min_val;
  const short straight_priority = 2;     // Straight priority bonus
  const short unvisited_priority = 1;    // Exploration bonus
  // Œ»İ‹æ‰æ‚Ì•Çî•ñæ“¾
  wall_data = map[ pos_x ][ pos_y ];
  // ŒvZ‚³‚ê‚é—Dæ“x‚ÌÅ‘å’l‚ğ‰Šú’l‚Éİ’è
  min_val = 1025;  // ‹æ‰æƒ|ƒeƒ“ƒVƒƒƒ‹Å‘å’l+1 255*4+4 +1 =1025
  // üˆÍ‚S‚Â‚Ì•ûŒü‚É‘Î‚µ‚Ä—Dæ“x‚ğŒvZ‚µC
  // ˆê”Ô—Dæ“x‚ª‚‚¢i’l‚ª¬‚³‚¢j‹æ‰æ‚ÉˆÚ“®‚·‚éD
  // —Dæ“x‚Íƒ|ƒeƒ“ƒVƒƒƒ‹C’¼iC–¢^Šù’Tõ‚Ì‡D
  // —áFƒ|ƒeƒ“ƒVƒƒƒ‹‚ª0‚Ìê‡Šî–{—Dæ“x‚Í0*4+4=4
  // ¦’¼i‚È‚ç-2C–¢’Tõ‚È‚ç-1‚ÌŒ¸Z•û®
  // 1:–¢’Tõ•’¼i
  // 2:Šù’Tõ•’¼i
  // 3:–¢’Tõ•’¼iˆÈŠO
  // 4:Šù’Tõ•’¼iˆÈŠO
  // —Dæ“x‚ª“¯‚¶Œ‹‰Ê‚Ìê‡‚Í–k“Œ“ì¼‚Ì‡‚É—Dæ‚³‚ê‚é
  // –k•ûŒü‚Ì—Dæ“x‚ÌŒvZ
  if(( wall_data & 0x01 ) == 0 && pos_y < 15 ){     // –k•ûŒü‚É•Ç‚ª–³‚¢‚Æ‚«
    // 1.ƒ|ƒeƒ“ƒVƒƒƒ‹‚ğŒ³‚ÉŠî–{—Dæ“x‚ğŒvZ
    val = p_map[ pos_x ][ pos_y + 1 ] * 4 + 4;
    // 2.•ûŒü‚É‚æ‚é—Dæ“x‚ÌŒvZ
    // –k•ûŒü‚ªis•ûŒü‚¾‚Á‚½ê‡F-1(—Dæ“x‚ğ1ã‚°‚é)
    if( head == 0 )  val -= straight_priority;
    // 3.–¢’Tõ^Šù’Tõ‚É‚æ‚é—Dæ“x‚ÌŒvZ
    // –¢’Tõ:-2(—Dæ“x‚ğ2ã‚°‚é)CŠù’Tõ:0
    if(( map[ pos_x ][ pos_y + 1 ] & 0xf0 ) != 0xf0 )  val -= unvisited_priority;
    // Å¬’l‚ÌXV
    if( val < min_val ){
      min_val = val;
      motion = 0;  // ˆÚ“®‚·‚×‚«•ûŒü‚ğ–k‚Éİ’è
    }
  }
  // “Œ•ûŒü‚Ì—Dæ“x‚ÌŒvZ
  if(( wall_data & 0x02 ) == 0 && pos_x < 15 ){     // “Œ•ûŒü‚É•Ç‚ª–³‚¢‚Æ‚«
    val = p_map[ pos_x + 1 ][ pos_y ] * 4 + 4;
    if( head == 1 )  val -= straight_priority;
    if(( map[ pos_x + 1 ][ pos_y ] & 0xf0 ) != 0xf0 )  val -= unvisited_priority;
    if( val < min_val ){
      min_val = val;
      motion = 1;  // ˆÚ“®‚·‚×‚«•ûŒü‚ğ“Œ‚Éİ’è
    }
  }
  // “ì•ûŒü‚Ì—Dæ“x‚ÌŒvZ
  if(( wall_data & 0x04 ) == 0 && pos_y > 0 ){     // “ì•ûŒü‚É•Ç‚ª–³‚¢‚Æ‚«
    val = p_map[ pos_x ][ pos_y - 1 ] * 4 + 4;
    if( head == 2 )  val -= straight_priority;
    if(( map[ pos_x ][ pos_y - 1 ] & 0xf0 ) != 0xf0 )  val -= unvisited_priority;
    if( val < min_val ){
      min_val = val;
      motion = 2;  // ˆÚ“®‚·‚×‚«•ûŒü‚ğ“ì‚Éİ’è
    }
  }
  // ¼•ûŒü‚Ì—Dæ“x‚ÌŒvZ
  if(( wall_data & 0x08 ) == 0 && pos_x > 0 ){     // ¼•ûŒü‚É•Ç‚ª–³‚¢‚Æ‚«
    val = p_map[ pos_x - 1 ][ pos_y ] * 4 + 4;
    if( head == 3 )  val -= straight_priority;
    if(( map[ pos_x - 1 ][ pos_y ] & 0xf0 ) != 0xf0 )  val -= unvisited_priority;
    if( val < min_val ){
      min_val = val;
      motion = 3;  // ˆÚ“®‚·‚×‚«•ûŒü‚ğ¼‚Éİ’è
    }
  }
  // ˆÚ“®‚·‚×‚«•ûŒü‚©‚çs“®‚ğŒˆ’è
  motion = ( motion - head ) & 0x03;
  return( motion );
}
#ifdef __cplusplus
void abort(void)
{
}
#endif
