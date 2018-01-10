#include "hardware/lightsensor.h"
#include <Arduino.h>

namespace hardware {

LightSensor::LightSensor(uint8_t analogPin) {
	m_pin = analogPin;
	m_currentValue = analogRead(m_pin);
}

uint16_t LightSensor::get() const {
	return m_currentValue;
}

void LightSensor::tick() {
	m_currentValue = analogRead(m_pin);
}

void LightSensor::printTo(Print& p) {
	p.print(get());
}

}