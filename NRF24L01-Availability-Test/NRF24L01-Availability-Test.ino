//Lights up the onboard led on the pro micro if the radio is working.
#include <Keyboard.h>

#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"
#define LED_PIN 17 //Onboard LED

int ReceivedMessage[1] = {000};
RF24 radio(9, 10); //MI and MO pins
const uint64_t pipe = 0xE6E6E6E6E6E6;

void setup(void) {
  radio.begin();
  radio.openReadingPipe(1, pipe); 
  radio.startListening(); 
}

void loop() {
  if (radio.isChipConnected())
  {
    digitalWrite(LED_PIN, LOW);
  }
  else
  {
    digitalWrite(LED_PIN, HIGH);
  }
}
