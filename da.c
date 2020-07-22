#include "iodefine.h"

// DA�ϊ����A�����d�����o�͂���(�ő�3.3V)
void init_DA(void)
{
	//���W���[���X�g�b�v�@�\���������AD/A�ϊ������s�\�ɂ���B(P302)
	SYSTEM.PRCR.WORD = 0xA502;
	SYSTEM.MSTPCRA.BIT.MSTPA19 = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	// �e�f�o�C�X��PFS�r�b�g�ɐݒ肷�邽�߁A�v���e�N�g����(P720)
	MPC.PWPR.BIT.B0WI = 0;	// PFSWE�̃v���e�N�V��������
	MPC.PWPR.BIT.PFSWE = 1;	// PFS���W�X�^�ւ̏������݋���
	
	// P03���A�i���O�[�q�Ƃ��Ďg�p
	PORT0.PMR.BIT.B3 = 0;
	MPC.P03PFS.BIT.ASEL = 1;

	// �e�f�o�C�X��PFS�r�b�g�ɐݒ�I����̍ăv���e�N�g(P720)
	MPC.PWPR.BIT.PFSWE = 0;	// PFS���W�X�^�ւ̏������݋֎~
	MPC.PWPR.BIT.B0WI = 1;	// PFSWE�̍ăv���e�N�V����
	
	//DA�ϊ��f�[�^�E�l�ߐݒ�(���W�X�^�i�[������0�p�f�B���O)
	DA.DADPR.BIT.DPSEL = 0;
	DA.DAADSCR.BIT.DAADST = 0;
	// max 1023 => 3.3V (���j
	DA.DADR0 = 1023;
	//Enable ch0 da convert
	DA.DACR.BIT.DAOE0 = 1;	
}

set_DA0(unsigned short value) {
	DA.DADR0 = value;
}
