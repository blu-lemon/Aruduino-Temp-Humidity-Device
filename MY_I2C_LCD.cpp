#include "MY_I2C_LCD.h"
#include "Arduino.h"
#include "Wire.h"
#include "avr/io.h"

/*
========================================================================================================================================================================
  Public Methods
*/
I2C_LCD::I2C_LCD(unsigned int lcd_addr, unsigned int lcd_width, unsigned int lcd_height)
{

}

void I2C_LCD::Initialise()
{ 
  delay(50);
  i2c_initialise();
  send_cmd(0x03);
  delay(10);
  send_cmd(0x03);
  delayMicroseconds(150);
  send_cmd(0x03);
  send_cmd(0x02);
  send_cmd(0x01);
}

void I2C_LCD::i2c_initialise()
{
  TWSR = 0;           // prescaler = 0
  TWBR = 72;          // SCK freq = 100kHz
  TWCR = (1<<TWEN);   // enable TWI
}

void I2C_LCD::lnOne_Cursor()
{
  send_cmd(0b00000110);
}

void I2C_LCD::lnTwo_Cursor()
{
  send_cmd(0b11000000);
}

void I2C_LCD::send_cmd(unsigned int value)
{
  send_data_cmd(value, 0); 
}

void I2C_LCD::send_data(unsigned char value)
{
  send_data_cmd(value, 1);
}

void I2C_LCD::print_txt(char *str)
{
  while(*str)
  {
    send_data(*str++);
  }
}
void I2C_LCD::print_num(float num, int dec_places)
{
   char holder[4];
   dtostrf(num, 1, 2, holder);
   print_txt(holder);
}

void I2C_LCD::Cursor_off()
{
   unsigned int controlCurs = 0x04 | 0x00 | 0x00;
   controlCurs &= ~0x02;
   send_cmd(0x08 | controlCurs);
}

void I2C_LCD::go_home()
{
   send_cmd(0b00000010);
}

/*
====================================================================================================================================================
   Private Methods
*/

void I2C_LCD::send_data_cmd(unsigned int bits, unsigned int mode)
{
  unsigned int high_nibble = bits & 0xF0;
  unsigned int low_nibble = (bits << 4) & 0xF0;
  send_byte(high_nibble | mode);
  send_byte(low_nibble | mode); 
}

void I2C_LCD::send_byte(unsigned int value)
{
   I2C_Write(value);
   I2C_Enable(value);
}

void I2C_LCD::I2C_Write(unsigned int data)
{                                        
   Wire.beginTransmission(I2C_ADDR);
   Wire.write(data | 0x08);
   Wire.endTransmission();
} 

void I2C_LCD::I2C_Enable(unsigned int data)
{
   I2C_Write(data | 0b00000100);	
   delayMicroseconds(2);
   I2C_Write(data & ~0b00000100);	
   delayMicroseconds(50);		
} 

//==================================================================================================================================================
