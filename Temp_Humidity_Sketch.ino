#include "Wire.h"
#include "MY_DHT.h"
#include "MY_I2C_LCD.h"

#define I2C_ADDR 0x27

MY_DHT dht(5);
I2C_LCD lcd(0x27, 16, 2);

int Red = 3;
int Blue = 4;
int Green = 2;

unsigned int binToDec(String binaryString) 
{
  unsigned int decimal = 0;
  for (int i = 0; i < binaryString.length(); i++) 
  {
    decimal = decimal * 2 + (binaryString.charAt(i) - '0');
  }
  return decimal;
}

void setup() 
{
  lcd.Initialise();
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  float h = dht.Integral_hum;
  float t_dec = binToDec(dht.Decimal_temp);
  float t = dht.Integral_temp + (t_dec/10);
  dht.read(5);
  lcd.lnOne_Cursor();
  lcd.print_txt("    Temp: ");
  lcd.print_num(t,2);
  lcd.print_txt("C ");
  lcd.lnTwo_Cursor();
  lcd.print_txt("Humidity: ");
  lcd.print_num(h,2);
  lcd.print_txt("%");
  lcd.Cursor_off();
  lcd.go_home();
  
  if(t < 20)
  {
    digitalWrite(Blue, HIGH);
    digitalWrite(Red, LOW);
    digitalWrite(Green, LOW);
    
  }
  else if(t > 20 && t < 30 )
  {
    digitalWrite(Blue, LOW);
    digitalWrite(Red, LOW);
    digitalWrite(Green, HIGH);
  }
  else if(t > 30)
  {
    digitalWrite(Blue, LOW);
    digitalWrite(Red, HIGH);
    digitalWrite(Green, LOW);
  }
}
