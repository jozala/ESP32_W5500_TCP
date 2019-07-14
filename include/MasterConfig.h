#define ETHERNET_MAC            "BA:E5:E3:B1:44:DD" // Ethernet MAC address (have to be unique between devices in the same network)
#define ETHERNET_IP             "10.0.88.244"       // IP address of RoomHub when on Ethernet connection

#define ETHERNET_RESET_PIN      13      // ESP32 pin where reset pin from W5500 is connected
#define ETHERNET_CS_PIN         5       // ESP32 pin where CS pin from W5500 is connected

#define TCP_HOSTNAME           "10.0.88.87"
#define TCP_PORT               6789

#define TCP_PUBLISH_INTERVAL_MS   1000