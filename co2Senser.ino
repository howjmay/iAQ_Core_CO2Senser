#include "Wire.h"

#define iaqaddress 0x5A

uint16_t predict;
uint8_t statu;
int32_t resistance;
uint16_t tvoc;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{     
  readAllBytes();
  checkStatus();

  Serial.print("CO2:");
  Serial.print(predict);
  Serial.print(", Status:");
  Serial.print(statu, HEX);
  Serial.print(", Resistance:");
  Serial.print(resistance);
  Serial.print(", TVoC:");
  Serial.println(tvoc);

  delay(2000);

}
void readAllBytes() 
{
  Wire.requestFrom(iaqaddress, 9); //Used by the master to request bytes from a slave device. The bytes may then be retrieved with the available() and read() functions.
                                   //Syntax:
                                   //   Wire.requestFrom(address, quantity)
                                   //Parameters:
                                   //   address: the 7-bit address of the device to request bytes from
                                   //   quantity: the number of bytes to request

  predict = (Wire.read()<< 8 | Wire.read()); 
  statu = Wire.read();
  resistance = (Wire.read()& 0x00)| (Wire.read()<<16)| (Wire.read()<<8| Wire.read());
  tvoc = (Wire.read()<<8 | Wire.read());
}
void checkStatus()
{
  if(statu == 0x10)
  {
    Serial.println("Warming up...");
  }
  else if(statu == 0x00)
  {
    Serial.println("Ready");  
  }
  else if(statu == 0x01)
  {
    Serial.println("Busy");  
  }
  else if(statu == 0x80)
  {
    Serial.println("Error");  
  }
  else
  Serial.println("No Status, check module");  
}
