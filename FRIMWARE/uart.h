#include "headers.h"//including necesarry header files
//function to initilise the UART0
void Init_UART0(void);
//function to Transmit charecter
void U0_TxByte(u8 );
//function to Receive character
u8 U0_RxByte(void);
//function to Transmit string 
void U0_TxStr(s8 *);
//functin to Receving the data through Interrupt
void UART0_ISR(void) __irq;

//function to initiliase UART1
void Init_UART1(void);
//function to Transmit byte
void U1_TxByte(u8 );
//function to Receive byte
u8 U1_RxByte(void);
//function to Transmit string
void U1_TxStr(s8 *);
//function to Receving the data through Interrupt
void UART1_ISR(void) __irq;
