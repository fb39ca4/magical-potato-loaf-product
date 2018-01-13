#include <bridgecontroller.h>
#include <Arduino.h>

BridgeController::BridgeController(BridgeActuator& actuator, hardware::Switch& switchN, hardware::Switch& switchE, hardware::Switch& switchS, hardware::Switch& switchW, hardware::Switch& switchPed) : m_actuator(actuator), m_switchN(switchN), m_switchE(switchE), m_switchS(switchS), m_switchW(switchW), m_switchPed(switchPed) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m_stateVector[i][j] = 0;
		}
	}
	m_boatAttempts = 0;
	m_boatTimer = millis();
	return;
}

const char* dir(Direction d) {
	switch (d) {
		case Direction::None:
			return "None";
		case Direction::North:
			return "North";
		case Direction::East:
			return "East";
		case Direction::South:
			return "South";
		case Direction::West:
			return "West";
	}
}

void swapDir(Direction* list, int i, int j) {
	Direction t = list[i];
	list[i] = list[j];
	list[j] = list[t];
}

Direction BridgeController::getLikely(Direction start, int rank) {
	Direction ranking[3] = {Direction::None};
	int r = 0;
	for (int i = 1; i < 5; i++) {
		if (i == start) i++;
		ranking[r++] = (Direction)i;
	}
	if (m_stateVector[start][ranking[0]] < m_stateVector[start][ranking[1]]) {
		swapDir(ranking, 0, 1);
	}
	if (m_stateVector[start][ranking[1]] < m_stateVector[start][ranking[2]]) {
		swapDir(ranking, 1, 2);
	}
	if (m_stateVector[start][ranking[0]] < m_stateVector[start][ranking[1]]) {
		swapDir(ranking, 0, 1);
	}
	if (m_stateVector[start][ranking[1]] < m_stateVector[start][ranking[2]]) {
		swapDir(ranking, 1, 2);
	}
	return ranking[rank];
}

void BridgeController::updateVector(Direction start, Direction end) {
	for (int i = 1; i < 5; i++) {
		m_stateVector[start][i] -= m_stateVector[start][i] >> 2;
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
		if (m_boatTimer > millis()) {
			return;
		}
		else {
			if (m_actuator.isReady()) {
				Serial.print(dir(boatStart));
				Serial.print(" ");
				Serial.println(dir(getLikely(boatStart, m_boatAttempts)));
				m_actuator.boatCrossing(boatStart, getLikely(boatStart, m_boatAttempts));
				m_boatTimer = millis() + 5000;
				m_boatAttempts += 1;
				m_boatAttempts = m_boatAttempts % 3;
			}
			return;
		}
	}
	
	if (m_switchN.released()) {
		updateVector(Direction::North, getLikely(Direction::North, (m_boatAttempts - 1) % 3));
		Serial.print("North ");
		for (int i = 1; i < 5; i++) {
			Serial.print(m_stateVector[Direction::North][i]);
			Serial.print(" ");
		}
		Serial.println();
	}
	else if (m_switchE.released()) {
		updateVector(Direction::East, getLikely(Direction::East, (m_boatAttempts - 1) % 3));
		Serial.print("East ");
		for (int i = 1; i < 5; i++) {
			Serial.print(m_stateVector[Direction::East][i]);
			Serial.print(" ");
		}
		Serial.println();
	}
	else if (m_switchS.released()) {
		updateVector(Direction::South, getLikely(Direction::South, (m_boatAttempts - 1) % 3));
		Serial.print("South ");
		for (int i = 1; i < 5; i++) {
			Serial.print(m_stateVector[Direction::South][i]);
			Serial.print(" ");
		}
		Serial.println();
	}
	else if (m_switchW.released()) {
		updateVector(Direction::West, getLikely(Direction::West, (m_boatAttempts - 1) % 3));
		Serial.print("West ");
		for (int i = 1; i < 5; i++) {
			Serial.print(m_stateVector[Direction::West][i]);
			Serial.print(" ");
		}
		Serial.println();
	}
	m_boatAttempts = 0;

		
	if (m_switchPed.get()) {
		if (m_actuator.isReady()) {
			m_actuator.pedCrossing();
		}
	}
		
}