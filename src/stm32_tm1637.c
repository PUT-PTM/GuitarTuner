#include "system_stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "stm32_tm1637.h"


void _tm1637Start(void);
void _tm1637Stop(void);
void _tm1637ReadResult(void);
void _tm1637WriteByte(unsigned char b);
void _tm1637DelayUsec(unsigned int i);
void _tm1637ClkHigh(void);
void _tm1637ClkLow(void);
void _tm1637DioHigh(void);
void _tm1637DioLow(void);

// Configuration.

#define CLK_PORT GPIOC
#define DIO_PORT GPIOC
#define CLK_PIN GPIO_Pin_0
#define DIO_PIN GPIO_Pin_1
#define CLK_PORT_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define DIO_PORT_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE


const char segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, //8-9
	0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3D, 0x76, // A-H,

    0x00
};


void tm1637Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);
	//CLK_PORT_CLK_ENABLE();
    //DIO_PORT_CLK_ENABLE();
    GPIO_InitTypeDef g = {0};
    g.GPIO_PuPd = GPIO_PuPd_UP;
    g.GPIO_Mode = GPIO_Mode_OUT; // OD = open drain
    g.GPIO_OType = GPIO_OType_OD;
    g.GPIO_Speed = GPIO_Speed_100MHz;
    g.GPIO_Pin = CLK_PIN;
    GPIO_Init(CLK_PORT, &g);
    g.GPIO_Pin = DIO_PIN;
    GPIO_Init(DIO_PORT, &g);




    tm1637SetBrightness(8);
}

void int_to_string(int a,char arr[4]) {
	if (a<=9999) {
	for (int i=3;i>=0;i--) {
		if (a!=0) arr[i]=a%10 +48; else arr[i]=' ';
		a/=10;
	}
	}
}

void tm1637DisplayDecimal(int v, int displaySeparator)
{
    unsigned char digitArr[4];
    for (int i = 0; i < 4; ++i) {
        digitArr[i] = segmentMap[v % 10];
        if (i == 2 && displaySeparator) {
            digitArr[i] |= 1 << 7;
        }
        v /= 10;
    }

    _tm1637Start();
    _tm1637WriteByte(0x40);
    _tm1637ReadResult();
    _tm1637Stop();

    _tm1637Start();
    _tm1637WriteByte(0xc0);
    _tm1637ReadResult();

    for (int i = 0; i < 4; ++i) {
        _tm1637WriteByte(digitArr[3 - i]);
        _tm1637ReadResult();
    }

    _tm1637Stop();
}


/*
 *
const char segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, //8-9
	0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3D, 0x76, // A-H,

    0x00
};
 * */
void tm1637Display(char arr[4], int displaySeparator)
{
    unsigned char digitArr[4];
    int j;
    for (int i=3;i>=0;i--)
    {
    	j = 3-i;
    switch (arr[i]) {
    	case 'a': { digitArr[j]=0x77; break;}
   		case 'b': { digitArr[j]=0x7c; break;}
  		case 'c': { digitArr[j]=0x39; break;}
  		case 'd': { digitArr[j]=0x5e; break;}
   		case 'e': { digitArr[j]=0x79; break;}
 		case 'f': { digitArr[j]=0x71; break;}
 		case 'g': { digitArr[j]=0x3D; break;}
   		case 'h': { digitArr[j]=0x76; break;}
   		case '0': { digitArr[j]=0x3f; break;}
   		case '1': { digitArr[j]=0x06; break;}
   		case '2': { digitArr[j]=0x5b; break;}
   		case '3': { digitArr[j]=0x4f; break;}
   		case '4': { digitArr[j]=0x66; break;}
   		case '5': { digitArr[j]=0x6d; break;}
   		case '6': { digitArr[j]=0x7d; break;}
   		case '7': { digitArr[j]=0x07; break;}
   		case '8': { digitArr[j]=0x7f; break;}
   		case '9': { digitArr[j]=0x6f; break;}
   		case ' ': {digitArr[j]=0x00 ; break;}
   		default : {digitArr[j]=0x2B; break;}
    }
    }
    _tm1637Start();
    _tm1637WriteByte(0x40);
    _tm1637ReadResult();
    _tm1637Stop();

    _tm1637Start();
    _tm1637WriteByte(0xc0);
    _tm1637ReadResult();

    for (int i = 0; i < 4; ++i) {
        _tm1637WriteByte(digitArr[3 - i]);
        _tm1637ReadResult();
    }

    _tm1637Stop();
}

// Valid brightness values: 0 - 8.
// 0 = display off.
void tm1637SetBrightness(char brightness)
{
    // Brightness command:
    // 1000 0XXX = display off
    // 1000 1BBB = display on, brightness 0-7
    // X = don't care
    // B = brightness
    _tm1637Start();
    _tm1637WriteByte(0x87 + brightness);
    _tm1637ReadResult();
    _tm1637Stop();
}

void _tm1637Start(void)
{
    _tm1637ClkHigh();
    _tm1637DioHigh();
    _tm1637DelayUsec(2);
    _tm1637DioLow();
}

void _tm1637Stop(void)
{
    _tm1637ClkLow();
    _tm1637DelayUsec(2);
    _tm1637DioLow();
    _tm1637DelayUsec(2);
    _tm1637ClkHigh();
    _tm1637DelayUsec(2);
    _tm1637DioHigh();
}

void _tm1637ReadResult(void)
{
    _tm1637ClkLow();
    _tm1637DelayUsec(5);
    // while (dio); // We're cheating here and not actually reading back the response.
    _tm1637ClkHigh();
    _tm1637DelayUsec(2);
    _tm1637ClkLow();
}

void testing() {
	for (int i=0;i<8;i++) {
		_tm1637ClkLow();
		_tm1637DioHigh();
	}
}

void _tm1637WriteByte(unsigned char b)
{
    for (int i = 0; i < 8; ++i)
    {
        _tm1637ClkLow();
        if (b & 0x01)
        {
            _tm1637DioHigh();
        }
        else
        {
            _tm1637DioLow();
        }
        _tm1637DelayUsec(3);
        b >>= 1;
        _tm1637ClkHigh();
        _tm1637DelayUsec(3);
    }
}

void _tm1637DelayUsec(unsigned int i)
{
    for (; i>0; i--) {
        for (int j = 0; j < 10; ++j) {
            __asm__ __volatile__("nop\n\t":::"memory");
        }
    }
}

void _tm1637ClkHigh(void)
{
    GPIO_SetBits(CLK_PORT, CLK_PIN);
	//HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, GPIO_PIN_SET);
}

void _tm1637ClkLow(void)
{
	GPIO_ResetBits(CLK_PORT, CLK_PIN);
	//HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, GPIO_PIN_RESET);
}

void _tm1637DioHigh(void)
{
	GPIO_SetBits(DIO_PORT, DIO_PIN);
    //HAL_GPIO_WritePin(DIO_PORT, DIO_PIN, GPIO_PIN_SET);
}

void _tm1637DioLow(void)
{
	GPIO_ResetBits(DIO_PORT, DIO_PIN);
	//HAL_GPIO_WritePin(DIO_PORT, DIO_PIN, GPIO_PIN_RESET);
}
