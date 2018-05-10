#include "toneContainer.h"

void charCopy(unsigned int n, char new[], char orig[])
{
	for(unsigned int i=0; i<n; i++)
	{
		new[i]=orig[i];
	}
}

void TC_append(toneContainer * tc, float32_t Tone, char disp[])
{
	tm1637Display(" 001");
	unsigned int size = tc->size;
	tm1637Display(" 002");
	if(size < TC_size)
	{
		if(tc->size==0)
		{
			tc->container[size].lowerBound = TC_MIN_FREQUENCY;
		}
		else
		{
			float32_t temp = (tc->container[size-1].toneFrequency + tc->container[size].toneFrequency)/2;
			tc->container[size-1].upperBound = temp;
			tc->container[size].lowerBound = temp;
		}
		tm1637Display(" 003");

		tc->container[size].upperBound = TC_MAX_FREQUENCY;
		tm1637Display(" 006");
		tc->container[size].toneFrequency = Tone;
		tm1637Display(" 007");
		charCopy(3,tc->container[size].display, disp);
		tm1637Display(" 008");
		tc->size++;
	}
}

void TC_find(toneContainer * tc, float32_t Frequency, char disp[4])
{
	for(int i=0;i<TC_size;i++)
	{
		if((tc->container[i].lowerBound <= Frequency) && (Frequency < tc->container[i].upperBound))
		{
			charCopy(3, disp, tc->container[i].display);

			if(Frequency < (tc->container[i].toneFrequency - tc->container[i].toneFrequency*TC_TuneMargin))
			{
				disp[3] = '-';
			}
			else if(Frequency > (tc->container[i].toneFrequency + tc->container[i].toneFrequency*TC_TuneMargin))
			{
				if(disp[2]==' ')
				{
					disp[2]='+';
					disp[3]='-';
				}
				else
				{
					disp[3]='+';
				}
			}
			else
			{
				disp[3]=' ';
			}
			return;
		}
	}
	charCopy(4, disp, "none");
}

void TC_init(toneContainer * tc)
{
	tc->size = 0;
}

void TC_fill(toneContainer * tc)
{
	tm1637Display("  01");

	TC_init(tc);
	tm1637Display("  02");

	TC_append(tc, 192.43, "g   ");
	TC_append(tc, 203.88, "ab  ");
	TC_append(tc, 216.00, "a   ");
	TC_append(tc, 228.84, "b   ");
	TC_append(tc, 242.45, "h   ");

	TC_append(tc, 256.87, "c1  ");
	TC_append(tc, 272.14, "db1 ");
	TC_append(tc, 288.33, "d1  ");
	TC_append(tc, 305.47, "eb1 ");
	TC_append(tc, 323.63, "e1  ");
	TC_append(tc, 342.88, "f1  ");
	TC_append(tc, 363.27, "gb1 ");
	TC_append(tc, 384.87, "g1  ");
	TC_append(tc, 407.75, "ab1 ");
	TC_append(tc, 432.00, "a1  "); //432
	TC_append(tc, 457.69, "b1  ");
	TC_append(tc, 484.90, "h1  ");

	TC_append(tc, 513.74, "c2  ");
	TC_append(tc, 544.29, "db2 ");
	TC_append(tc, 576.65, "d2  ");
	TC_append(tc, 610.94, "eb2 ");
	TC_append(tc, 647.27, "e2  ");
	TC_append(tc, 685.76, "f2  ");
	TC_append(tc, 726.53, "gb2 ");
	TC_append(tc, 769.74, "g2  ");
	TC_append(tc, 815.51, "ab2 ");
	TC_append(tc, 864.33, "a2  ");
	TC_append(tc, 915.38, "b2  ");
	TC_append(tc, 969.81, "h2  ");

	TC_append(tc, 1027.47, "c3  ");
	TC_append(tc, 1088.57, "db3 ");
	TC_append(tc, 1153.30, "d3  ");
	TC_append(tc, 1221.88, "eb3 ");
	TC_append(tc, 1294.54, "e3  ");
	TC_append(tc, 1371.51, "f3  ");
	TC_append(tc, 1453.07, "gb3 ");
	TC_append(tc, 1539.47, "g3  ");
	tm1637Display("  09");
}
