#include <avr/io.h>

void usart_init(){
	UBRR0L = 103;
	UBRR0H = 0;
	
	
	UCSR0C &= ~(1<<UMSEL01) | ~(1<<UMSEL00) ; //asynchronous
	
	UCSR0C &= ~(1<<UPM01) | ~(1<<UPM00); //no parity
	
	UCSR0C &=  ~(1<<USBS0); //1 stop bit
	
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); //8 bit 
	 
	UCSR0B |= (1<<TXEN0) ;  //enable transmitting	
	UCSR0B |= (1<<RXEN0) ;	//enable receiving
}

void usart_send(char charc){
	
	
	while((UCSR0A & (1<<UDRE0))==0){}   //for next byte
	
	UCSR0A |= (1<<UDRE0) ;
	
	UDR0 = charc;
	
	while((UCSR0A & (1<<TXC0))==0){} 
	
	UCSR0A |= (1<<TXC0) ;
	
}

char usart_receive(){
	
while((UCSR0A & (1<<RXC0))==0){} // check for character receiving

UCSR0A |= (1<<RXC0) ;

return UDR0; 

}



char caeser_cipher(char encrpt_char){
	int cusCode;
	int ciphVal;
	int ascii_char = (int)encrpt_char; //convert to ascii value
	
	if(ascii_char >= 65 && ascii_char <= 90){ //check for alphabetical letters;simple letters
		cusCode = ascii_char -65; //to 0-25 code range (including 26)
		ciphVal = (cusCode + 3)%26; //encryption process with caeser cipher
		return (char)(ciphVal + 65); //convert to a ascii value
		
	}else if(ascii_char >= 97 && ascii_char <= 122){ //check for alphabetical letters;capital letters
		cusCode = ascii_char - 97; 
		ciphVal = (cusCode +3)%26; 
		return (char)(ciphVal +97);
	}
	return encrpt_char; //return without encrypting if the character is not in alphabet
}
	

int main(void){
	
	usart_init();
	
	char rece_byte;
	char encrpt_char;
	
	while(1){
		rece_byte = usart_receive();  //receive bytes
		encrpt_char = caeser_cipher(rece_byte); //encryption
		usart_send(encrpt_char); //send the encrypted characters
	}
	return 0;
}



	