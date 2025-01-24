#include <DHT.h>
#include "VOneMqttClient.h"

// Define device IDs for telemetry data
const char* PIR_SENSOR_ID = "c09754e3-6a6f-444b-a7e9-443af90a6b84";
const char* TEMP_SENSOR_ID = "35a61e42-e2b0-485a-82f1-e6344a9494e9";
const char* GAS_SENSOR_ID = "61e172a1-d836-43b0-bbef-01dfe1768ef8";  
const char* Relay = "b5b556f9-f0a8-4c1e-ae59-1a924cfdde7f";
const char* LEDLight1 = "ab7df60b-512f-4025-af75-4df85f2b5326";

// Pin Definitions
const int PIR_PIN = A4;            
const int DHT_PIN = 42;            
const int FAN_PIN = 39;            
const int LED_PIN = 10;            
const int GAS_PIN = A2;            

const int GAS_THRESHOLD = 300;     

#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

const float HIGH_TEMP_THRESHOLD = 25.0;
const float LOW_TEMP_THRESHOLD = 22.0;

VOneMqttClient voneClient;

unsigned long lastMsgTime = 0;
const unsigned long TELEMETRY_INTERVAL = 5000;  

bool acOn = false;

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendEmailAlert() {
  Serial.println("High gas levels detected! Sending email alert...");
  String alertMessage = "Warning: High levels of gas detected (possible carbon monoxide or fire hazard). Please check the room!";
  voneClient.publishTelemetryData(GAS_SENSOR_ID, "Alert", alertMessage.c_str());
}

void triggerActuator_callback(const char* actuatorId, const char* command) {
  // Handle actuator commands here
  Serial.println("Actuator callback triggered.");
  Serial.print("Actuator ID: ");
  Serial.println(actuatorId);
  Serial.print("Command: ");
  Serial.println(command);
}


void setup() {
  setup_wifi();
  voneClient.setup();
  voneClient.registerActuatorCallback(triggerActuator_callback);

  dht.begin();

  pinMode(PIR_PIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(GAS_PIN, INPUT);

  digitalWrite(FAN_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.println("System initialized...");
}

void loop() {
  if (!voneClient.connected()) {
    voneClient.reconnect();
    voneClient.publishDeviceStatusEvent(PIR_SENSOR_ID, true);
  }
  voneClient.loop();

  bool motionDetected = digitalRead(PIR_PIN);
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Error reading temperature data!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  int gasLevel = analogRead(GAS_PIN);
  Serial.print("Gas level: ");
  Serial.println(gasLevel);

  if (gasLevel > GAS_THRESHOLD) {
    sendEmailAlert();
  }

  if (motionDetected) {
    Serial.println("Motion detected. Turning on AC...");
    acOn = true;
  } else {
    Serial.println("No motion detected. Turning off AC...");
    acOn = false;
  }

  if (acOn) {
    digitalWrite(LED_PIN, HIGH);  
    if (temperature > HIGH_TEMP_THRESHOLD) {
      Serial.println("High temperature detected. Turning on fan...");
      digitalWrite(FAN_PIN, HIGH);
    } else if (temperature < LOW_TEMP_THRESHOLD) {
      Serial.println("Low temperature detected. Turning off fan...");
      digitalWrite(FAN_PIN, LOW);
    }
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - lastMsgTime > TELEMETRY_INTERVAL) {
    lastMsgTime = currentMillis;
    voneClient.publishTelemetryData(PIR_SENSOR_ID, "Motion", motionDetected ? "true" : "false");
    voneClient.publishTelemetryData(TEMP_SENSOR_ID, "Temperature", temperature);
    voneClient.publishTelemetryData(GAS_SENSOR_ID, "Gas detector", gasLevel);
  }

  delay(2000);  
}
