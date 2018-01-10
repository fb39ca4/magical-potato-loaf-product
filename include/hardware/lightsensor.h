#pragma once
#include <stdint.h>
#include <Print.h>

namespace hardware {

class LightSensor {
public:
	LightSensor(uint8_t analogPin);
	uint16_t get() const;
	void tick();
	void printTo(Print& p);

private:
	uint8_t m_pin;
	uint16_t m_currentValue;
};

}