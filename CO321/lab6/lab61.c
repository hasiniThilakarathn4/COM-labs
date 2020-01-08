#include <avr/io.h>


void usart_init(){
	
	UCSR0C |= ~(1<<UMSEL01) | ~(1<<UMSEL00) ; //asynchronous
	UCSR0C |= ~(1<<UPM01) | ~(1<<UPM00) ; //no parity
	
	
	
	
}
	


int main(void){
	
}