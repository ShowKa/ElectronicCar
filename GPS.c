#include "vect.h"
#include "iodefine.h"

/** Sentence */
// $GPGGA,085120.307,3541.1493,N,13945.3994,E,1,08,1.0,6.9,M,35.9,M,,0000*5E
unsigned char GPS_NMEA_MESSAGE[100];
unsigned char TEMP__GPS_NMEA_MESSAGE[100];
unsigned char GPS_ERROR = 0;

void init_GPS();
void Excep_SCI0_RXI0(void);
void reset_GPS();

// methods
// you have to init SCI0
void init_GPS() {
	unsigned short a;
	for (a = 0; a < 100; a++) {
		GPS_NMEA_MESSAGE[a] = '#';
	}
	GPS_ERROR = 0;
}

void Excep_SCI0_RXI0(void) {
	static unsigned short i = 0;
	unsigned char data =  SCI0.RDR;
	if (data == '$' || i > 99) {
		i = 0;
	}
	TEMP__GPS_NMEA_MESSAGE[i++] = data;
	if (data == '*') {
		unsigned short j = 0;
		unsigned char tmp  = TEMP__GPS_NMEA_MESSAGE[j];
		while (tmp != '*') {
			GPS_NMEA_MESSAGE[j++] = tmp;
			tmp = TEMP__GPS_NMEA_MESSAGE[j];
		}
		i = 0;
	}
	reset_GPS();
}

void reset_GPS() {
	// error handling
	if (SCI0.SSR.BIT.ORER != 0 || SCI0.SSR.BIT.FER != 0 || SCI0.SSR.BIT.PER != 0) {
		SCI0.SSR.BYTE = 0x00;
		initSCI0();
	}
}
