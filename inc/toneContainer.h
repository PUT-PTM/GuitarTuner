#include "arm_math.h"


#ifndef TC
#define TC

#define TC_size 64
#define TC_TuneMargin 0.1

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


void TC_append(toneContainer *tc, double ToneFrequency, char* display);

void TC_find(toneContainer *tc, double ToneFrequency, char* display);

void TC_init(toneContainer *TC);

void TC_fill(toneContainer *TC);

#endif
