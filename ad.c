#include "iodefine.h"
#include "vect.h"

// MAX 4095
// AD変換し、入力された直流電流を検出する
unsigned short AN000_DATA;

void init_AD() {
	// 省電力機能解除
	// プロテクト解除
	SYSTEM.PRCR.WORD = 0xA502;
	SYSTEM.MSTPCRA.BIT.MSTPA17 = 0;
	// 再プロテクト
	SYSTEM.PRCR.WORD = 0xA500; 
	// PFS許可のためにプロテクト解除
	MPC.PWPR.BIT.B0WI = 0;
	// PFS：port function select 許可
	MPC.PWPR.BIT.PFSWE = 1;
	// PMR:port mode register = 周辺機能として使用
	PORT4.PMR.BIT.B0 =1 ;
	// port40をアナログとして使用
	MPC.P40PFS.BIT.ASEL = 1;
	// プロテクトを戻す。
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;
	// cks クロックス：3は比較的高速
	S12AD.ADCSR.BIT.CKS = 3;
	// AD変換 = シングルスキャン・モード
	S12AD.ADCSR.BIT.ADCS = 0;
	// チャネル0をon
	S12AD.ADANS0.WORD = 0x01;
	S12AD.ADANS1.WORD = 0X00;
	// config
	// データの自動クリア禁止
	S12AD.ADCER.BIT.ACE = 0;
	// レジスタ：16bit幅に詰める値を右づめにする（左に0詰めする）
	S12AD.ADCER.BIT.ADRFMT = 0;
}
