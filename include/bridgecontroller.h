#pragma once
#include <hardware/switch.h>
#include <bridgeactuator.h>

class BridgeController {
public:
	BridgeController(BridgeActuator& actuator, hardware::Switch& switchN, hardware::Switch& switchE, hardware::Switch& switchS, hardware::Switch& switchW);
	void tick();
private:
	BridgeActuator& m_actuator;
	hardware::Switch& m_switchN;
	hardware::Switch& m_switchE;
	hardware::Switch& m_switchS;
	hardware::Switch& m_switchW;

};