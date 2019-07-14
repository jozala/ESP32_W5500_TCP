ESP32_W5500_TCP
===============

Simple example of using Arduino Ethernet library with ESP32 and W5500 to send messages to TCP server.
This project periodically sends batch of messages to TCP server.

IMPORTANT: 
**It has been created to present intermittent connection problems which seems to occur on W5500.**

## Physical connection between ESP32 and W5500

* GPIO23 <--> MOSI
* GPIO19 <--> MISO
* GPIO18 <--> SCLK
* GPIO5  <--> SCS
* GPIO13 <--> RESET

It is possible to change pins used for chip-select and reset in 
`include/MasterConfig.h` file.


## Configuration

Fixed IP address of the device (`ETHERNET_IP`) and MQTT hostname (`MQTT_HOSTNAME`) should most probably be changed in `include/MasterConfig.h` to fit your setup.
Changing other configurations in `MasterConfig.h` is optional.


## Running the test

It has been prepared as PlatformIO project. All dependencies will be automatically downloaded if run with PlatformIO.

Complementary TCP server has been implemented in Java and can be run either with Java or as a Docker container. For more information see 
https://github.com/maniekq/servertcp-esp32 .
You can start TCP server quickly with:
```
docker run -p 6789:6789 --name servertcp -d maniekq/servertcp-esp32
```

### Expected results:
Batch of messages, send by ESP32, should be received exectly as is on the TCP server.


### Actual results:
Usually after few hours, some messages are not send properly to TCP server. 
Instead of the correct message, TCP server receives some "gibberish" content.
See network packets dump in "wireshark-dump/raw_TCP_incorrect_packet.pcapng" (packet 91).