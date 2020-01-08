#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(){
	
	DDRD &= ~(1<<2);  //input PORTD bit2
	
	DDRB |= (1<<0);		//output LED. PORTB bit0
	
	EICRA |= (1<<ISC01); //falling edge for INT0
	EICRA |= (0<<ISC00);
	
	
	sei();  //enable global interrupt 
	
	EIMSK |= (1<<INT0);  //enable external interrupt for int0
	
	while(1){
		
	}
	return 0;
	
}

ISR(INT0_vect){
	
	
	PORTB ^= (1<<0); //toggle only bit 0 of PORTB
	
	
}