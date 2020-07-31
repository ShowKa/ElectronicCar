/*************************************************************************
	RX63N SCI

*************************************************************************/
#include "iodefine.h"
#include "typedefine.h"

/*============================================================
	pGetChar_SCI関数

==============================================================*/
char pGetChar_SCI2()
{
	return SCI2.RDR;

}
/*============================================================
	pSendChar_SCI関数

==============================================================*/
char pSendChar_SCI2(unsigned char data)
{
	while( SCI2.SSR.BIT.TEND == 0 );
	SCI2.TDR = data;
	return 0;
}

/*============================================================
	pPrint_SCI関数
	ポーリングで文字列を送信
==============================================================*/
void pPrint_SCI2(unsigned char *string, int max_length)
{
	unsigned char er = 0;
	int i = 0;
	while( string[i] != '\0' && i < max_length ) {
		er = pSendChar_SCI2( string[i]);
		if( er != 0 ){	//エラー時はここで停止
			while(1);
		}
		i++;
	}
}

/*==============	=========================================================
	Initialize SCI 1
	TXD1: P26 RXD1: P15
	
	- SCI Mode : Asyncronous Serial Communication, BitRate: 9600bps
	- Clock Source: Onchip Baud rate Generator.SCKn Pin Clock Output Off
	- SCI Clock : PCLK/4 ( n = 1 )	
	- Data Fomat : LSB First, Length: 8bit, StopBit: 1bit, Parity: None
=======================================================================*/
void initSCI2(void)
{
	/* Enable SCI2 Module */
	MSTP(SCI2) = 0;
	
	/* Stop Communication SCI2 */
	SCI2.SCR.BIT.TE = 0;		//トランスミットイネーブルビット SCI2 Transmit Disable at setting
	SCI2.SCR.BIT.RE = 0;		//レシーブイネーブルビット SCI2 Recive Disable at setting
	SCI2.SCR.BIT.TEIE = 0;		//トランスミットエンドインタラプトイネーブルビット
	
	/* I/O PORT Setting */
	// PORT1.PDR.BYTE = 0x00;	// 不要
	PORT1.PMR.BIT.B2 = 1;		// P12/RXD2 Peripheral Module
	PORT1.PMR.BIT.B3 = 1;       // P13/TXD2 Peripheral Module
	
	/*** SCI PIN Setting ***/
	MPC.PWPR.BYTE &= ~0x80;	// Release Protect
	MPC.PWPR.BYTE |= 0x40;
	
	MPC.P12PFS.BYTE = 0x0A;  //マルチファンクションピンコントローラP726 PSELビット: 01010b TXD0 Interrupt OFF
	MPC.P13PFS.BYTE = 0x0A;  //マルチファンクションピンコントローラP726 PSELビット: 01010b RXD0 Interrupt OFF
	
	MPC.PWPR.BYTE &= ~0x40;	// Release Protect
	MPC.PWPR.BYTE |= 0x80;
	
	/* Clock Select */
	SCI2.SCR.BIT.CKE = 0;      // Clock Enable : 内蔵ボーレートジェネレータ(SCK0端子は入出力ポートとして可)
	
	/* SCI2 Module Mode Select ( all Default Value) */
	SCI2.SIMR1.BIT.IICM = 0;    // I2C Mode Select : Serial Interface Mode[default]
	SCI2.SPMR.BIT.CKPH = 0;     // Clock Phase Select : Clock Delay None
	SCI2.SPMR.BIT.CKPOL = 0;    // Clock Polarity Invert : None
	
	/* Communication Data Format Setting */

	SCI2.SMR.BIT.CKS = 0x01;   // Clock PCLK/4 n=1	( BRR )
	SCI2.SMR.BIT.MP = 0;	   // MultiProccesor communication function OFF
	SCI2.SMR.BIT.STOP = 0;     // Stop Bit : 1bit
	SCI2.SMR.BIT.PM = 0;       // Parity Mode : Even Parity
	SCI2.SMR.BIT.PE = 0;       // Parity Enable : No Parity
	SCI2.SMR.BIT.CHR = 0;      // Character Length : 8bit
	SCI2.SMR.BIT.CM = 0;     // 調歩同期式モード

	SCI2.SCMR.BIT.SMIF = 0;    // SmartCard Interface Mode Select: Serial Communication
	SCI2.SCMR.BIT.SINV = 0;    // 送受信データインバート(invert logic): Normal
	SCI2.SCMR.BIT.SDIR = 0;    // LSB First
	// SCI2.SCMR.BIT.BCP2 = 0x04;    // Basic Clock Pulse : 32 Clock for SmartCard
	
	SCI2.SEMR.BIT.ACS0 = 0;	    // Asynchronous Clock Source : external
	SCI2.SEMR.BIT.ABCS = 0;     // Asynchronous Base Clock Select : 16cycle
	SCI2.SEMR.BIT.NFEN = 0;     // Noise Filter Disable
	
	/* Bit Rate Setting */
	SCI2.BRR = 38;
	
	/* Enable SCI2 Communication */
	SCI2.SCR.BIT.TEIE = 1;     // Trancemit end interrupt Enable
	SCI2.SCR.BIT.MPIE = 0;     // MultiProcessor Interrupt Disable
	SCI2.SCR.BIT.RE = 1;       // Recive Enable
	SCI2.SCR.BIT.TE = 1;       // Transmit Enable
	SCI2.SCR.BIT.RIE = 1;      // Recive Interrupt Enable
	SCI2.SCR.BIT.TIE = 1;      // Transmit Interrupt Enable
	
	/**** SCI2 Interrupt Setting ***/
	/* SCI2 RXD Interrupt */
	IPR( SCI2, RXI2) = 10;	// Priory Level 10
	IR( SCI2, RXI2) = 0;	// clear status flag
	IEN( SCI2, RXI2) = 1;	// Enable Interrupt
}
