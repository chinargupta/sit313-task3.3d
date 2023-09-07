#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

char ssid[] = "Chinar";        // your network SSID
char pass[] = "gupta123";    // your network password

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "mqtt-dashboard.com";
int port = 1883;
const char topic[] = "chinar";

const int ledPin = 8; // Use a specific pin number for your LED

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // Attempt to connect to the Wi-Fi network:
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // Failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // Set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // Subscribe to a topic
  mqttClient.subscribe(topic);

  Serial.print("Topic: ");
  Serial.println(topic);

  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Call poll() regularly to allow the library to receive MQTT messages and
  // send MQTT keep-alive messages to avoid being disconnected by the broker
  mqttClient.poll();
  
  // Your LED control logic here, e.g., blink the LED
  if (millis() % 2000 < 1000) {
    digitalWrite(ledPin, HIGH); // Turn on LED for 1 second
  } else {
    digitalWrite(ledPin, LOW);
  }
}

// Callback function for MQTT messages
void onMqttMessage(int messageSize) {
  // Handle incoming MQTT messages here if needed
}
