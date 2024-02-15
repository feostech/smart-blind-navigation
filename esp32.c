#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SSID";
const char* password = "SSID-password";
const char* mqtt_server = "IP-Address";
const uint16_t mqtt_server_port = 1883;
const char* mqttTopic = "Topic-name";

const int trigPin = 5;
const int echoPin = 18;
const int ledPin = 2;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

long duration;
float distance;

void setup() {
Serial.begin(115200);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(ledPin, OUTPUT);
setup_wifi();
mqttClient.setServer(mqtt_server, mqtt_server_port);
}

void setup_wifi() {
delay(10);
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("WiFi connected");
}

void reconnect() {
while (!mqttClient.connected()) {
Serial.print("Attempting MQTT connection...");
if (mqttClient.connect("ESP32Client")) {
Serial.println("connected");
} else {
Serial.print("failed, rc=");
Serial.print(mqttClient.state());
Serial.println(" try again in 5 seconds");
delay(5000);
}
}
}

float measureDistance() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration * 0.034 / 2;
return distance;
}

void loop() {
if (!mqttClient.connected()) {
reconnect();
}
mqttClient.loop();

float measuredDistance = measureDistance();
Serial.print("Distance (cm): ");
Serial.println(measuredDistance);

char payload[10];
dtostrf(measuredDistance, 4, 2, payload);
mqttClient.publish(mqttTopic, payload);
if (measuredDistance <= 100) {
digitalWrite(ledPin, HIGH); // Turn on LED
} else {
digitalWrite(ledPin, LOW); // Turn off LED
}
delay(1000);
}

