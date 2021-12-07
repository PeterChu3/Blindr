#include <ESP8266WebServer.h>

// Wifi config
#define HTTP_REST_PORT 80
const char *ssid = "apt1050-4";
const char *password = "Newrouter1873";
const String deviceName = "Blindr";
ESP8266WebServer http_rest_server(HTTP_REST_PORT);

const int GEAR_RATIO = 2;           // Gear ratio of the blind gear to motor (2:1)
const int NUM_ENCODER_HOLES = 10;    // Number of holes in the encoder wheel (10 = 1 rotation)

#define UP D6
#define DOWN D7

#define CLOSED_UP 0
#define OPEN 1
#define CLOSED_DOWN 2

#define DEBUG 1

// Can be open (blinds horizontal) or closed (blinds vertical)
// Closed can be up or down (concave up or concave down)
int currentState = OPEN;
int nextState = OPEN;

const int analogInPin = A0;   // Sensor pin
int sensorValue = 0;          // Value read from the sensor
bool wasLow = false;          // Was the sensor low last time we checked?

int ticks = 0;               // Number of ticks since last movement
int tickStop = 0;            // Number of ticks to stop motor at
void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);

  // Webserver init
  #ifdef DEBUG
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  #endif

  WiFi.hostname(deviceName);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    // Wait a bit and then try again
    delay(500);
    #ifdef DEBUG
        Serial.print(".");
    #endif
  }

  #ifdef DEBUG
    Serial.println("");
    Serial.println("WiFi connected");
  #endif

  // Set routes
  configureRouter();

  // Start the server
  http_rest_server.begin();

  #ifdef DEBUG
    Serial.println("Server started");
    // Print the IP address
    Serial.print("Use this URL : ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
  #endif

}

void loop() {
  // Count encoder ticks
  sensorValue = analogRead(analogInPin);
  // #ifdef DEBUG
  //   Serial.print("Sensor value: ");
  //   Serial.println(sensorValue);
  // #endif
  if (sensorValue > 500 && wasLow == true) {
    wasLow = false;
    ticks++;
    // #ifdef DEBUG
    //   Serial.print("Ticks: ");
    //   Serial.println(ticks);
    // #endif
  } else if (sensorValue < 500 && wasLow == false) {
    wasLow = true;
  }

  // Check if we need to move the blinds/they are moving
  if (currentState != nextState) {
    if (ticks >= tickStop) {
      // Finished transitioning to nextState
      Stop();
      currentState = nextState;
    }
  }
}

void configureRouter() {
  // http_rest_server.on("/name", HTTP_GET, getDeviceName);
  http_rest_server.on("/", HTTP_GET, getState);
  http_rest_server.on("/", HTTP_POST, changeState);
}

// HTTP server helpers
String getStateText() {
  return currentState == OPEN ? "open" : "closed";
}
void getState() {
  http_rest_server.send(200, "text/plain", getStateText());
}

void changeState() {
  String post_body = http_rest_server.arg("plain");
  // Ensure the body is correct
  if (post_body != "0" || post_body != "1" || post_body != "2") {
    http_rest_server.send(400, "text/plain", "Invalid state");
    return;
  }
  int newState = post_body.toInt();
  currentState = newState;
  moveTo(newState);
  http_rest_server.send(200, "text/html", getStateText());
}

// Motor control helpers
void moveTo(int newState) {
  if (newState == currentState) {
    return;
  }
  int numRotations = currentState - newState;
  bool isForward = numRotations > 0;
  // Rotations always positive now that we have determined direction
  if (numRotations < 0) {
    numRotations = -numRotations;
  }
  // Start transition to newState
  ticks = 0;
  tickStop = numRotations * NUM_ENCODER_HOLES * GEAR_RATIO;
  if (isForward) {
    Forward();
  } else {
    Backward();
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
