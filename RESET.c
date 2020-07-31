#include	"iodefine.h"

// portC
#define  RESET_IO PORTC.PDR.BIT.B6
#define  RESET PORTC.PODR.BIT.B6

init_RESET() {
	RESET_IO = 0x01;
}

void reset() {
	RESET = 0x01;
	delay_ms(200);
	RESET = 0x00;
	delay_ms(200);
	RESET = 0x01;
	delay_ms(80);
}
