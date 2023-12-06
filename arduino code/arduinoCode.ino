#ifdef ESP8266
#include <ESP8266WiFi.h> /* WiFi library for ESP8266 */
#else
#include <WiFi.h> /* WiFi library for ESP32 */
#endif

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include "DHT.h"
#include <PubSubClient.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define DHTPIN 2    // D2 on the NodeMCU ESP8266 for DHT11
#define DHTTYPE DHT11
#define MQ135_PIN A0

const char *wifi_ssid = "xxxxxxxxxxx";
const char *wifi_password = "xxxxxxxxxxx";
// const char *mqtt_server = "91.121.93.94";
const char *mqtt_server = "192.168.xxx.xxx";
const int mqtt_port = 1883;
const char *mqtt_client_id = "weatherstation1";

Adafruit_BMP280 bme; // I2C
DHT dht(DHTPIN, DHTTYPE);
int mq135Pin = MQ135_PIN;

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("BMP280 + DHT11 + MQ135 test"));

  

  if (!bme.begin(0x76))
  {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  connectWiFi();
  client.setServer(mqtt_server, mqtt_port);
  connectMQTT();
  dht.begin();
}

void loop()
{
  float temperatureBMP = bme.readTemperature();
  float pressure = bme.readPressure() /100;
  float altitude = bme.readAltitude(101325.0) /100;
  float humidityDHT = dht.readHumidity();
  float temperatureDHT = dht.readTemperature();
  int airQualityValue = analogRead(mq135Pin);

  publishData("sensor/BMP280/temperature", String(temperatureBMP).c_str());
  publishData("sensor/BMP280/pressure", String(pressure).c_str());
  publishData("sensor/BMP280/altitude", String(altitude).c_str());
  publishData("sensor/DHT11/humidity", String(humidityDHT).c_str());
  publishData("sensor/DHT11/temperature", String(temperatureDHT).c_str());
  publishData("sensor/MQ135/air_quality", String(airQualityValue).c_str());

  Serial.println();
  delay(2000);
}

void connectWiFi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    if (client.connect(mqtt_client_id))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void publishData(const char *topic, const char *payload)
{
  if (client.connected())
  {
    Serial.print("Publishing to ");
    Serial.print(topic);
    Serial.print(": ");
    Serial.println(payload);

    client.publish(topic, payload, true);
  }
}

