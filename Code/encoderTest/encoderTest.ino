#include <HCSR04.h>
#define UP D6
#define DOWN D7

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
bool wasLow = false;

int ticks = 0;
int tickStop = 0;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
}

void loop() {
  sensorValue = analogRead(analogInPin);

//  Serial.print("sensor = ");
//  Serial.println(sensorValue);
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
      tickStop = ticks + 50;
      Forward();
      Serial.print("stopping at: ");
      Serial.println(tickStop);
    } else if (inByte == 'd') {
      tickStop = ticks + 50;
      Backward();
      Serial.print("stopping at :");
      Serial.println(tickStop);
    }
  }

  if (tickStop < ticks) {
    Stop();
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
  analogWrite(UP, LOW);
  digitalWrite(DOWN, LOW);
}
