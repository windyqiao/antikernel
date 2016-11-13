EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:cmos
LIBS:cypress-azonenberg
LIBS:hirose-azonenberg
LIBS:memory-azonenberg
LIBS:microchip-azonenberg
LIBS:osc-azonenberg
LIBS:passive-azonenberg
LIBS:power-azonenberg
LIBS:special-azonenberg
LIBS:xilinx-azonenberg
LIBS:analog-azonenberg
LIBS:cat5-tdr-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 11
Title "Decoupling capacitors for FPGA"
Date "Fri 16 Jan 2015"
Rev "$Rev: 1703 $"
Comp "Andrew Zonenberg"
Comment1 "Quad-Channel 1.25 GSa/s 12-bit Time-Domain Reflectometer"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 6750 3750 0    60   ~ 0
Bank 0
Text Notes 2850 3750 0    60   ~ 0
Bank 13
Text Notes 3500 3750 0    60   ~ 0
Bank 14
Text Notes 4150 3750 0    60   ~ 0
Bank 15
Text Notes 4800 3750 0    60   ~ 0
Bank 16
Text Notes 5450 3750 0    60   ~ 0
Bank 33
Text Notes 6100 3750 0    60   ~ 0
Bank 34
Text HLabel 2750 2900 0    60   Input ~ 0
GND
Text Notes 2850 3050 0    60   ~ 0
VCCINT
Text Notes 5350 3050 0    60   ~ 0
VCCAUX
Text Notes 3800 3050 0    60   ~ 0
VCCBRAM
Text Notes 7300 3000 0    60   ~ 0
VCCXADC
$Comp
L C C107
U 1 1 54AF0D32
P 2850 2700
F 0 "C107" H 2900 2800 50  0000 L CNN
F 1 "330 uF" H 2900 2600 50  0000 L CNN
F 2 "azonenberg:EIA_1210_CAP_NOSILK" H 2850 2700 60  0001 C CNN
F 3 "" H 2850 2700 60  0000 C CNN
	1    2850 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 2900 7350 2900
Text HLabel 2750 2500 0    60   Input ~ 0
1V0
Wire Wire Line
	2750 2500 4500 2500
$Comp
L C C112
U 1 1 54AF0E25
P 3800 2700
F 0 "C112" H 3850 2800 50  0000 L CNN
F 1 "100 uF" H 3850 2600 50  0000 L CNN
F 2 "azonenberg:EIA_1206_CAP_NOSILK" H 3800 2700 60  0001 C CNN
F 3 "" H 3800 2700 60  0000 C CNN
	1    3800 2700
	1    0    0    -1  
$EndComp
Connection ~ 2850 2500
Connection ~ 2850 2900
$Comp
L C C114
U 1 1 54AF0E93
P 4150 2700
F 0 "C114" H 4200 2800 50  0000 L CNN
F 1 "4.7 uF" H 4200 2600 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 4150 2700 60  0001 C CNN
F 3 "" H 4150 2700 60  0000 C CNN
	1    4150 2700
	1    0    0    -1  
$EndComp
$Comp
L C C117
U 1 1 54AF0EC3
P 4500 2700
F 0 "C117" H 4550 2800 50  0000 L CNN
F 1 "4.7 uF" H 4550 2600 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 4500 2700 60  0001 C CNN
F 3 "" H 4500 2700 60  0000 C CNN
	1    4500 2700
	1    0    0    -1  
$EndComp
Connection ~ 3800 2500
Connection ~ 4150 2500
Connection ~ 3800 2900
Connection ~ 4150 2900
Text HLabel 5350 2500 0    60   Input ~ 0
1V8
$Comp
L C C121
U 1 1 54AF1057
P 5350 2700
F 0 "C121" H 5400 2800 50  0000 L CNN
F 1 "47 uF" H 5400 2600 50  0000 L CNN
F 2 "azonenberg:EIA_0805_CAP_NOSILK" H 5350 2700 60  0001 C CNN
F 3 "" H 5350 2700 60  0000 C CNN
	1    5350 2700
	1    0    0    -1  
$EndComp
Connection ~ 4500 2900
$Comp
L C C123
U 1 1 54AF10B5
P 5650 2700
F 0 "C123" H 5700 2800 50  0000 L CNN
F 1 "47 uF" H 5700 2600 50  0000 L CNN
F 2 "azonenberg:EIA_0805_CAP_NOSILK" H 5650 2700 60  0001 C CNN
F 3 "" H 5650 2700 60  0000 C CNN
	1    5650 2700
	1    0    0    -1  
