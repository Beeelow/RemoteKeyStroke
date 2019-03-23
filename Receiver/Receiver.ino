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
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01

    if (ReceivedMessage[0] == 111) // Switch 1 is pressed - Lock Computer.
    {
      digitalWrite(LED_PIN, LOW);
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('l');
      Keyboard.releaseAll();
    }
    else if (ReceivedMessage[0] == 222) // Switch 2 is pressed - Minimize all windows.
    {
      digitalWrite(LED_PIN, LOW);
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.write('d');
      Keyboard.releaseAll();
    }
    delay(10);
  }
}
