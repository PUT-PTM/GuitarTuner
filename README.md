# GuitarTuner

## Work in progress

## 1.Overview
This program is used for tuning instruments like Guitar. LED Display shows frequency of sound and name of tone with direction for tune ('-' up, '+' down).

## 2.Description
Tuner accuracy is 2Hz.

## 3.Tools
### Following hardware is required:

| STM32F4 DISCOVERY | TM1637 LED Display | Analog Microphone | RGB LED |
| --- | --- | --- | --- |

| USART Module - Only for Debug |
| --- |

You need also additional wires to connect the devices.

### Following additional libraries are required:
| [CMSIS DSP Library](https://github.com/ARM-software/CMSIS) | [Library for TM1637](https://github.com/rogerdahl/stm32-tm1637) |
| --- | --- |

Libraries are included in this project.

### Following additional software is required:

| [Hercules by HW-group.com](https://www.hw-group.com/products/hercules/index_en.html) | For USART Debug Only |
| --- | --- |

## 4.How to run
### 4.1 Wire Connections 

**Connect pins as follows:** <br/>

| **STM32F4 DISCOVERY** | **TM1637 LED Display** | 
| ----------------- | ------------------ |
| 3.3V | VCC |
| GND | GND |
| PC0 | CLK |
| PC1 | DIO |
| **STM32F4 DISCOVERY** | **Analog Microphone** |
| 3.3V | VCC |
| GND | GND |
| PA1 | AOUT |
| **STM32F4 DISCOVERY** | **RGB LED** |
| GND | GND |
| PB7 | R |
| PB8 | G |
| PB5 | B |
| **STM32F4 DISCOVERY** | **USART Module** |
| GND | GND |
| TXD | PC11 |
| RXD | PC10 |

### 4.2 IDE
Use Eclipse for C/C++ Developers updated to STM32 Workbench.

## 5.How to compile
Connect STM32 to PC using USB cable. Simply compile the project using IDE.

## 6.Future improvements
### This project will no longer be supported

### Known issues
:x: **Use of `float` causes `Hard Fault`. Due to this `double` is used.**<br/>
:x: **Use of `arm_cmplx_mag_f32` causes `Hard Fault`. Due to this `arm_cmplx_mag_squared_f32` is used.** <br/>

## 7.Attributions
### External libraries
| [CMSIS DSP Library](https://github.com/ARM-software/CMSIS) | [Library for TM1637](https://github.com/rogerdahl/stm32-tm1637) |
| --- | --- |

## 8.License
**GuitarTuner** is licensed under GNU GPL v3.0. Refer to [license.md](https://github.com/PUT-PTM/GuitarTuner/blob/master/license.md) for more. <br/>

**[CMSIS DSP Library](https://github.com/ARM-software/CMSIS)** is licensed under [license](https://github.com/ARM-software/CMSIS/blob/master/CMSIS/DSP_Lib/license.txt).
 <br/>

**[Library for TM1637](https://github.com/rogerdahl/stm32-tm1637/)** is licensed under [MIT License](https://github.com/rogerdahl/stm32-tm1637/blob/master/LICENSE.md). <br/>

## 9.Credits

| [Stanisław Wasik](https://github.com/st-wasik) | [Stanisław Gilewicz](https://github.com/forgut) |
| --- | --- | 


| **The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.** |
| :---: |
| **Supervisor: Marek Kraft/Michał Fularz/Tomasz Mańkowski/Adam Bondyra** |

