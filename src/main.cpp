#include <Arduino.h>

void setup(){
	pinMode(LED_BUILTIN, OUTPUT);
	while (true) {
		delay(500);
		digitalWrite(13, HIGH);
		delay(500);
		digitalWrite(13, LOW);
	}
}

void loop() {}
