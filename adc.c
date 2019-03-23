/*
Andrew Huebner
This program varies the frequency of a flashing led
proportional to the voltage as read by the built in
adc of the atmega 328p
*/

#define F_CPU 8000000UL
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
