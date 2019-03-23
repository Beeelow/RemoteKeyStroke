#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

#define SWITCH1_PIN 2
#define LED_PIN 17 //Onboard LED

int SentMessage[1] = {000};
RF24 radio(9, 10); //CE, CSN
const uint64_t pipe = 0xE6E6E6E6E6E6; //Transmission pipe

void setup(void)
{
  pinMode(SWITCH1_PIN, INPUT_PULLUP);
  digitalWrite(SWITCH1_PIN, HIGH);

  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe);
}

void loop(void)
{
  if (digitalRead(SWITCH1_PIN) == LOW)  // If Switch is Activated
  {
    SentMessage[0] = 111;
    radio.write(SentMessage, 1);
    digitalWrite(LED_PIN, LOW);
  }
  else {
    SentMessage[0] = 666;
    radio.write(SentMessage, 1);
    digitalWrite(LED_PIN, HIGH);
  }
}
