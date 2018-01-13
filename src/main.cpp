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
	hardware::Switch switchPed(10, LOW);
	pinMode(12, OUTPUT);
	digitalWrite(12, LOW);

	hardware::ServoMotor bridgeMotorNE(8, 5);
	hardware::ServoMotor bridgeMotorSW(9, 5);

	bridgeMotorNE.setPosition(90);
	delay(200);
	bridgeMotorSW.setPosition(90);
	delay(200);

	BridgeActuator bridgeActuator(bridgeMotorNE, bridgeMotorSW);
	bridgeActuator.setNE(Direction::South);
	delay(500);
	bridgeActuator.setSW(Direction::North);
	BridgeController bridgeController(bridgeActuator, switchN, switchE, switchS, switchW, switchPed);
	bool open = false;
	while (true) {
		switchN.tick();
		switchE.tick();
		switchS.tick();
		switchW.tick();
		switchPed.tick();
		bridgeMotorNE.tick();
		bridgeMotorSW.tick();
		bridgeActuator.tick();
		bridgeController.tick();
		/*if (switchN.pressed()) bridgeActuator.setNE(Direction::South);
		if (switchE.pressed()) bridgeActuator.setNE(Direction::West);
		if (switchS.pressed()) bridgeActuator.setSW(Direction::North);
		if (switchW.pressed()) bridgeActuator.setSW(Direction::East);*/

	
		delay(30);
	}
}

void loop() {}
