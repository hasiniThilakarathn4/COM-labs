#include <avr/io.h>


int main(void){
	
	DDRC &= ~(1<<1); //input
	
	DDRB = 0xFF ; //output
	
	ADCSRA |= (1<<ADEN); //enable ADC

	
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2) ;//prescaler
	
	ADMUX |= (1<<REFS0); //reference
	
	ADMUX |= (1<<MUX0); //ADC1
	
	
	ADMUX |= (1<<ADLAR);//left-justified
	
	
	
	while(1){
		
		ADCSRA |= (1<<ADSC);//start coversion

		while((ADCSRA & 0b00010000)==0){			
		}
		ADCSRA |= (1<<ADIF);
		
		if(ADCH < 125){
			PORTB |= (1<<5);
		}else{
			PORTB &= ~(1<<5);
		}
		
	}
}
			
			
	
	