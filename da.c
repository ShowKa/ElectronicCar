#include "iodefine.h"

// DA変換し、直流電流を出力する(最大3.3V)
void init_DA(void)
{
	//モジュールストップ機能を解除し、D/A変換を実行可能にする。(P302)
	SYSTEM.PRCR.WORD = 0xA502;
	SYSTEM.MSTPCRA.BIT.MSTPA19 = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	// 各デバイスのPFSビットに設定するため、プロテクト解除(P720)
	MPC.PWPR.BIT.B0WI = 0;	// PFSWEのプロテクション解除
	MPC.PWPR.BIT.PFSWE = 1;	// PFSレジスタへの書き込み許可
	
	// P03をアナログ端子として使用
	PORT0.PMR.BIT.B3 = 0;
	MPC.P03PFS.BIT.ASEL = 1;

	// 各デバイスのPFSビットに設定終了後の再プロテクト(P720)
	MPC.PWPR.BIT.PFSWE = 0;	// PFSレジスタへの書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;	// PFSWEの再プロテクション
	
	//DA変換データ右詰め設定(レジスタ格納時左側0パディング)
	DA.DADPR.BIT.DPSEL = 0;
	DA.DAADSCR.BIT.DAADST = 0;
	// max 1023 => 3.3V (比例）
	DA.DADR0 = 1023;
	//Enable ch0 da convert
	DA.DACR.BIT.DAOE0 = 1;	
}

set_DA0(unsigned short value) {
	DA.DADR0 = value;
}
