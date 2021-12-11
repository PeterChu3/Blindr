#include <HCSR04.h>
#define UP D6
#define DOWN D7

#define LED1 D5
#define LED2 D4
#define LED3 D8

int ledState = LOW;

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
//  pinMode(LED1, OUTPUT);
//  pinMode(LED2, OUTPUT);
//  pinMode(LED3, OUTPUT);


}

void loop() {
  while (Serial.available() > 0)
  {

    //Read the next available byte in the serial receive buffer
    char inByte = Serial.read();
    if (inByte == 'u') {
      Serial.println("up");
      Forward();
    } else if (inByte == 'd') {
      Serial.println("down");
      Backward();
    } else if (inByte == 's') {
      Serial.println("stop");
      Stop();
    }
  }
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED1, ledState);
    digitalWrite(LED2, ledState);
    digitalWrite(LED3, ledState);
  }
}
void Forward() {
  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, LOW);
}
void Backward() {
  digitalWrite(UP, LOW);
  digitalWrite(DOWN, HIGH);
}
void Stop() {
  digitalWrite(UP, LOW);
  digitalWrite(DOWN, LOW);
}
