# 🎯 STM32 Lightgun Controller (IR-Based)

A **custom-built lightgun controller** inspired by classic systems like the NES Zapper and modern designs like the Wii Remote, using **IR tracking, STM32 microcontroller, and real-time input processing**.

---

## 🚀 Project Overview

This project focuses on building a **low-latency lightgun system** capable of accurately detecting screen position and translating it into interactive input for games.

The system leverages:

* **Infrared (IR) tracking** for positional accuracy
* **STM32 microcontroller (Bluepill)** for real-time processing
* **Sensor fusion and input handling** for enhanced interaction

---

## 🎯 Objectives

* Develop an **IR-based positional tracking system**
* Implement **low-latency input processing** using STM32
* Enable **trigger-based shooting mechanics**
* Integrate **motion sensing** for additional interactions (e.g., reload)
* Support **wired and wireless connectivity**

---

## 🧠 System Architecture

### 🔦 IR Tracking System

* Uses **IR camera module** to detect IR LEDs from a sensor bar
* Calculates relative position on screen in real-time

### 🎮 Input System

* Trigger → primary shooting input
* Buttons → secondary actions

### 🧭 Motion Sensing

* MPU6050 (Gyroscope + Accelerometer)
* Used for:

  * Off-screen detection
  * Reload gestures

### 🔊 Feedback System

* Speaker + amplifier for **audio feedback**

---

## ⚙️ Tech Stack

### 💻 Software

* Embedded C (Bare-metal programming)
* STM32 HAL / Register-level programming

### 🔌 Hardware

* STM32 Bluepill / Blackpill
* IR Camera Module (DFRobot SEN0188)
* IR LED Emitter
* MPU6050 (Gyroscope + Accelerometer)
* nRF24L01 (Wireless Module)
* Trigger Switch + Push Buttons
* Speaker + Amplifier
* USB Interface

---

## 🔧 Features

* 🎯 Real-time IR-based position tracking
* ⚡ Low-latency input handling
* 🔫 Trigger-based shooting mechanism
* 🧭 Motion-based reload system
* 📡 Optional wireless connectivity
* 🔊 Audio feedback integration

---

## 🏗️ Hardware Components

| Component         | Purpose                     |
| ----------------- | --------------------------- |
| STM32 (Bluepill)  | Main controller             |
| IR Camera         | Detect IR light sources     |
| IR LED            | Position tracking reference |
| MPU6050           | Motion sensing              |
| nRF24L01          | Wireless communication      |
| Trigger & Buttons | User input                  |
| Speaker           | Audio feedback              |

---

## 📷 photos

*Add images of assembled lightgun here*
<img width="1579" height="1536" alt="Lightgun1" src="https://github.com/user-attachments/assets/1bbc11b0-81aa-4b24-b2c3-35bb7b7bf4f5" />

---

## 🧪 Current Status

🚧 **Work in Progress**

* [x] System design finalized
* [ ] IR tracking implementation
* [ ] STM32 peripheral setup (GPIO, I2C, SPI)
* [ ] Motion sensing integration
* [ ] Wireless communication
* [ ] Game integration

---

## 🔮 Future Enhancements

* 🎮 Integration with PC games / emulators
* 🧠 Sensor fusion for improved accuracy
* 📡 Full wireless mode with low latency
* 🔋 Battery-powered portable design
* 🖥️ Calibration software for precision tuning

---

## 💡 Inspiration

* NES Zapper
* Wii Remote (IR tracking system)

---

## 📚 References

* STM32 Documentation
* MPU6050 Datasheet
* nRF24L01 Documentation
* IR Tracking Systems (Wii Controller Architecture)

---

## 👨‍💻 Author

**R. Haricharan**
🔗 GitHub: [https://github.com/Haricharan2012](https://github.com/Haricharan2012)

---


