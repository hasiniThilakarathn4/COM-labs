#include <avr/io.h>

void delay_timer0(){
	
	TCNT0 = 65504;  //Load timer counter register
	
	TCCR0A = 0x00;   //Set Timer0 under normal mode with 1:8 prescaler
	TCCR0B = 0x05;
	
	while((TIFR0&0x01)==0);  //Wait till timer overflow bit (TOV0) is set_new_handler
	
	TCCR0A = 0x00;   //Clear timer setings (this stops the timer)
	TCCR0B = 0x00;
	
	TIFR0 = 0x01; 
}

int main (void){
	
	DDRB = DDRB | (1<<5);  //configure pin 5 of PORTB for output
	
	while(1){
		PORTB = PORTB ^ (1<<5);  //configure pin 5 of PORTB for output
		delay_timer0();
	}
}
	