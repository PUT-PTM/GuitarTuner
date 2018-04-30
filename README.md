# GuitarTuner

## Work in progress

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.

Supervisor: Marek Kraft/Michał Fularz/Tomasz Mańkowski/Adam Bondyra

## 1.Overview
This program is used for tuning instruments like Guitar. 
LED Display shows frequency of sound and name of tone with direction for tune ('+' up, '-' down).

## 2.Description

## 3.Tools
This project is for STM32F4Discovery.
LED Dispaly TM1637 and connection wires are also needed.

## 4.How to run
### 4.1 Wire Connections 
**Connect pins as follows**
<br/>
**STM32F4 <-----> LED Display**
* PB0 <-----> a <br />
* PB1 <-----> b <br />
* PB2 <-----> c <br />
* PB4 <-----> d <br />
* PB5 <-----> e <br /> 
* PB7 <-----> f <br />
* PB8 <-----> g <br />
* PB11 <-----> h <br />
* PB12 <-----> 1 <br />
* PB13 <-----> 2 <br />
* PB14 <-----> 3 <br />
* PB15 <-----> 4 <br />
* 3.3V <-----> VCC <br />

**STM32F4 <-----> STM32F4**
* PA1 <-----> 

### 4.2 IDE
Use Eclipse for C/C++ Developers updated to STM32 Workbench.

## 5.How to compile
Connect STM32 to PC using USB cable. Simply compile the project using IDE.

## 6.Future improvements

## 7.Attributions

## 8.License
### GNU GPL v3.0 
Refer to license.md for more.

## 9.Credits


