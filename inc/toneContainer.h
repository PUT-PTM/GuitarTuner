#include "arm_math.h"

#ifndef TC
#define TC

#define TC_size 64
#define TC_TuneMargin 0.1

typedef struct {

	float32_t lowerBound, toneFrequency, upperBound;

	char display[3];

} toneNode;

typedef struct {
	unsigned int size;
	toneNode container[TC_size];

} toneContainer;

void TC_append(toneContainer* TC, float32_t Tone, char display[4]);

void TC_find(toneContainer* TC, float32_t Frequency, char display[4]);

void TC_init(toneContainer* TC);

void TC_fill(toneContainer* TC);

#endif
