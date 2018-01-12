#pragma once

#include <hardware/servomotor.h>


class BridgeActuator {
public:

	enum Direction {
		None = 0,
		North = 1,
		East = 2,
		South = 3,
		West = 4
	};
private:
	hardware::ServoMotor& m_motorNE;
	hardware::ServoMotor& m_motorSW;
	Direction m_bridgeNEPosition;
	Direction m_bridgeSWPosition;
	bool m_pedNS = true;
	int m_state = 0;
	unsigned long m_waitUntil;
public:
	BridgeActuator(hardware::ServoMotor& motorNE, hardware::ServoMotor& motorSW);
	bool boatCrossing(Direction in, Direction out);
	bool isReady() {
		return m_state == 0;
	}
	bool setSW(Direction dir) {
		return true;
	}
	bool setNE(Direction dir) {
		return true;
	}
	void warningLight(bool on) {
		return;
	}
	void tick();
};