#include <machine.h>
#include "sciDrv.h"
#include "vect.h"

//�O���[�o���ϐ��錾
extern int DISTANCE;
extern unsigned short TEMPERATURE;

void setup();

void main() {
	setup();
	while(1);
}

// ������
void setup() {
	init_DA();
	init_TPU2();
	init_CMT2();
	setpsw_i();
}

// CMT����
void Excep_CMT1_CMI1(void){

}

// CMT����
int i = 0;
void Excep_CMT2_CMI2(void) {
	if (0 <= i && i < 10) {
		set_DA0(512);
	} else if (10 <= i && i < 20){
		set_DA0(1023);
	}
	if (++i == 20) {
		i = 0;
	}
}
