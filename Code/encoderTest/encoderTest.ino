#include <HCSR04.h>
#define UP D6
#define DOWN D7
#define LED1 D5
#define LED2 D4
#define LED3 D8

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
bool wasLow = false;

int ticks = 0;
int tickStop = 0;

int ledState = LOW;

unsigned long previousMillis = 0;


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

}

void loop() {
  sensorValue = analogRead(analogInPin);

  //Serial.print("sensor = ");
  //Serial.println(sensorValue);
  if (sensorValue > 500 && wasLow == true) {
    wasLow = false;
    ticks++;
    Serial.print("ticks = ");
    Serial.println(ticks);
  } else if (sensorValue < 500 && wasLow == false) {
    wasLow = true;
  }

  while (Serial.available() > 0)
  {

    //Read the next available byte in the serial receive buffer
    char inByte = Serial.read();
    if (inByte == 'u') {
      tickStop = ticks + 65;
      Forward();
      Serial.print("stopping at: ");
      Serial.println(tickStop);
    } else if (inByte == 'd') {
      tickStop = ticks + 65;
      Backward();
      Serial.print("stopping at :");
      Serial.println(tickStop);
    }
  }

  if (tickStop < ticks) {
    Brake();
    delay(10);
    Stop();
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
void Brake() {
  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, HIGH);
}
void Stop() {
  digitalWrite(UP, LOW);
  digitalWrite(DOWN, LOW);
}
