# 🍱 Food Spoilage Detection System

A real-time food spoilage detection system using **gas sensors**, **DHT11**, **LCD**, **buzzer**, and **LED indicators** to monitor environmental conditions and detect spoilage-causing gases. Designed for smart fridges, food storage, or supply chain monitoring.

## 📌 Features
- Detects **flammable gases** (LPG, methane) using **MQ2** and **MQ6 sensors**
- Monitors **temperature** and **humidity** using **DHT11**
- Triggers **alerts** via buzzer and LEDs when gas thresholds are crossed
- Displays readings on **16x2 LCD**
- Sends data over **Serial** for logging or monitoring

## 🧠 Core Functionality
- If MQ2 or MQ6 detects gas (limit reached), buzzer sounds and Red LED turns ON.
- Green LED indicates normal air conditions.
- Displays live values of gas, temperature (°C), and humidity (%) on the LCD.
- Sends comma-separated sensor data to Serial Monitor in this format:
