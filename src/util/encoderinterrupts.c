#include "util/encoderinterrupts.h"
#include <Arduino.h>
#include <util/atomic.h>

volatile int32_t encoder_count[2] = {0};
volatile uint16_t encoder_bad[2] = {0};
uint8_t encoder_prev_state[2] = {0};

static const int8_t encoder_table[16] = {
	0, 1, -1, 2,
	-1, 0, 2, 1,
	1, 2, 0, -1,
	2, -1, 1, 0
};


void encoder_init() {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		pinMode(8, INPUT_PULLUP);
		pinMode(9, INPUT_PULLUP);
		pinMode(10, INPUT_PULLUP);
		pinMode(11, INPUT_PULLUP);
		PCMSK0 = (1<<PCINT0) | (1<<PCINT1) | (1<<PCINT2) | (1<<PCINT3);
		PCICR = (1<<PCIE0);
	}
}

static inline void encoder_update(uint8_t idx, uint8_t encoder_current_state) {
	int8_t encoder_delta = encoder_table[(encoder_current_state | (encoder_prev_state[idx] << 2)) & 0xF];
	encoder_prev_state[idx] = encoder_current_state;
	if (encoder_delta != 2) {
		encoder_count[idx] += encoder_delta;
	}
	else {
		encoder_bad[idx] += 1;
	}
}

ISR(PCINT0_vect) {
	encoder_update(0, (PINB >> 0) & 0b11);
	encoder_update(1, (PINB >> 2) & 0b11);
}

int32_t encoder_get(uint8_t idx) {
	int32_t retval;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		retval = encoder_count[idx];
	}
	return retval;
}

void encoder_set(uint8_t idx, int32_t value) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		encoder_count[idx] = value;
	}
}