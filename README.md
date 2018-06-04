# *GuitarTuner*

## Work in progress

## 1. Overview :eyes:
This program is used for tuning instruments like Guitar. LED Display shows frequency of sound and name of tone with direction for tune ('-' up, '+' down).

## 2. Description :books:
### 2.1 Use of *GuitarTuner* :musical_score: :notes: :musical_note: :trumpet: :saxophone: :postal_horn: :guitar: :violin: :musical_keyboard: 
Power on *GuitarTuner* and play a sound. Display shows the tone name and direction for tune. If you see '+' you sound is too high. If you see '-' your sound is too low. You can also see the frequency of sound. To do it change display mode. To change display mode use **USER-Button**. For tune scale and other information see the table below. 

### 2.2 Specification :pushpin:
| Tuner Specification | |
| --- | --- |
| Accuracy | ±1Hz |
| Sampling frequency | 2.4kHz |
| FFT size | 1024 complex samples | 
| FFT base type | float32 |
| **A** frequency <br/> (change only in code) | 432Hz (G3-D6 only) <br/> **440Hz (default)** |
| Maximum read <br/> tone frequency | 1200Hz |
| Tune scale | +C+ - D3 (German) <br/> C2 - D6 (American) |
| Tone names | German |
| Display mode | Tone name <br/> Frequency |

## 3. Tools :wrench:
### Following hardware is required:

| STM32F4 DISCOVERY | TM1637 LED Display | Analog Microphone | RGB LED |
| --- | --- | --- | --- |

| USART Module - For Debug Only |
| --- |

You need also additional wires to connect the devices.

### Following additional libraries are required:
| [CMSIS DSP Library](https://github.com/ARM-software/CMSIS) | [Library for TM1637](https://github.com/rogerdahl/stm32-tm1637) |
| --- | --- |

Libraries are included in this project.

### Following additional software is required:

| [Hercules by HW-group.com](https://www.hw-group.com/products/hercules/index_en.html) - For USART Debug Only |
| --- |

## 4. How to run :inbox_tray:
### 4.1 Wire Connections :electric_plug:

**Connect pins as follows:** <br/>

| **STM32F4 DISCOVERY** | **TM1637 LED Display** | 
| ----------------- | ------------------ |
| 3V | VCC |
| GND | GND |
| PC0 | CLK |
| PC1 | DIO |
| **STM32F4 DISCOVERY** | **Analog Microphone** |
| 3V | VCC |
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

### 4.2 IDE :computer:
Use Eclipse for C/C++ Developers updated to STM32 Workbench.

## 5. How to compile :page_with_curl:
:one: Create project using *.cproject* or *.project* (Eclipse 4.7.3a - use *Open Project from File System*). <br/>
:two: Connect STM32F4 DISCOVERY to your PC using USB wire. <br/>
:three: Simply compile the project using IDE (this project was compiled by GCC). <br/>
:four: Upload compiled software to your μC. <br/>
:five: Tune your musical instrument. 

## 6. Future improvements :seedling:
### :warning: This project will no longer be supported

### Known issues
:x: **Use of `float` causes `Hard Fault`. Due to this `double` is used.**<br/>
:x: **Use of `arm_cmplx_mag_f32` causes `Hard Fault`. Due to this `arm_cmplx_mag_squared_f32` is used.** <br/>
:x: **Use of first argument of type `double` in `TC_append` causes `Hard Fault`. Due to this `int` is used.** <br/>
:x: **Use of first argument of type `double` in `TC_find` causes `Hard Fault`. Due to this `int` is used.** <br/>
:x: **Microphone malfunction: temporary loss of signal. `MICROPHONE ERROR CHECK` section `(in FFT.c)` used to detect microphone error. Skip this code in your project.** <br/>

## 7. Attributions :bookmark_tabs:
### External libraries
| [CMSIS DSP Library](https://github.com/ARM-software/CMSIS) | [Library for TM1637](https://github.com/rogerdahl/stm32-tm1637) |
| --- | --- |

## 8. License :scroll:
**GuitarTuner** is licensed under GNU GPL v3.0. Refer to [license.md](https://github.com/PUT-PTM/GuitarTuner/blob/master/license.md) for more. <br/>

**[CMSIS DSP Library](https://github.com/ARM-software/CMSIS)** is licensed under [license](https://github.com/ARM-software/CMSIS/blob/master/CMSIS/DSP_Lib/license.txt).
 <br/>

**[Library for TM1637](https://github.com/rogerdahl/stm32-tm1637/)** is licensed under [MIT License](https://github.com/rogerdahl/stm32-tm1637/blob/master/LICENSE.md). <br/>

## 9. Credits :gem:

| [Stanisław Wasik](https://github.com/st-wasik) | [Stanisław Gilewicz](https://github.com/forgut) |
| --- | --- | 


| **The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.** |
| :---: |
| **Supervisor: Marek Kraft/Michał Fularz/Tomasz Mańkowski/Adam Bondyra** |

