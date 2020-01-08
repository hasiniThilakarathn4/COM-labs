#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	
	DDRD = 0xFF; //output LEDs

	DDRC &= ~(1<<1);  //PC1
	
	ADCSRA |= (1<<ADEN); //enable ADC
	
	ADCSRA |= (1<<PRADC); //power
	
	ADCSRA |= (1<ADPS1) | (1<<ADPS0);//prescler
	
	ADMUX |= (1<<REFS0); //refernce selection bits
	ADMUX &= ~(1<<REFS1);
	
	ADMUX |= (1<<MUX0); //input channel
	
	ADCSRA |= (1<<ADSC); //start conversion
	
	ADMUX |= (1<<ADLAR); //left
	
	
	while(1){
		
	while((ADSCRA|=(1<<ADIF)==0){
		
		
	}
	}
	
	}