# AVR-ADC

## Purpose

To learn how to use the ADC on the ATmega328p.

I attempt to control the frequency of an led by sending the ADC the output from a potentiometer
configured as a voltage divider. By turning the pot, the frequency should change.

Final Product

<img src="images/finalproduct.jpg" alt="Final Product (should be picture here)" width="70%">

## Setup

### The Programmer

My programming setup consists of a Waveshare USB AVRISP XPII programmer conected to a breadboard.
The chip is powered via an arduino board, and has a pull up resistor connected to the reset pin.

<img src="images/programmer.jpg" alt="USB AVRISP XPII (should be picture here)" width="70%">


### The Software

I use `avr-gcc`, `avr-objcopy`, and `avrdude` to compile, convert to hex, and then upload to the
microcontroller. This is all run on Ubuntu 18.04. `avr-gcc` and `avr-objcopy` can be found in
the Ubuntu repo as `avr-libc` and `avrdude` as `avrdude`. All the commands are layed out in the included makefile.

The makefile included is for general purpose avr programming. For this specific repo you need to give make the name of the C source file to use. In this case using `adc.c` you need to tell make `adc`. To build and upload (using the same programming setup) run the following:

`make file=adc; make upload file=adc`

## Code

```c

define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void main(void)
{
	//setup port
	//using B1 as output
	DDRB = 0x02;
	PORTB = 0x00;
	//setup adc
	//power adc
	PRR = 0xFE;
	//set voltage reference & input channel
	//use AREF & ADC0 (PC0), bits left adjusted
	ADMUX = 0x20;
	//enable adc, set division factor of 8
	ADCSRA |= 0x83;

	while(1){
		//start adc conversion
		ADCSRA |= 0x40;
		//wait for conversion to finish
		while(ADCSRA & 0x40) {}
		// read value from adc
		unsigned int adcVal = ADCH;
		PINB = 0x02;
		for (int x = 0; x < adcVal*2; x++) {
			_delay_ms(1);
		}
	}

}

```

## Diagram

<img src="images/diagram.png" alt="Diagram Of Circuit (should be picture here)" width="70%">

Made with [www.circuit-diagram.org](https://www.circuit-diagram.org)

## Demo

Video Link

[![YouTube Link](https://img.youtube.com/vi/oh5O5O0txsk/0.jpg)](https://www.youtube.com/watch?v=oh5O5O0txsk)

## Useful Links

[328p datasheet](https://cdn.sparkfun.com/assets/c/a/8/e/4/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf)

[avr-libc library reference](https://www.nongnu.org/avr-libc/user-manual/modules.html)

[AVRFREAKS: Bit manipulation](https://www.avrfreaks.net/forum/tut-c-bit-manipulation-aka-programming-101?page=all)

[oscilloscope](https://www.amazon.com/dp/B06XZ1VXRV/ref=cm_sw_em_r_mt_dp_U_UWLLCb05ZB9QG)
