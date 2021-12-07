#include <HCSR04.h>
#define UP D6
#define DOWN D7

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);

}

void loop() {
 while (Serial.available() > 0)
 {

   //Read the next available byte in the serial receive buffer
   char inByte = Serial.read();
   if (inByte == 'u') {
    Forward();
   } else if (inByte == 'd') {
    Backward();
   } else if (inByte == 's') {
    Stop();
   }
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
