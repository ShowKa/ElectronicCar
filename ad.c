#include "iodefine.h"
#include "vect.h"

// MAX 4095
// AD�ϊ����A���͂��ꂽ�����d�������o����
unsigned short AN000_DATA;

void init_AD() {
	// �ȓd�͋@�\����
	// �v���e�N�g����
	SYSTEM.PRCR.WORD = 0xA502;
	SYSTEM.MSTPCRA.BIT.MSTPA17 = 0;
	// �ăv���e�N�g
	SYSTEM.PRCR.WORD = 0xA500; 
	// PFS���̂��߂Ƀv���e�N�g����
	MPC.PWPR.BIT.B0WI = 0;
	// PFS�Fport function select ����
	MPC.PWPR.BIT.PFSWE = 1;
	// PMR:port mode register = ���Ӌ@�\�Ƃ��Ďg�p
	PORT4.PMR.BIT.B0 =1 ;
	// port40���A�i���O�Ƃ��Ďg�p
	MPC.P40PFS.BIT.ASEL = 1;
	// �v���e�N�g��߂��B
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;
	// cks �N���b�N�X�F3�͔�r�I����
	S12AD.ADCSR.BIT.CKS = 3;
	// AD�ϊ� = �V���O���X�L�����E���[�h
	S12AD.ADCSR.BIT.ADCS = 0;
	// �`���l��0��on
	S12AD.ADANS0.WORD = 0x01;
	S12AD.ADANS1.WORD = 0X00;
	// config
	// �f�[�^�̎����N���A�֎~
	S12AD.ADCER.BIT.ACE = 0;
	// ���W�X�^�F16bit���ɋl�߂�l���E�Â߂ɂ���i����0�l�߂���j
	S12AD.ADCER.BIT.ADRFMT = 0;
}
