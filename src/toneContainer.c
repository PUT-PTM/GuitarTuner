#include "toneContainer.h"

#include "stm32_tm1637.h"

void charCopy(unsigned int n, char new[], char orig[])
{
	for(unsigned int i=0; i<n; i++)
	{
		new[i]=orig[i];
	}
}

toneContainer tc;

void TC_append(int Tone, char* disp)
{
	tm1637Display("abb1");
	unsigned int size = tc.size;
	tm1637Display("abb2");
	if(size < TC_size)
	{
		tm1637Display("ab25");
		if(tc.size==0)
		{
			tc.container[size].lowerBound = (double)TC_MIN_FREQUENCY;
		}
		else
		{
			double temp = (tc.container[size-1].toneFrequency + tc.container[size].toneFrequency)/2;
			tc.container[size-1].upperBound = temp;
			tc.container[size].lowerBound = temp;
		}
		tm1637Display("abb3");

		tc.container[size].upperBound = (double)TC_MAX_FREQUENCY;
		tm1637Display("abb4");
		tc.container[size].toneFrequency = (double)((double)Tone);
		tm1637Display("abb5");
		charCopy(3,tc.container[size].display, disp);
		tm1637Display("abb6");
		tc.size++;
	}
}


void TC_find(int f, char disp[4])
{
	double Frequency = (double)f;
	for(int i=0;i<TC_size;i++)
	{
		if((tc.container[i].lowerBound <= Frequency) && (Frequency < tc.container[i].upperBound))
		{
			charCopy(3, disp, tc.container[i].display);

			if(Frequency < (tc.container[i].toneFrequency - tc.container[i].toneFrequency*TC_TuneMargin))
			{
				disp[3] = '-';
			}
			else if(Frequency > (tc.container[i].toneFrequency + tc.container[i].toneFrequency*TC_TuneMargin))
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

void TC_init()
{
	tc.size = 0;
}

void TC_fill()
{
	TC_init(tc);

	TC_append( 192, "g   ");
	TC_append( 203, "ab  ");
	TC_append( 216, "a   ");
	TC_append( 228, "b   ");
	TC_append( 242, "h   ");

	TC_append(256.87, "c1  ");
	TC_append(272.14, "db1 ");
	TC_append(288.33, "d1  ");
	TC_append(305.47, "eb1 ");
	TC_append(323.63, "e1  ");
	TC_append(342.88, "f1  ");
	TC_append(363.27, "gb1 ");
	TC_append(384.87, "g1  ");
	TC_append(407.75, "ab1 ");
	TC_append(432.00, "a1  "); //432
	TC_append(457.69, "b1  ");
	TC_append(484.90, "h1  ");

	TC_append(513.74, "c2  ");
	TC_append(544.29, "db2 ");
	TC_append(576.65, "d2  ");
	TC_append(610.94, "eb2 ");
	TC_append(647.27, "e2  ");
	TC_append(685.76, "f2  ");
	TC_append(726.53, "gb2 ");
	TC_append(769.74, "g2  ");
	TC_append(815.51, "ab2 ");
	TC_append(864.33, "a2  ");
	TC_append(915.38, "b2  ");
	TC_append(969.81, "h2  ");

	TC_append(1027.47, "c3  ");
	TC_append(1088.57, "db3 ");
	TC_append(1153.30, "d3  ");
	TC_append(1221.88, "eb3 ");
	TC_append(1294.54, "e3  ");
	TC_append(1371.51, "f3  ");
	TC_append(1453.07, "gb3 ");
	TC_append(1539.47, "g3  ");
}
