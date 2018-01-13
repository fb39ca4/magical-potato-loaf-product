#include <bridgecontroller.h>
#include <Arduino.h>

BridgeController::BridgeController(BridgeActuator& actuator, hardware::Switch& switchN, hardware::Switch& switchE, hardware::Switch& switchS, hardware::Switch& switchW) : m_actuator(actuator), m_switchN(switchN), m_switchE(switchE), m_switchS(switchS), m_switchW(switchW) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m_stateVector[i][j] < 0;
		}
	}
	m_boatAttempts = 0;
	return;
}


void swapDir(Direction *i, Direction *j) {
   Direction t = *i;
   *i = *j;
   *j = t;
}

Direction BridgeController::getLikely(Direction start, int rank) {
	Direction ranking[3] = {Direction::None};
	int r = 0;
	for (int i = 1; i < 5; i++) {
		if (i == start) continue;
		ranking[r++] = (Direction)i;
	}
	if (m_stateVector[start][ranking[0]] < m_stateVector[start][ranking[1]]) {
		swapDir(&ranking[0], &ranking[1]);
	} 
	if (m_stateVector[start][ranking[1]] < m_stateVector[start][ranking[2]]) {
		swapDir(&ranking[1], &ranking[2]);
	}
	return ranking[rank];
}

void BridgeController::updateVector(Direction start, Direction end) {
	for (int i = 1; i < 5; i++) {
		m_stateVector[start][i] -= m_stateVector[start][i] >> 3;
	}
	m_stateVector[start][end] += 8;
}

void BridgeController::tick() {
		Direction boatStart = Direction::None;
		if (m_switchN.get()) {
			boatStart = Direction::North;
		}
		else if (m_switchE.get()) {
			boatStart = Direction::East;
		}
		else if (m_switchS.get()) {
			boatStart = Direction::South;
		}
		else if (m_switchW.get()) {
			boatStart = Direction::West;
		}
		if (boatStart) {
			if (m_boatTimer < millis()) {
				return;
			}
			else {
				if (m_actuator.isReady()) {
					m_actuator.boatCrossing(boatStart, getLikely(boatStart, m_boatAttempts));
					m_boatTimer = millis() + 5000;
					m_boatAttempts += 1;
					m_boatAttempts = m_boatAttempts % 3;
				}
			}
		}
		else {
			if (m_switchN.released()) {
				updateVector(Direction::North, getLikely(Direction::North, m_boatAttempts));
			}
			else if (m_switchE.released()) {
				updateVector(Direction::East, getLikely(Direction::East, m_boatAttempts));
			}
			m_boatAttempts = 0;
		} 


		if (m_pedestrianTimer < millis()) {
			return;
		}
		else {
			m_actuator.pedCrossing();
			m_pedestrianTimer = millis() + 10000;
		}
}