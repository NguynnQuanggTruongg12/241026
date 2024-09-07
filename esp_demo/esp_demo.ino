#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

//----Thay đổi thành thông tin của bạn---------------
const char* ssid = "Q.Truong";      // Wifi SSID
const char* password = "123456667";   // Wifi Password

const char* mqtt_server = "604b372efa0e444ebbe062ca5d3e2243.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_username = "truong"; // MQTT Username
const char* mqtt_password = "Lhh12345@@"; // MQTT Password
//--------------------------------------------------

WiFiClientSecure espClient;
PubSubClient client(espClient);

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
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientID = "ESPClient-";
    clientID += String(random(0xffff), HEX);
    if (client.connect(clientID.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("esp8266/client"); // Subscribing to the topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Callback to handle received messages
void callback(char* topic, byte* payload, unsigned int length) {
  String incomingMessage = "";
  for (int i = 0; i < length; i++) {
    incomingMessage += (char)payload[i];
  }
  // Serial.println("Message arrived [" + String(topic) + "]: " + incomingMessage);

  if (incomingMessage == "START") {
    // Code to handle "START" command
    Serial.println("START.");
  } else if (incomingMessage == "STOP") {
    // Code to handle "STOP" command
    Serial.println("STOP.");
  }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  espClient.setInsecure();  // Allow insecure connection for SSL
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
