#include "vect.h"
#include "iodefine.h"

unsigned char SCI2_RX_DATA;
unsigned char SCI2_RX_FLAG;

void _getResponseOfTalk();

void setBaudrate() {
	pSendChar_SCI2('?');
	// _getResponseOfTalk();
}

void speech(unsigned char *words, unsigned int length) {
	// AquesTALK pico setup
	setCommand_PMOD();
	reset();
	setBaudrate();
	// speech
	pPrint_SCI2(words, length);
	pSendChar_SCI2(0x0D);
	// _getResponseOfTalk();
}

void chime_J() {
	pPrint_SCI2("#J", 2);
	pSendChar_SCI2(0x0D);
	// _getResponseOfTalk();
}

void chime_K() {
	pPrint_SCI2("#K", 2);
	pSendChar_SCI2(0x0D);
	// _getResponseOfTalk();
}

unsigned char RESPONSE_OF_TALK[10];

void _getResponseOfTalk() {
	int i = 0, a = 0;
	for (a = 0; a < 10; a++) {
		RESPONSE_OF_TALK[a] = 0x00;
	}
	while (1) {
		if (SCI2_RX_FLAG == 1) {
			unsigned char data = SCI2_RX_DATA;
			SCI2_RX_FLAG = 0;
			if (data == '>' || data == '*') {
				return;
			} else {
				RESPONSE_OF_TALK[i] = data;
				i++;
				if (i == 10) {
					break;
				}
			}
		}
	}
}

// 
void Excep_SCI2_RXI2(void) {
	SCI2_RX_DATA = SCI2.RDR;
	SCI2_RX_FLAG = 1;	
}