$EndComp
$Comp
L C C124
U 1 1 54AF10D7
P 5950 2700
F 0 "C124" H 6000 2800 50  0000 L CNN
F 1 "4.7 uF" H 6000 2600 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 5950 2700 60  0001 C CNN
F 3 "" H 5950 2700 60  0000 C CNN
	1    5950 2700
	1    0    0    -1  
$EndComp
$Comp
L C C126
U 1 1 54AF11B9
P 6300 2700
F 0 "C126" H 6350 2800 50  0000 L CNN
F 1 "4.7 uF" H 6350 2600 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 6300 2700 60  0001 C CNN
F 3 "" H 6300 2700 60  0000 C CNN
	1    6300 2700
	1    0    0    -1  
$EndComp
$Comp
L C C127
U 1 1 54AF1215
P 6650 2700
F 0 "C127" H 6700 2800 50  0000 L CNN
F 1 "4.7 uF" H 6700 2600 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 6650 2700 60  0001 C CNN
F 3 "" H 6650 2700 60  0000 C CNN
	1    6650 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2500 7350 2500
Connection ~ 5650 2500
Connection ~ 5950 2500
Connection ~ 6300 2500
Connection ~ 6300 2900
Connection ~ 5950 2900
Connection ~ 5350 2900
Connection ~ 5650 2900
$Comp
L C C128
U 1 1 54AF1579
P 6750 3400
F 0 "C128" H 6800 3500 50  0000 L CNN
F 1 "47 uF" H 6800 3300 50  0000 L CNN
F 2 "azonenberg:EIA_0805_CAP_NOSILK" H 6750 3400 60  0001 C CNN
F 3 "" H 6750 3400 60  0000 C CNN
	1    6750 3400
	1    0    0    -1  
$EndComp
$Comp
L C C108
U 1 1 54AF169B
P 2850 3400
F 0 "C108" H 2900 3500 50  0000 L CNN
F 1 "47 uF" H 2900 3300 50  0000 L CNN
F 2 "azonenberg:EIA_0805_CAP_NOSILK" H 2850 3400 60  0001 C CNN
F 3 "" H 2850 3400 60  0000 C CNN
	1    2850 3400
	1    0    0    -1  
$EndComp
Text Label 6950 2900 0    60   ~ 0
GND
Text Label 2750 3600 2    60   ~ 0
GND
$Comp
L C C111
U 1 1 54AF18ED
P 3500 3400
F 0 "C111" H 3550 3500 50  0000 L CNN
F 1 "47 uF" H 3550 3300 50  0000 L CNN
F 2 "azonenberg:EIA_0805_CAP_NOSILK" H 3500 3400 60  0001 C CNN
F 3 "" H 3500 3400 60  0000 C CNN
	1    3500 3400
	1    0    0    -1  
$EndComp
Connection ~ 2850 3600
Wire Wire Line
	2750 3600 6750 3600
$Comp
L C C115
U 1 1 54AF1DAD
P 4150 3400
F 0 "C115" H 4200 3500 50  0000 L CNN
F 1 "47 uF" H 4200 3300 50  0000 L CNN
F 2 "azonenberg:EIA_0805_CAP_NOSILK" H 4150 3400 60  0001 C CNN
F 3 "" H 4150 3400 60  0000 C CNN
	1    4150 3400
	1    0    0    -1  
$EndComp
$Comp
L C C118
U 1 1 54AF1E66
P 4800 3400
F 0 "C118" H 4850 3500 50  0000 L CNN
F 1 "47 uF" H 4850 3300 50  0000 L CNN
F 2 "azonenberg:EIA_0805_CAP_NOSILK" H 4800 3400 60  0001 C CNN
F 3 "" H 4800 3400 60  0000 C CNN
	1    4800 3400
	1    0    0    -1  
$EndComp
$Comp
L C C122
U 1 1 54AF1FA8
P 5450 3400
F 0 "C122" H 5500 3500 50  0000 L CNN
F 1 "47 uF" H 5500 3300 50  0000 L CNN
F 2 "azonenberg:EIA_0805_CAP_NOSILK" H 5450 3400 60  0001 C CNN
F 3 "" H 5450 3400 60  0000 C CNN
	1    5450 3400
	1    0    0    -1  
