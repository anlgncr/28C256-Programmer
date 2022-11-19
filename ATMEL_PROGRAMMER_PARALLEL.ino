/*
	Arduino uno pins;
	PORTB
		9	-> Data7 (Most Significant Bit)
		8	-> Data6
		
	PORTD
		7	-> Data5
		6	-> Data4
		5	-> Data3
		4	-> Data2
		3	-> Data1
		2	-> Data0 (Least Significant Bit)
	
	PORTC	
		A0	-> Address High Clock
		A1	-> Address Low Clock
		A2	-> Button with pull down resistor
		
		A4	-> Eeprom Output Enable Pin 
		A5	-> Eeprom Write Enable Pin
*/

#define ARDUINO 1
#define EEPROM 2
#define BUTTON A2


void selectOutput(byte i){
	if(i == ARDUINO){
		PORTC |= B00010000; // Disable Eeprom Output
		setAsOutput();
	}
	else if(i == EEPROM){
		setAsInput();
		PORTC &= B11101111; // Enable Eeprom Output	
	}
}

void setData(byte data){
	PORTD &= B00000011;
	PORTD |= (data<<2);
	
	PORTB &= B00100000;
	PORTB |= (data>>6);
}

byte getData(){
	return ((PINB<<6) | (PIND>>2));
}

void writeEeprom(unsigned int address, byte value){
	byte addressL = (byte)address;
	byte addressH = (byte)(address>>8);
	
	selectOutput(ARDUINO);
	
	setData(addressL);
	PORTC &= B11111101;
	PORTC |= B00000010; // Address Low Clock
	
	setData(addressH);
	PORTC &= B11111110;
	PORTC |= B00000001; // Address High Clock
	
	setData(value);
	
	PORTC &= B11011111; // Enable Eeprom Write
	delayMicroseconds(1);
	PORTC |= B00100000; // Disable Eeprom Write

	while(readEeprom(address) != value);
}

byte readEeprom(unsigned int address){
	byte addressL = (byte)address;
	byte addressH = (byte)(address>>8);
	
	selectOutput(ARDUINO);
	
	setData(addressL);
	PORTC &= B11111101;
	PORTC |= B00000010; // Address Low Clock
	
	setData(addressH);
	PORTC &= B11111110;
	PORTC |= B00000001; // Address High Clock
	
	selectOutput(EEPROM);
	delayMicroseconds(10);
	return getData();
}


void setAsInput(){
	DDRB &= B11111100;
	DDRD &= B00000011;
}

void setAsOutput(){
	DDRB |= B00000011;
	DDRD |= B11111100;
}

void setup() {
	Serial.begin(9600);

	DDRC = B00110011;
	PORTC |= B00110000; // Disable eeprom write and eeprom data output

	selectOutput(ARDUINO);
	
	Serial.println("Presss the button to start...");
	while(!(digitalRead(BUTTON)));	
	
	for(unsigned int i=0; i<512; i++){
		writeEeprom(i, i%201);
	}
	
	for(unsigned int i=0; i<512; i++){
		Serial.println(readEeprom(i));
	}
	
}

void loop() {

}
