#ifndef __RX_I2C
#define __RX_I2C
#include "iodefine.h"
#include "machine.h"

extern char send_data[50];
extern char receve_data[50];
extern char receve_data_out[50];
extern int send_data_num;
extern int receve_num;
extern int stop_disen_flag;
extern int receve_flag;
extern int receve_fin_flag;
extern void init_riic0(void);
extern void int_iic0_eei(void);
extern void int_iic0_txi(void);
extern void int_iic0_rxi(void);
extern void int_iic0_tei(void);
extern int iic0_send(char*,int,int);
extern char* iic0_gets();
extern int iic0_reqest_send(char* data , int r_num,int addr);
extern int iic0_set_addr(int addr, int num);
extern int  iic0_receve(char* p_data,int n);
#endif
 
