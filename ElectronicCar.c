#include <machine.h>
#include "sciDrv.h"
#include "vect.h"
#include "iodefine.h"

//グローバル変数宣言
extern int DISTANCE;
extern unsigned short TEMPERATURE;
extern unsigned short AN001_DATA;
extern unsigned char ACCELL_SWITCH;
extern unsigned char GPS_NMEA_MESSAGE[100];
extern unsigned char GPS_ERROR;

void setup();

void main() {
	setup();
	while(1);
}

// 初期化
void setup() {
	initSCI0();
	init_DA();
	init_S12AD();
	init_GPS();
	init_TPU2();
	init_TPU9();
	init_CMT0();
	init_CMT1();
	init_CMT2();
	LCD_init();
	init_US_TRIGGER();
	initIRQ();
	setpsw_i();
}

// CMT割込
void Excep_CMT1_CMI1(void){
	// reset GPS if ERROR occurred
	reset_GPS();
}

// CMT割込
void Excep_CMT2_CMI2(void) {
	static int i = 0;
	static int value;
	static char value_str[21];
	float volt = 3.3f;
	value_str[20] = 0x00;
	// set value
	if (DISTANCE < 100 || ACCELL_SWITCH == 0) {
		ACCELL_SWITCH = 0;
		value = 0;
	} else {
		value = 1023 * (AN001_DATA / 4095.0);
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
	//LCD_clear();
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
	// GPS
	value_str[0] = 'G';
	value_str[1] = 'P';
	value_str[2] = 'S';
	value_str[3] = ':';
	value_str[4] = GPS_NMEA_MESSAGE[0];
	value_str[5] = GPS_NMEA_MESSAGE[1];
	value_str[6] = GPS_NMEA_MESSAGE[2];
	value_str[7] = GPS_NMEA_MESSAGE[3];
	value_str[8] = GPS_NMEA_MESSAGE[4];
	value_str[9] = GPS_NMEA_MESSAGE[5];
	value_str[10] = GPS_NMEA_MESSAGE[6];
	value_str[11] = GPS_NMEA_MESSAGE[7];
	value_str[12] = GPS_NMEA_MESSAGE[8];
	value_str[13] = GPS_NMEA_MESSAGE[9];
	value_str[14] = GPS_NMEA_MESSAGE[10];
	value_str[15] = GPS_NMEA_MESSAGE[11];
	value_str[16] = GPS_NMEA_MESSAGE[12];
	value_str[17] = GPS_NMEA_MESSAGE[13];
	value_str[18] = GPS_NMEA_MESSAGE[14];
	value_str[19] = GPS_NMEA_MESSAGE[15];
	// LCD
	LCD_locate(1, 3);
	LCD_putstr(value_str);
	// ACCELL SWITCH
	value_str[0] = 'A';
	value_str[1] = 'C';
	value_str[2] = 'C';
	value_str[3] = 'E';
	value_str[4] = 'L';
	value_str[5] = 'L';
	value_str[6] = ':';
	value_str[7] = 'O';
	value_str[8] = ACCELL_SWITCH == 1 ? 'n' : 'f';
	value_str[9] = ACCELL_SWITCH == 1 ? ' ' : 'f';
	value_str[10] = 0x00;
	// LCD
	LCD_locate(1, 4);
	LCD_putstr(value_str);
	// index
	if (++i == 20) {
		i = 0;
	}
}
