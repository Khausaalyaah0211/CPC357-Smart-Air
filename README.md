# CPC357-Smart-Air
Project Description
The SmartAir: IoT-Driven Smart Air Conditioning System is a smart energy optimization solution designed to address energy inefficiencies in urban spaces by leveraging the Internet of Things (IoT). This system integrates various hardware components, sensors, and cloud-based platforms to create a robust framework for intelligent air conditioning management. The aim is to reduce energy consumption, enhance environmental sustainability, and improve indoor safety and comfort.

Core Features
Human Presence Detection (PIR Sensor):
The PIR (Passive Infrared) sensor is the system's primary mechanism for detecting human presence. By sensing infrared radiation from humans, it determines whether a space is occupied. If motion is detected, the air conditioner (simulated by an LED) is triggered to turn on. Conversely, when no motion is detected, the system powers down, ensuring energy efficiency by eliminating unnecessary usage.

Environmental Monitoring (DHT Sensors):
Temperature and humidity sensors (DHT11/DHT22) continuously monitor environmental conditions. Based on real-time data, the system dynamically adjusts the air conditioning settings to maintain a comfortable indoor environment. For example, high temperatures activate a fan motor to simulate cooling, while low temperatures turn it off to conserve energy.

Gas Detection and Safety Monitoring (MQ2 Gas Sensor):
The MQ2 gas sensor monitors air quality, focusing on the detection of hazardous gases such as carbon monoxide. If unsafe levels are detected, the system triggers an immediate safety protocol, including sending email alerts to users via the V-One IoT platform. This functionality ensures occupant safety by providing early warnings of potential fire hazards or poor air quality.

Energy Efficiency and Smart Control:
The system is designed to operate only when necessary, minimizing energy consumption. Integration with a relay module allows the Maker Feather microcontroller to safely control the AC unit (simulated by an LED), ensuring seamless switching while protecting the electronic components from high voltage.

Data Storage and Analysis (V-One IoT Platform):
Sensor data is transmitted to the V-One IoT platform for cloud storage and analysis. Users can monitor environmental trends, air conditioning usage, and safety events through a web-based dashboard. This feature promotes long-term insights into energy usage patterns and environmental conditions, enabling further optimization.

Technical Overview
Hardware Components:

Maker Feather Microcontroller: Processes sensor data, communicates with the cloud, and controls the relay module.
PIR Sensor: Detects motion and triggers AC activation.
DHT11/DHT22 Sensor: Monitors temperature and humidity levels.
MQ2 Gas Sensor: Detects hazardous gases and sends safety alerts.
Relay Module: Acts as a switching mechanism for the simulated AC unit.
Fan Motor: Simulates the cooling effect.
LED: Indicates the AC unit’s status visually.
Software Tools:

Arduino IDE: Used to program the microcontroller for sensor integration, data processing, and control.
V-One IoT Platform: Provides cloud connectivity, data visualization, and an alerting system for user notifications.
Sustainability and Impact
The SmartAir system is aligned with the United Nations Sustainable Development Goals (SDGs), specifically:

Goal 7: Affordable and Clean Energy – By reducing energy consumption through smart automation, it promotes energy efficiency.
Goal 11: Sustainable Cities and Communities – The project fosters a sustainable urban lifestyle by integrating technology to reduce wasteful energy usage.
Goal 13: Climate Action – It addresses the issue of excessive carbon emissions by optimizing air conditioning usage, one of the major contributors to energy consumption in urban environments.
Challenges Addressed
Urban areas face rising energy demands, safety concerns due to poor air quality, and the need for smarter resource management. The SmartAir system is an innovative response to these challenges, demonstrating how IoT technology can tackle real-world issues effectively. Its scalability allows adaptation to various settings, including residential, commercial, and industrial environments.

Future Enhancements
Future iterations of the SmartAir system could include:

Integration with renewable energy sources like solar panels.
Machine learning algorithms for predictive maintenance and behavior-based energy optimization.
Advanced safety features, such as integration with fire suppression systems for industrial applications.

