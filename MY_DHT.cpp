#include <Arduino.h>
#include <MY_DHT.h>

MY_DHT::MY_DHT(uint8_t pin)
{
}

void MY_DHT::read(uint8_t pin)
{
  uint16_t rawHumidity = 0;
  uint16_t rawTemperature = 0;
  uint8_t checkSum = 0;

  // Wait for sensor to stabilize
  delay(1000);

  // Send start signal
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(18000);
  digitalWrite(pin, HIGH);
  delayMicroseconds(30);
  pinMode(pin, INPUT_PULLUP);

  // Wait for sensor to respond
  uint32_t duration = pulseIn(pin, LOW, 10000);
  if (duration == 0) {
    Serial.println("ERROR_TIMEOUT");
    return;
  }

  // Read data bits
  for (int i = 0; i < 40; i++) {
    duration = pulseIn(pin, HIGH, 10000);
    if (duration == 0) {
      Serial.println("ERROR_TIMEOUT");
      return;
    }
    if (duration > 40) {
      if (i < 16) {
        rawHumidity |= (1 << (15 - i));
      } else if (i < 32) {
        rawTemperature |= (1 << (31 - i));
      } else if (i < 40) {
        checkSum |= (1 << (7 - (i - 32)));
      }
    }
  }

  // Check checksum
  if (checkSum != ((rawHumidity >> 8) + (rawHumidity & 0xFF) + (rawTemperature >> 8) + (rawTemperature & 0xFF))) {
    Serial.println("ERROR_CHECKSUM");
    return;
  }

  // Convert raw data to temperature and humidity
  Integral_hum = rawHumidity >> 8;
  Decimal_hum = rawHumidity & 0xFF;
  Integral_temp = rawTemperature >> 8;
  Decimal_temp = rawTemperature & 0xFF;

}