#include "arm_math.h"

#ifndef TC
#define TC

#define TC_size 64
#define TC_TuneMargin 2.0

#define TC_MIN_FREQUENCY 0.0
#define TC_MAX_FREQUENCY 16000.0

typedef struct
{
	double lowerBound, toneFrequency, upperBound;
	char display[3];
} toneNode;

typedef struct
{
	unsigned int size;
	toneNode container[TC_size];
} toneContainer;

void TC_append(int ToneFrequency, char* display);

void TC_find(int ToneFrequency, char* display);

void TC_init();

void TC_fill();

#endif