$EndComp
$Comp
L C C125
U 1 1 54AF2031
P 6100 3400
F 0 "C125" H 6150 3500 50  0000 L CNN
F 1 "47 uF" H 6150 3300 50  0000 L CNN
F 2 "azonenberg:EIA_0805_CAP_NOSILK" H 6100 3400 60  0001 C CNN
F 3 "" H 6100 3400 60  0000 C CNN
	1    6100 3400
	1    0    0    -1  
$EndComp
Connection ~ 5450 3600
Connection ~ 4800 3600
Connection ~ 3500 3600
Connection ~ 4150 3600
Connection ~ 6650 2900
Connection ~ 6100 3600
Text HLabel 2850 3900 0    60   Input ~ 0
GTX_VCC
Text HLabel 3850 3900 0    60   Input ~ 0
GTX_VTT
$Comp
L C C109
U 1 1 54AF3DCB
P 2850 4100
F 0 "C109" H 2900 4200 50  0000 L CNN
F 1 "4.7 uF" H 2900 4000 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 2850 4100 60  0001 C CNN
F 3 "" H 2850 4100 60  0000 C CNN
	1    2850 4100
	1    0    0    -1  
$EndComp
Text Label 2750 4300 2    60   ~ 0
GND
Wire Wire Line
	2750 4300 5150 4300
$Comp
L C C110
U 1 1 54AF3EF8
P 3200 4100
F 0 "C110" H 3250 4200 50  0000 L CNN
F 1 "4.7 uF" H 3250 4000 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 3200 4100 60  0001 C CNN
F 3 "" H 3200 4100 60  0000 C CNN
	1    3200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 3900 3200 3900
Connection ~ 2850 4300
Text Notes 2850 4450 0    60   ~ 0
Transceivers
$Comp
L C C113
U 1 1 54AF40C4
P 3850 4100
F 0 "C113" H 3900 4200 50  0000 L CNN
F 1 "4.7 uF" H 3900 4000 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 3850 4100 60  0001 C CNN
F 3 "" H 3850 4100 60  0000 C CNN
	1    3850 4100
	1    0    0    -1  
$EndComp
$Comp
L C C116
U 1 1 54AF4109
P 4200 4100
F 0 "C116" H 4250 4200 50  0000 L CNN
F 1 "4.7 uF" H 4250 4000 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 4200 4100 60  0001 C CNN
F 3 "" H 4200 4100 60  0000 C CNN
	1    4200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3900 4200 3900
Connection ~ 3200 4300
Connection ~ 3850 4300
Text HLabel 4800 3900 0    60   Input ~ 0
GTX_VAUX
$Comp
L C C119
U 1 1 54AF64BE
P 4800 4100
F 0 "C119" H 4850 4200 50  0000 L CNN
F 1 "4.7 uF" H 4850 4000 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 4800 4100 60  0001 C CNN
F 3 "" H 4800 4100 60  0000 C CNN
	1    4800 4100
	1    0    0    -1  
$EndComp
$Comp
L C C120
U 1 1 54AF64FB
P 5150 4100
F 0 "C120" H 5200 4200 50  0000 L CNN
F 1 "4.7 uF" H 5200 4000 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 5150 4100 60  0001 C CNN
F 3 "" H 5150 4100 60  0000 C CNN
	1    5150 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3900 5150 3900
Connection ~ 4200 4300
Connection ~ 4800 4300
$Comp
L C C129
U 1 1 54AF721E
P 7350 2700
F 0 "C129" H 7400 2800 50  0000 L CNN
F 1 "4.7 uF" H 7400 2600 50  0000 L CNN
F 2 "azonenberg:EIA_0603_CAP_NOSILK" H 7350 2700 60  0001 C CNN
F 3 "" H 7350 2700 60  0000 C CNN
	1    7350 2700
	1    0    0    -1  
$EndComp
Connection ~ 6650 2500
Text Label 5650 2500 0    60   ~ 0
1V8
Text Label 2850 3200 2    60   ~ 0
1V8
Text Label 5450 3200 2    60   ~ 0
1V8
Text HLabel 4150 3200 0    60   Input ~ 0
2V5
Wire Wire Line
	4150 3200 4800 3200
Wire Wire Line
	5450 3200 6750 3200
Connection ~ 6100 3200
Wire Wire Line
	2850 3200 3500 3200
$EndSCHEMATC