#include <Arduino.h>
#include <Servo.h>


#include <hardware/servomotor.h>
#include <hardware/switch.h>
#include <bridgeactuator.h>
#include <bridgecontroller.h>



void setup(){
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(12, OUTPUT);
	
	hardware::Switch switchN(4, LOW);
	hardware::Switch switchE(5, LOW);
	hardware::Switch switchS(6, LOW);
	hardware::Switch switchW(7, LOW);

	hardware::ServoMotor bridgeMotorNE(8, 5);
	hardware::ServoMotor bridgeMotorSW(9, 5);

	bridgeMotorNE.setPosition(0);
	delay(2000);
	bridgeMotorSW.setPosition(0);
	delay(2000);

	BridgeActuator bridgeActuator(bridgeMotorNE, bridgeMotorSW);
	BridgeController bridgeController(bridgeActuator, switchN, switchE, switchS, switchW);
	bridgeActuator.boatCrossing(Direction::North, Direction::West);

	bool open = false;
	while (true) {
		bridgeMotorNE.tick();
		bridgeMotorSW.tick();
		bridgeActuator.tick();
		bridgeController.tick();


	
		delay(30);
	}
}

void loop() {}
