#ifndef MY_DHT_H
#define MY_DHT_H

class MY_DHT
{   
    public:
	MY_DHT(uint8_t pin);
	void read(uint8_t pin);
	int pin;        
	uint8_t Integral_hum;
        String Decimal_hum;
        uint8_t Integral_temp;
        String Decimal_temp;
	uint16_t rawHumidity;
        uint16_t rawTemperature;
};
#endif