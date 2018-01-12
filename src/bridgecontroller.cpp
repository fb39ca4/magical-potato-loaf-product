#include <bridgecontroller.h>

BridgeController::BridgeController(BridgeActuator& actuator, hardware::Switch& switchN, hardware::Switch& switchE, hardware::Switch& switchS, hardware::Switch& switchW) : m_actuator(actuator), m_switchN(switchN), m_switchE(switchE), m_switchS(switchS), m_switchW(switchW) {
	return;
}

void BridgeController::tick() {
	if (m_actuator.isReady()) {

	}
}