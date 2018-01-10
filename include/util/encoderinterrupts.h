#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void encoder_init(void);
int32_t encoder_get(uint8_t idx);
void encoder_set(uint8_t idx, int32_t value);

#ifdef __cplusplus
}
#endif