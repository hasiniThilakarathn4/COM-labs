#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 100

unsigned char count = 0;

int main(){
	
	DDRD &= ~(1<<2);  //input pin 2 of PORTD
	
	DDRB = 0xFF;
	
	
	//while(count<64){
	//	if(PIND & (1<<2)){
	EICRA |= (1<<ISC01);
	EICRA |= (0<<ISC00);
	
	//count = count +1;
	//	}
	//}
	
	sei();
	
	EIMSK |= (1<<INT0);
	
	PORTB =0;
	while(1){
		
	}
	

	return 0;

}

ISR(INT0_vect){

	
	
	//PORTB |= (1<<0);
	//count = count +1;
	PORTB += 1 ;
	_delay_ms(BLINK_DELAY_MS);
	//PORTB = 0x00;
	
	/*PORTB &= ~(1<<0);
	_delay_ms(BLINK_DELAY_MS);*/
	
	//PORTB &= ~(1<<0);
	//PORTB |= (1<<0);
	
	
	
}