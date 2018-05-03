#include "toneContainer.h"

void char4Copy(char new[4], char orig[4])
{
	for(int i =0;i<4;i++)
	{
		new[i]=orig[i];
	}
}

void TC_append(toneContainer* tc, double Tone, double Low, double Up, char display[4])
{
	for(int i=0;i<TC_size;i++)
	{
		if (tc->container[i].toneFrequency == 0)
		{
			tc->container[i].lowerBound = Low;
			tc->container[i].upperBound = Up;
			tc->container[i].toneFrequency = Tone;
			char4Copy(tc->container[i].display, display);
			return;
		}
	}
}

void TC_find(toneContainer* tc, double Frequency, char disp[4])
{
	for(int i=0;i<TC_size;i++)
	{
		if((tc->container[i].lowerBound <= Frequency) && (Frequency < tc->container[i].upperBound))
		{
			char4Copy(disp, tc->container[i].display);
			return;
		}
	}
}

void TC_clear(toneContainer* tc)
{
	for(int i=0;i<TC_size;i++)
	{
		tc->container[i].toneFrequency = 0;
	}
}
