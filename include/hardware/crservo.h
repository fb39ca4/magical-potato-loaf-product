#pragma once
#include <stdint.h>
#include <Servo.h>

namespace hardware {

class ContinuousRotationServo {
public:
ContinuousRotationServo(uint8_t pin, bool reversed);
	void setPower(int16_t power);
	void stop();

private:
	uint8_t m_pin;
	Servo servo;
	bool m_reversed;
};

}