#include <bridgeactuator.h>
#include <Arduino.h>

BridgeActuator::BridgeActuator(hardware::ServoMotor& motorNE, hardware::ServoMotor& motorSW) : m_motorNE(motorNE), m_motorSW(motorSW) {
	m_bridgeNEPosition = Direction::South;
	m_bridgeSWPosition = Direction::North;
	m_waitUntil = millis();
}

bool BridgeActuator::boatCrossing(Direction in, Direction out) {
	Direction newSWPosition = Direction::None;
	Direction newNEPosition = Direction::None;
	if (in == Direction::South) {
		if (out == Direction::West) {
			newSWPosition = Direction::West;
		}
		else if (out == Direction::North) {
			newSWPosition = Direction::North;
			newNEPosition = Direction::South;
		}
		else if (out == Direction::West) {
			newSWPosition = Direction::North;
			newNEPosition = Direction::West;
		}
	}
	else if (in == Direction::West) {
		if (out == Direction::North) {
			newSWPosition = Direction::East;
			newNEPosition = Direction::South;
		}
		else if (out == Direction::East) {
			newSWPosition = Direction::East;
			newNEPosition = Direction::West;
		}
		else if (out == Direction::South) {
			newSWPosition = Direction::South;
		}
	}
	else if (in == Direction::North) {
		if (out == Direction::East) {
			newNEPosition = Direction::East;
		}
		else if (out == Direction::South) {
			newSWPosition = Direction::North;
			newNEPosition = Direction::South;
		}
		else if (out == Direction::West) {
			newNEPosition = Direction::South;
			newSWPosition = Direction::East;
		}
	}
	else if (in == Direction::East) {
		if (out == Direction::North) {
			newNEPosition = Direction::North;
		}
		else if (out == Direction::South) {
			newSWPosition = Direction::North;
			newNEPosition = Direction::West;
		}
		else if (out == Direction::West) {
			newNEPosition = Direction::West;
			newSWPosition = Direction::East;
		}
	}
	if ((m_bridgeNEPosition != newNEPosition) || (m_bridgeSWPosition != newSWPosition)) {
		m_bridgeNEPosition = newNEPosition;
		m_bridgeSWPosition = newSWPosition;
		m_state = 1;
	}
}

void BridgeActuator::tick() {
		switch (m_state) {
		case 0:
			break;

		case 1:
			warningLight(true);
			m_waitUntil = millis() + 3000;
			m_state++;
		case 2:
			if (millis() < m_waitUntil) {
				break;
			}
			m_state++;
		case 3:
			if (!setSW(m_bridgeSWPosition)) {
				break;
			}
			m_state++;
		case 4:
			if (setNE(m_bridgeNEPosition)) {
				break;
			}
			m_state++;
		case 5:
			warningLight(false);
			m_state = 0;
			break;
		}
	}