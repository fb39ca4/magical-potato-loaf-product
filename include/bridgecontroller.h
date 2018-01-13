#pragma once
#include <hardware/switch.h>
#include <bridgeactuator.h>

class BridgeController {
public:
	BridgeController(BridgeActuator& actuator, hardware::Switch& switchN, hardware::Switch& switchE, hardware::Switch& switchS, hardware::Switch& switchW, hardware::Switch& switchPed);
	void tick();
	Direction getLikely(Direction start, int rank);
	void updateVector(Direction start, Direction end);
private:
	void stateScale();
	BridgeActuator& m_actuator;
	hardware::Switch& m_switchN;
	hardware::Switch& m_switchE;
	hardware::Switch& m_switchS;
	hardware::Switch& m_switchW;
	hardware::Switch& m_switchPed;
	unsigned long m_pedestrianTimer = 0;
	unsigned long m_boatTimer = 0;
	uint32_t m_stateVector[5][5];
	int m_boatAttempts = 0;
};