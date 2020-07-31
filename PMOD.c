#include	"iodefine.h"

// portC
#define  PMOD_IO_0 PORTC.PDR.BIT.B4
#define  PMOD_IO_1 PORTC.PDR.BIT.B5

#define  PMOD_0 PORTC.PODR.BIT.B4
#define  PMOD_1 PORTC.PODR.BIT.B5

init_PMOD() {
	PMOD_IO_0 = 0x01;
	PMOD_IO_1 = 0x01;
}

setDemo_PMOD() {
	PMOD_0 = 0x00;
	PMOD_1 = 0x00;
}

setStandAlone_PMOD() {
	PMOD_0 = 0x01;
	PMOD_1 = 0x00;
}

setCommand_PMOD() {
	PMOD_0 = 0x01;
	PMOD_1 = 0x01;
}