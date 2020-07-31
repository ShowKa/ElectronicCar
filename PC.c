#include	"iodefine.h"

// portC
#define  PC_IO_0 PORTC.PDR.BIT.B0
#define  PC_IO_1 PORTC.PDR.BIT.B1
#define  PC_IO_2 PORTC.PDR.BIT.B2
#define  PC_IO_3 PORTC.PDR.BIT.B3

#define  PC_0 PORTC.PODR.BIT.B0
#define  PC_1 PORTC.PODR.BIT.B1
#define  PC_2 PORTC.PODR.BIT.B2
#define  PC_3 PORTC.PODR.BIT.B3

init_PC() {
	PC_IO_0 = 0x01;
	PC_IO_1 = 0x01;
	PC_IO_2 = 0x01;
	PC_IO_3 = 0x01;
	PC_0 = 0x01;
	PC_1 = 0x01;
	PC_2 = 0x01;
	PC_3 = 0x01;
}


soundPRESET_MSG0() {
	PC_0 = 0x00;
	PC_1 = 0x00;
	PC_2 = 0x00;
	PC_3 = 0x00;
}

