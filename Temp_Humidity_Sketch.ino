#include "Wire.h"          // Include Wire library for I2C communication
#include "MY_DHT.h"        // Include custom DHT sensor library
#include "MY_I2C_LCD.h"    // Include custom I2C LCD library

#define I2C_ADDR 0x27      // I2C address for the LCD

MY_DHT dht(5);            // Create a DHT sensor object on pin 5
I2C_LCD lcd(I2C_ADDR, 16, 2); // Create an LCD object with I2C address, 16 columns, and 2 rows

int Red = 3;               // Red LED pin
int Blue = 4;              // Blue LED pin
int Green = 2;             // Green LED pin

// Function to convert a binary string to a decimal number
unsigned int binToDec(String binaryString) 
{
  unsigned int decimal = 0;
  for (int i = 0; i < binaryString.length(); i++) 
  {
    decimal = decimal * 2 + (binaryString.charAt(i) - '0'); // Convert each bit
  }
  return decimal;
}

void setup() 
{
  lcd.Initialise();        // Initialize the LCD
  pinMode(Red, OUTPUT);    // Set Red LED pin as output
  pinMode(Green, OUTPUT);  // Set Green LED pin as output
  pinMode(Blue, OUTPUT);   // Set Blue LED pin as output
}

void loop() 
{
  float h = dht.Integral_hum;          // Get humidity reading from DHT sensor
  float t_dec = binToDec(dht.Decimal_temp); // Convert binary string to decimal for temperature
  float t = dht.Integral_temp + (t_dec / 10); // Calculate total temperature
  dht.read(5);                         // Read DHT sensor data

  // Display temperature on LCD
  lcd.lnOne_Cursor();                  // Move cursor to line one
  lcd.print_txt("    Temp: ");         // Print "Temp:" label
  lcd.print_num(t, 2);                 // Print temperature with 2 decimal places
  lcd.print_txt("C ");                 // Print "C" for Celsius

  // Display humidity on LCD
  lcd.lnTwo_Cursor();                  // Move cursor to line two
  lcd.print_txt("Humidity: ");         // Print "Humidity:" label
  lcd.print_num(h, 2);                 // Print humidity with 2 decimal places
  lcd.print_txt("%");                  // Print "%" for percentage

  lcd.Cursor_off();                    // Turn off the LCD cursor
  lcd.go_home();                       // Move the cursor to the home position

  // Control LEDs based on temperature range
  if (t < 20) 
  {
    digitalWrite(Blue, HIGH);          // Turn on Blue LED if temperature < 20
    digitalWrite(Red, LOW);            // Turn off Red LED
    digitalWrite(Green, LOW);          // Turn off Green LED
  } 
  else if (t > 20 && t < 30) 
  {
    digitalWrite(Blue, LOW);           // Turn off Blue LED if 20 <= temperature < 30
    digitalWrite(Red, LOW);            // Turn off Red LED
    digitalWrite(Green, HIGH);         // Turn on Green LED
  } 
  else if (t > 30) 
  {
    digitalWrite(Blue, LOW);           // Turn off Blue LED if temperature > 30
    digitalWrite(Red, HIGH);           // Turn on Red LED
    digitalWrite(Green, LOW);          // Turn off Green LED
  }
}
