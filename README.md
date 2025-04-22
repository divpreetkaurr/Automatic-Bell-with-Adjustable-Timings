# 🔔 Automatic Bell with Adjustable Timings | Arduino Project

This project is a **real-time automatic bell system** built using Arduino Uno. It allows users to set multiple custom bell timings via a 4x4 matrix keypad, displays real-time clock on a 16x2 LCD, and uses a buzzer to ring bells based on stored schedules. Perfect for schools, colleges, or factories!

---

## 📌 Project Description

This system replaces manual bell ringing with an automatic solution. The user sets the current time and adds up to 10 custom bell timings using a keypad. The system uses the **DS3231 RTC module** to keep track of the current time accurately and rings the buzzer automatically when the bell time matches the system time. The bell timings are saved in EEPROM, so they remain even after power reset. The LCD shows live date and time, and the keypad offers a user-friendly interface to set everything easily.

---

## 🛠️ Components Used

- **Arduino Uno R3** – Microcontroller to run the project logic.
- **DS3231 RTC Module** – Provides real-time clock with battery backup.
- **16×2 LCD with I2C** – Displays time, date, and menu prompts.
- **4×4 Matrix Keypad** – For user input (set time, bell times, etc.).
- **Buzzer** – Rings during scheduled bell times.
- **Jumper Wires** – For circuit connections.

---

## ✨ Features

- ⏰ Displays current date and time on LCD.
- 🔢 Set up to **10 custom bell times**.
- 💾 Bell schedule stored in EEPROM (no data loss on reset).
- 🔘 Keypad menu interface to set time and bells.
- 🔇 Buzzer can be stopped during ringing via keypad.
- 🔄 Real-time auto-check every second for bell trigger.

---

## 🧠 Learning Outcomes

- Interfacing real-time clock, LCD, and keypad with Arduino.
- Building a menu-driven UI for microcontrollers.
- EEPROM read/write for persistent memory usage.
- Scheduling with precise timing logic.
- Modular programming and hardware-software integration.

---

## ⚙️ Working

1. LCD displays real-time date and time.
2. Press `*` on the keypad to enter the menu.
3. Choose to:
   - `1`: Set the current time and date.
   - `2`: Set bell timings (hour and minute).
4. The system checks the time every second.
5. When a match occurs, the buzzer rings automatically.
6. Press `B` during buzzer ringing to stop it manually.

---

## 📸 Images / Circuit Diagram
![image](https://github.com/user-attachments/assets/8e3a0596-ae40-45c8-9483-63c436ed5445)
circuit daigram
![image](https://github.com/user-attachments/assets/ee565642-91ee-4de0-8aff-8a211bfbf943)
when system is connected to USB 
![image](https://github.com/user-attachments/assets/fc5df523-16df-43e5-99e1-bbb18d2b6bbe)
On pressing *, this menu appears
![image](https://github.com/user-attachments/assets/31c8d9ff-dd82-40d0-b6ee-e4a8581c705c)
on pressing 1, setting of date and time is done via keypad
![image](https://github.com/user-attachments/assets/a5c65f26-82b0-45d9-a4b5-b7b766b52d6c)
enter number of bells you want to buzz

---
