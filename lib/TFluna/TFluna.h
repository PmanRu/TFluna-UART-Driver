#ifndef TFLUNA_H
#define TFLUNA_H

#include <avr/io.h>

uint16_t TF_distance(char unit);
void TF_monitor(uint16_t distance);

#endif