ESP32 Environment & Security Monitor

An ESP32-based embedded system that monitors environmental conditions and reacts dynamically using multiple sensors, audio feedback, relay control, and an OLED display.

Features

Real-time temperature and humidity monitoring (DHT11)

Ambient light level detection (LDR)

Motion detection using PIR sensor

Obstacle detection via IR sensor

State-based system logic: Sleep / Normal / Stress / Threat

Passive buzzer feedback on state changes

Active buzzer alarms during threat conditions

Relay control for external devices

Live data visualization on I2C OLED display

Hardware Components

ESP32 Development Board

DHT11 Temperature & Humidity Sensor

LDR (Photoresistor) Module

PIR Motion Sensor

IR Obstacle Avoidance Sensor

I2C OLED Display (SSD1306)

Passive Buzzer

Active Buzzer

2-Channel Relay Module

Jumper wires and breadboard

Pin Configuration
Component	ESP32 Pin
DHT11 Data	GPIO 4
LDR (Analog)	GPIO 36
PIR Sensor	GPIO 27
Obstacle Sensor (DO)	GPIO 26
Passive Buzzer	GPIO 18
Active Buzzer	GPIO 19
Relay	GPIO 25
OLED SDA	GPIO 21
OLED SCL	GPIO 22
Software Requirements

Arduino IDE

ESP32 Board Support Package

Adafruit SSD1306 Library

Adafruit GFX Library

DHT Sensor Library

System Logic

The system continuously reads sensor data and determines the current operating mode:

Sleep: Low temperature, low light, no motion

Normal: Default state

Stress: High temperature combined with motion

Threat: Low light with motion or obstacle detection

Mode changes trigger a passive buzzer notification, while active threat conditions enable continuous alarm output and relay activation.

Display Output

The OLED screen shows:

Temperature and humidity values

Ambient light level

Motion detection status

Obstacle detection status

Current system mode

Notes

Due to the limited quality and precision of the sensors used, occasional noisy readings, unstable values, or missed detections may occur. This behavior is expected and acceptable within the scope of this prototype.

Possible Improvements

Sensor data filtering (moving average, debounce)

WiFi-based monitoring interface

Mobile or web dashboard

Data logging to SD card or cloud

Improved sensors for higher accuracy

