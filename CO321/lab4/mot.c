#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000


int main(){
	
	DDRD &= ~(1<<2);
	DDRD &= ~(1<<3);
	
	DDRD |= (1<<6);
	DDRD |= (1<<5);
	
	TCCR0A = (1<<WGM01) | (1<<WGM00);
	TCCR0A |= (1<<COM0A0) | (1<<COM0B1);
	
	TCCR0B = 0x03;
	OCR0A = 127;
	//sei();
	//TIMSK0 = 0x01;
	
	while(1){
		
		if(PIND&(1<<2)){
			OCR0B = 76;
		}
		
		if(PIND&(1<<3)){
			OCR0B = 30;
		}
		
	}
	
	return 0;
}
	