#include "vect.h"

// you have to init IRQ1
unsigned char ACCELL_SWITCH = 0;
void Excep_ICU_IRQ1(void) {
	ACCELL_SWITCH = 1;
}
