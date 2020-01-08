#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void){
	
	DDRD |= (1<<6);
	
	TCCR0A = (1<<WGM01) | (1<<WGM00);  //fast PWM mode
	TCCR0A |= (1<<COM0A1);  //non-inverting mode

	
     OCR0A = 127;  //output compare register DC=50%
 
	while (1){
		int i=2;
		
			while(i<6){
			TCCR0B = i;    //prescaler
			_delay_ms(BLINK_DELAY_MS);
			i++;
		}
		
		
	} 
	return 0;
}