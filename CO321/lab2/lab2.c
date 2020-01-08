#include <avr/io.h> 
#include <util/delay.h>

#define BLINK_DELAY_MS 100

int main(){
	
	DDRD &= ~(1<<7);  //input for PORTD pin 7
	//DDRB = 0xFF;		//PORTB for output
	unsigned char count = 0;
	
	while(1){  //8 bits in PORTB.maximum inputs = 63
		
		if(PIND & (1<<7)){	//if the button is pressed
		
				count = count + 1;
				
				//PORTB = count;
				
			//	_delay_ms(BLINK_DELAY_MS);
				
		}
	
	}
	
	//return 0;
}