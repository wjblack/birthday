#include "DigiKeyboard.h"
#include <avr/pgmspace.h>

// 1. Deciseconds of delay before proceeding, followed by
// 2. Raw keycode to send, followed by
// 3. Processed string to send.
uint8_t messages[] = {
	10, MOD_GUI_LEFT, '\0',
	10, 0x0, 'n', 'o', 't', 'e', 'p', 'a', 'd', '\n', '\0',
	50, 0x0, 'C', 'h', 'r', 'i', 's', 't', 'i', 'a', 'n', '?', '\n', '\0',
	20, 0x0, 'C', 'h', 'r', 'i', 's', 't', 'i', 'a', 'n', '!', '\n', '\0',
	20, 0x0, 'C', 'H', 'R', 'I', 'S', 'T', 'I', 'A', 'N', '!', '!', '!', '\n', '\0',
	20, 0x0, 'H', 'A', 'P', 'P', 'Y', ' ', 'B', 'I', 'R', 'T', 'H', 'D', 'A', 'Y', ',', ' ', 'C', 'H', 'R', 'I', 'S', 'T', 'I', 'A', 'N', '!', '!', '!', '\n', '\0',
};

void flash(int num) {
	int j;
	for(j=0; j<num; j++) {
		digitalWrite(1, HIGH);
		DigiKeyboard.delay(100);
		digitalWrite(1, LOW);
		DigiKeyboard.delay(100);
	}
}

void setup() {
	int i;
	pinMode(1, OUTPUT);
	flash(2);
}

void loop() {
	int i=0;

	DigiKeyboard.sendKeyStroke(0);

	DigiKeyboard.delay(100);

	while(i<sizeof(messages)) {
		flash(1);
		DigiKeyboard.delay(100 * (int) messages[i]);
		i++;
		if(messages[i]) {
			flash(1);
			DigiKeyboard.sendKeyStroke(0, messages[i]);
		}
		i++;
		while(messages[i]) {
			DigiKeyboard.write(messages[i]);
			DigiKeyboard.delay(100);
			i++;
		}
		i++;
	}

	for(i=0; i<3600; i++) {
		digitalWrite(1, HIGH);
		DigiKeyboard.delay(1000);
		digitalWrite(1, LOW);
		DigiKeyboard.delay(1000);
	}
}
