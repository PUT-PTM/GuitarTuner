
#ifndef TC
#define TC

#define TC_size 1024

typedef struct {

	double lowerBound, toneFrequency, upperBound;

	char display[3];

} toneNode;

typedef struct {

	toneNode container[TC_size];

} toneContainer;

void TC_append(toneContainer* TC, double Tone, char display[4]);

void TC_find(toneContainer* TC, double Frequency, char display[4]);

void TC_clear(toneContainer* TC);

void TC_fill(toneContainer* TC);

#endif
