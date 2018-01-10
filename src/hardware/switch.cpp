#include "hardware/switch.h"
#include <Arduino.h>

namespace hardware {

Switch::Switch(uint8_t pin, uint8_t pressedState) {
	m_pin = pin;
	m_pressedState = pressedState;
	pinMode(pin, INPUT_PULLUP);
	m_prevState = digitalRead(pin);
	m_pressEvent = false;
	m_releaseEvent = false;
}

bool Switch::get() const {
	return digitalRead(m_pin) == m_pressedState;
}

bool Switch::pressed() const {
	return m_pressEvent;
}

bool Switch::released() const {
	return m_releaseEvent;
}

void Switch::tick() {
	bool currentState = get();

	if ((currentState == true) && (currentState != m_prevState)) {
		m_pressEvent = true;
	}
	else {
		m_pressEvent = false;
	}

	if ((currentState == false) && (currentState != m_prevState)) {
		m_releaseEvent = true;
	}
	else {
		m_releaseEvent = false;
	}
	m_prevState = currentState;
}

void Switch::printTo(Print& p) {
	p.print(get());
}

}