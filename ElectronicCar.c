#include <machine.h>
#include "sciDrv.h"
#include "vect.h"

//グローバル変数宣言
extern int DISTANCE;
extern unsigned short TEMPERATURE;

void setup();

void main() {
	setup();
	while(1);
}

// 初期化
void setup() {
	init_DA();
	init_TPU2();
	init_TPU9();
	init_CMT0();
	init_CMT2();
	LCD_init();
	init_US_TRIGGER();
	initIRQ();
	setpsw_i();
}

// CMT割込
void Excep_CMT1_CMI1(void){

}

// CMT割込
int i = 0;
void Excep_CMT2_CMI2(void) {
	static int value;
	static char value_str[21];
	float volt = 3.3f;
	value_str[20] = 0x00;
	// set value
	if (DISTANCE < 100) {
		value = 0;
	} else if (0 <= i && i < 10) {
		value = 0;
		
	} else if (10 <= i && i < 20){
		value = 1023;
	}
	set_DA0(value);
	// lcd
	value_str[0] = 'D';
	value_str[1] = '/';
	value_str[2] = 'A';
	value_str[3] = ':';
	value_str[4] = value / 1000 % 10 + '0';
	value_str[5] = value / 100 % 10 + '0';
	value_str[6] = value / 10 % 10 + '0';
	value_str[7] = value / 1 % 10 + '0';
	// 電圧
	volt *= (value / 1023.0);
	value_str[8] = ':';
	value_str[9] = (int)volt % 10 + '0';
	value_str[10] = '.';
	value_str[11] = (int)(volt * 10) % 10 + '0';
	value_str[12] = 'v';
	value_str[13] = 0x00;
	// LCD
	LCD_clear();
	LCD_locate(1, 1);
	LCD_putstr(value_str);
	// 距離
	value_str[0] = 'D';
	value_str[1] = 'i';
	value_str[2] = 's';
	value_str[3] = 't';
	value_str[4] = 'a';
	value_str[5] = 'n';
	value_str[6] = 'c';
	value_str[7] = 'e';
	value_str[8] = ':';
	value_str[9] = DISTANCE / 100 % 10 + '0';
	value_str[10] = DISTANCE / 10 % 10 + '0';
	value_str[11] = DISTANCE / 1 % 10 + '0';
	value_str[12] = 'c';
	value_str[13] = 'm';
	value_str[14] = 0x00;
	// LCD
	LCD_locate(1, 2);
	LCD_putstr(value_str);
	// index
	if (++i == 20) {
		i = 0;
	}
}
