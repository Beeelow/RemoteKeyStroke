//Used to send switch activation codes to receiver in order for receiver to enter keystrokes.
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

#define SWITCH1_PIN 2
#define SWITCH2_PIN 3
#define LED_PIN 17 //Onboard LED

int SentMessage[1] = {000};
RF24 radio(9, 10); //CE, CSN
const uint64_t pipe = 0xE6E6E6E6E6E6; //Transmission pipe
int Previous_Switch1_State = HIGH;
int Previous_Switch2_State = HIGH;

void setup(void)
{
  //Initialize Buttons
  pinMode(SWITCH1_PIN, INPUT_PULLUP);
  digitalWrite(SWITCH1_PIN, HIGH);
  pinMode(SWITCH2_PIN, INPUT_PULLUP);
  digitalWrite(SWITCH2_PIN, HIGH);

  //Initialize Radio
  radio.begin(); 
  radio.openWritingPipe(pipe);
  radio.setChannel(80);
  radio.setDataRate(RF24_1MBPS);
  radio.powerUp();
}

void loop(void)
{
  //Send data based upon switch activation
  if (digitalRead(SWITCH1_PIN) == LOW && Previous_Switch1_State == HIGH)  // If Switch 1 is Activated - we only want to sent one key combo at a time.
  {
    SentMessage[0] = 111;
    radio.write(SentMessage, 1);
    digitalWrite(LED_PIN, LOW);
    Previous_Switch1_State = LOW;
  }
  else if (digitalRead(SWITCH2_PIN) == LOW && Previous_Switch2_State == HIGH)  // If Switch 2 is Activated - we only want to sent one key combo at a time.
  {
    SentMessage[0] = 222;
    radio.write(SentMessage, 1);
    digitalWrite(LED_PIN, LOW);
    Previous_Switch2_State = LOW;
  }
  else 
  {
    SentMessage[0] = 000;
    radio.write(SentMessage, 1);
    digitalWrite(LED_PIN, HIGH);
  }
  
  //Reset previous switch states when switches are released.
  if (digitalRead(SWITCH1_PIN) == HIGH && Previous_Switch1_State == LOW)
  {
      Previous_Switch1_State = HIGH;
  }
  
  if (digitalRead(SWITCH2_PIN) == HIGH && Previous_Switch2_State == LOW)
  {
      Previous_Switch2_State = HIGH;
  }
}
