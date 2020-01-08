#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

unsigned char count = 0;

int main(){
	
	DDRD &= ~(1<<2); //'1'
	DDRD &= ~(1<<3); //'0'
	
	DDRB = 0xFF;
	while(count<6){
	//int 0 rising edge
	EICRA |= (1<<ISC01);
	EICRA |= (1<<ISC00);
	
	sei(); //enable global interrupt
	
	EIMSK |= (1<<INT0); 	//enabling external interrupts for int0
	
	//int 1 rising edge
	EICRA |= (1<<ISC10);
	EICRA |= (1<<ISC11);
	
	sei(); //enable global interrupt
	
	EIMSK |= (1<<INT1);		//enabling external interrupts for int1
	
	}
	while(1){
	}
	return 0;
}


ISR(INT0_vect){
	count++;
	PORTB |= (1<<count);
	_delay_ms(BLINK_DELAY_MS);
	
}
	
ISR(INT1_vect){
    count++;
    PORTB &= ~(1<<count);
	_delay_ms(BLINK_DELAY_MS);
}	