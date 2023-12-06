# IoT Sensor Monitoring Project ( Minor-Project)

## Overview

This project involves monitoring environmental parameters using various sensors and transmitting the data to an MQTT broker. The data is then visualized in a web-based dashboard.

## Components

- **ESP8266 (NodeMCU):** Handles WiFi connectivity and MQTT communication.
- **DHT11 Sensor:** Measures temperature and humidity.
- **BMP280 Sensor:** Measures temperature, pressure, and altitude.
- **MQ135 Sensor:** Measures air quality.


## Dependencies

- **Arduino IDE:** Used to program the ESP8266 and Arduino Uno.
- **PubSubClient Library:** Enables MQTT communication on ESP8266.
- **Adafruit_BMP280 Library:** Supports BMP280 sensor.
- **DHT Sensor Library:** Supports DHT11 sensor.
- **(Any additional libraries for digital sensors)**

## Setup

1. **Hardware Setup:**
   - Connect DHT11, BMP280, and MQ135 sensors to the ESP8266.
   - Ensure proper power supply for all components.

2. **Arduino IDE:**
   - Upload the ESP8266 code to read DHT11, BMP280, and MQ135 data.
   - Upload the Arduino Uno code to read data from digital sensors.

3. **MQTT Broker:**
   - Set up an MQTT broker (e.g., Mosquitto) on a server or cloud platform.

4. **Web Dashboard:**
   - Host the HTML, CSS, and JavaScript files for the dashboard on a server or use a hosting service.

5. **Configure:**
   - Update WiFi credentials, MQTT broker details, and sensor pins in the ESP8266 code.
   - Configure the dashboard to subscribe to the appropriate MQTT topics.

## Usage

1. Power up the system.
2. Sensor data is transmitted to the MQTT broker.
3. The web dashboard displays real-time sensor readings.
4. Set up alerts for specific thresholds in the dashboard.

## Additional Notes

- **Customization:**
  - Customize the dashboard and alerts based on your preferences.
  
- **Security:**
  - Ensure secure practices, especially if deploying the system in a public network.

## Acknowledgments

- Mention any third-party libraries, resources, or inspirations used.

