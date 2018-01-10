#include <Arduino.h>
#include <NewPing.h>
#include <Servo.h>


#include <util/encoderinterrupts.h>

#include <hardware/switch.h>
#include <hardware/lightsensor.h>
#include <hardware/crservo.h>
#include <hardware/encoder.h>
#include <hardware/encodermotor.h>

using namespace hardware;

NewPing sonar(10,11,100);

void setup(){
	Serial.begin(115200);
	encoder_init();
	pinMode(LED_BUILTIN, OUTPUT);
	
	Switch button(6, LOW);
	LightSensor lineSensor(0);
	Encoder encoder(0, false);
	ContinuousRotationServo motor(7, false);
	EncoderMotor em(motor, encoder);

	int i = 0;
	while (true) {
		encoder.tick();
		em.tick();

		em.setVelocity(button.get() * 1);


		Serial.print(encoder.getPosition());
		Serial.print(" ");
		Serial.println(encoder.getVelocity());
		delay(30);
	}
}

void loop() {}
