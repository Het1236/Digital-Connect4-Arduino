

# Digital Connect 4 with Arduino Mega (Dual-Board)
 A dual-Arduino version of Connect 4 using LEDs and serial communication.

This project is a digital recreation of the classic Connect 4 game using **two Arduino Mega boards**, each controlling one color of LEDs. The game is controlled via **Serial Monitors on two laptops**, and utilizes **Serial1 communication (pins 18/19)** between Arduinos to synchronize turns and moves.

---

## 🎮 Features

- 5-row × 6-column LED grid (30 LEDs per board)
- Red and Yellow player LEDs controlled by two Arduino Mega boards
- Turn-based system with **alternate turns**
- Automatic **win detection** (horizontal, vertical, diagonal)
- LED animation on winning
- No buttons — input through Serial Monitor
- Uses `Serial1` (TX1/RX1) for cross-board communication

---

## ⚙️ Hardware Requirements

- 2 × Arduino Mega
- 60 × LEDs (30 red, 30 yellow)
- 60 × Resistors (~220Ω)
- Jumper wires
- Breadboards or a general purpose board
- Common ground between both Arduinos
- Serial connection via USB (for Serial Monitor inputs)

---

## 🔌 Wiring (LED Pins Mapping per Board)

| Row Index | Digital Pins           |
|-----------|------------------------|
| Row 0     | 46, 47, 48, 49, 50, 51 |
| Row 1     | 40, 41, 42, 43, 44, 45 |
| Row 2     | 34, 35, 36, 37, 38, 39 |
| Row 3     | 28, 29, 30, 31, 32, 33 |
| Row 4     | 22, 23, 24, 25, 26, 27 |

Use the same mapping on both boards (Red & Yellow).

---

## 🧠 How to Play

1. Upload the respective sketch (`Red_Connect4_Final.ino` or `Yellow_Connect4_Final.ino`) to each Arduino using separate laptops.
2. Connect:
    - TX1 (Pin 18) ↔ RX1 (Pin 19) between Arduinos
    - GND ↔ GND
3. Open Serial Monitor on both laptops.
4. Enter a column number (0–5) on the current player's turn.
5. The LED will light up in that column (stacked from bottom).
6. Game alternates turns automatically.
7. First player to connect **4 in a row** wins — LEDs flash in celebration!

---

## 📁 Files

- `Red_Connect4_Final.ino` – Code for Red player Arduino
- `Yellow_Connect4_Final.ino` – Code for Yellow player Arduino
- `README.md` – Project documentation and instructions

---

## 🔧 Future Improvements

- Add buzzer or LCD to display turns and winner
- Add reset button or serial command to restart game
- Implement full single-Arduino version

---

## 📷 Demo & Showcase
   
![WhatsApp Image 2025-04-19 at 12 50 07_a2aa5b3a](https://github.com/user-attachments/assets/3373396b-bd53-43b5-853a-ca3455652f17)

---

