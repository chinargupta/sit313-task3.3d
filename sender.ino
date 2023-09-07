#include <ArduinoMqttClient.h>
#include <ArduinoBLE.h>
#include <BLEClient.h>


const char ssid[] = "Chinar";      // your network SSID
const char pass[] = "gupta123";  // your network password

BLEClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "mqtt-dashboard.com";
int port = 1883;
const char topic[] = "chinar";

const int trigPin = 8;
const int echoPin = 9;

float duration, distance;

const long interval = 1000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  }

  // Attempt to connect to WiFi network:
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  while (!BLE.begin()) {
    // BLE initialization failed, retry
    Serial.println("Starting BLE failed!");
    delay(5000);
  }

  Serial.println("BLE started successfully");

  // You can provide a unique client ID, if not set, the library uses Arduino-millis()
  // Each client must have a unique client ID
  // mqttClient.setId("clientId");

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  // Call poll() regularly to allow the library to receive MQTT messages and
  // send MQTT keep-alive messages to avoid being disconnected by the broker
  mqttClient.poll();

  // To avoid having delays in loop, we'll use the strategy from BlinkWithoutDelay
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time a message was sent
    previousMillis = currentMillis;

    // Your distance measurement code here
    // ...

    if (distance < 12) {
      // Send message, the Print interface can be used to set the message contents
      mqttClient.beginMessage(topic);
      mqttClient.print("Sohil Nagpal: Wave is detected, ");
      mqttClient.print("Distance: ");
      mqttClient.print(distance);
      mqttClient.endMessage();
      delay(1000);
    }

    Serial.println();

    count++;
  }
}
