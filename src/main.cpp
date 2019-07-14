#include "MasterConfig.h"

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

IPAddress ipAddress;
EthernetClient ethClient;

uint32_t lastTcpPublishTime = 0;
uint8_t buffer[512];

void macCharArrayToBytes(const char* str, byte* bytes) {
    for (int i = 0; i < 6; i++) {
        bytes[i] = strtoul(str, NULL, 16);
        str = strchr(str, ':');
        if (str == NULL || *str == '\0') {
            break;
        }
        str++;
    }
}

/*
 * Wiz W5500 reset function
 */
void ethernetWizReset(const uint8_t resetPin) {
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, HIGH);
    delay(250);
    digitalWrite(resetPin, LOW);
    delay(50);
    digitalWrite(resetPin, HIGH);
    delay(350);
}

void connectEthernet() {
    delay(500);
    byte* mac = new byte[6];
    macCharArrayToBytes(ETHERNET_MAC, mac);
    ipAddress.fromString(ETHERNET_IP);

    Ethernet.init(ETHERNET_CS_PIN);
    ethernetWizReset(ETHERNET_RESET_PIN);

    Serial.println("Starting ETHERNET connection...");
    Ethernet.begin(mac, ipAddress);
    delay(200);

    Serial.print("Ethernet IP is: ");
    Serial.println(Ethernet.localIP());
}

void connectToServer() {
    Serial.println("Connecting to TCP server...");
    while (!ethClient.connect(TCP_HOSTNAME, TCP_PORT))  {
      Serial.println("Connection failed. Reconnecting...");
      delay(1000);
    }
    Serial.println("Connected to TCP server");
}

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32_W5500_TCP");
  connectEthernet();
  connectToServer();
}

void loop() {


  if (ethClient.available()) {
    char c = ethClient.read();
    Serial.print(c);
  }

  uint32_t now = millis();
  if (now - lastTcpPublishTime > TCP_PUBLISH_INTERVAL_MS) {
    String uptimeInSec = String(now/1000);
    Serial.print("Sending another batch of messages to TCP server.");
    Serial.print(" uptime = ");
    Serial.println(uptimeInSec);

    String uptimeMessage = "1. This is uptime message to be sent to TCP server. Uptime = " + uptimeInSec + "\n";
    ethClient.write(uptimeMessage.c_str());
    ethClient.write("2. This is another message to send more and check if it ifluence stability\n");
    ethClient.write("3. One more check if it ifluence stability\n", 43);
    ethClient.write("4. End even more more and check if it ifluence stability\n", 57);
    ethClient.write("5. More More More MOre moRE More More More MOre moRE More More More MOre moRE More More More MOre moRE\n", 103);
    ethClient.write("6. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam id orci ex\n", 78);
    ethClient.write("7. enean pellentesque lectus vitae erat tempus, vel gravida lacus imperdiet\n", 76);

    if (!ethClient.connected()) {
      Serial.println("Client disconnected...");
      connectToServer();
    }
    lastTcpPublishTime = now;
  }
}