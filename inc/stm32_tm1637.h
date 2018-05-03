#ifndef TM1637
#define TM1637


void int_to_string(int a,char arr[4]);

void tm1637Init(void);
void tm1637Display(char arr[4], int displaySeparator);
void tm1637DisplayDecimal(int v, int displaySeparator);
void tm1637SetBrightness(char brightness);

#endif
