#ifndef TM1637
#define TM1637

enum displayMode {Tone, Frequency};

void int_to_string_8(int a,char arr[8]);

void int_to_string(int a,char arr[4]);

void tm1637Init(void);

void tm1637Display(char arr[4]);

#endif
