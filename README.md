# 28C256-Programmer
28C256 Eeprom Programmer

This programmer uses three 8bits registers (74HC574) and an arduino uno.

Arduino uno pin connections;

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
    
    I have not used all PORTC pins so i can use Serial Commmunication (RX and TX pins)
    
   


