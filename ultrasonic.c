// init TPU9, cmt0, irq0 !

#include "iodefine.h"
#include "vect.h"

int DISTANCE; //cm

init_US_TRIGGER() {
	PORT9.PDR.BIT.B0 = 0xff;
}

setTrigger(char output) {
	PORT9.PODR.BIT.B0 = output;
}

// trigger pulse: width=10us
void trigger() {
	setTrigger(1);
	delay_us(10);
	setTrigger(0);
}

// catch output Echo
void Excep_ICU_IRQ0(void){
	int span, i;
	char isStartTimer = isStart_TIMER();
	start_TPU9();
	// wait until interupted signal will be low.
	i = 0;
	while(PORTD.PIDR.BIT.B0 == 1) {
		// おおむね4メートル強でブレイクさせる。判定条件はテキトーなのでバグるかも。
		if (++i > 131072) break;
	}
	// get distance
	span = getTimeSpan_TPU9();
	DISTANCE = span / 58;
	// restart timer
	if (isStartTimer) {
		start_TIMER();
	}
}

// CMT0 割込み処理
// triggerが60us毎に実施されるようにする。
void Excep_CMT0_CMI0(void) {
	char isStartTimer = isStart_TIMER();
	trigger();
	if (isStartTimer) {
		start_TIMER();
	}
}
