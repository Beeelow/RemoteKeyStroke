#include <Keyboard.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

#define LED_PIN 17 //Onboard LED

int ReceivedMessage[1] = {000};
RF24 radio(9, 10); //CE, CSN
const uint64_t pipe = 0xE6E6E6E6E6E6; //Transmission pipe

void setup(void) 
{
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  Keyboard.begin();
}

void loop(void) 
{
  while (radio.available())
  {
    digitalWrite(LED_PIN, LOW);  //Connection established
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01

    if (ReceivedMessage[0] == 111) // Switch is pressed
    {
      digitalWrite(LED_PIN, LOW);
      Keyboard.print("Switch1 Hit");
    }
    else
    {
      digitalWrite(LED_PIN, HIGH);
    }
    delay(10);
  }
   digitalWrite(LED_PIN, HIGH); //No connection established
}
