///////////////////////////////////////////////////////////////////////////////

//Modified by: Jeferson Pazze  (jeferson.pazze@tothlifecare.com)
//Date: 03/20/2020

///////////////////////////////////////////////////////////////////////////////

#include <ad7124.h>

const int ledPin = 9;
const int ssPin = 10;

Ad7124Chip adc;

void setup() {

  pinMode (ledPin, OUTPUT);
  digitalWrite (ledPin, 1); 

  Serial.begin (38400);
  while (!Serial) 
  {
    ; 
  }

  Serial.println ("AD7124 Voltmeter");

  adc.begin (ssPin);

  adc.setConfig (0, Ad7124::RefInternal, Ad7124::Pga1, true);
  adc.setChannel (0, 0, Ad7124::AIN1Input, Ad7124::AIN0Input);
  adc.setAdcControl (Ad7124::StandbyMode, Ad7124::FullPower, true);
}

void loop() 
{
  long value;
  double voltage;

  digitalWrite (ledPin, 0);
  value = adc.read (0);
  digitalWrite (ledPin, 1);

  if (value >= 0) {

    voltage = Ad7124Chip::toVoltage (value, 1, 2.5, true);
    Serial.println (voltage, 3);
  }
  else 
  {
    Serial.println ("FAIL");
  }
}
