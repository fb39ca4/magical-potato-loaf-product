#include "hardware/crservo.h"
 
#include <Arduino.h>

namespace hardware {

ContinuousRotationServo::ContinuousRotationServo(uint8_t pin, bool reversed) {
	m_pin = pin;
	servo.attach(pin);
	servo.write(90);
	m_reversed = reversed;
}

void ContinuousRotationServo::setPower(int16_t power) {
	if (power > 255) {
		power = 255;	
	}
	if (power < -255) {
		power = -255;
	}
	if (m_reversed) power = -power;
	power = (power * 90) / 255;
	servo.write(power + 90);
}

void ContinuousRotationServo::stop() {
	servo.write(90);
}

}