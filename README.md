# 2D-River-Raid-Game

This project implements a River Raid-style 2D game using Object-Oriented Programming (OOP) principles in C++. The game features dynamic enemy spawning, collision detection, fuel management, scoring system, and file-based save/load functionality.

Course: CIE101 – Fundamentals of Computer Programming  
Institution: Zewail City of Science and Technology  
Semester: Spring 2025  

---

## 🚀 Project Overview

The objective of this project is to develop an interactive River Raid game using structured OOP design and a provided GUI framework.

The player controls a jet flying over a scrolling river while:

- Shooting enemy ships, helicopters, jets, and bridges
- Avoiding collisions with riverbanks and enemies
- Managing fuel levels
- Progressing through increasing difficulty levels

The project is built using the CMU Graphics Library for GUI handling.

---

## 🎮 Gameplay Features

### 🛩 Player Controls
- Move left/right using Arrow keys or A/D
- Increase/decrease speed using W/S or Up/Down arrows
- Shoot bullets vertically using Space key

---

### 🎯 Enemies & Objects

- Tankers (Ships)
- Helicopters
- Enemy Jets
- Bridges
- Fuel Depots

Each enemy type has unique movement behavior:
- Tankers → Vertical movement
- Helicopters → Side-to-side movement
- Jets → Horizontal movement
- Bridges → Stationary
- Fuel Depots → Stationary

---

## 🧮 Scoring System

| Enemy Type | Points |
|------------|--------|
| Tankers    | +30    |
| Helicopters| +60    |
| Jets       | +100   |
| Bridges    | +500   |

---

## ⛽ Game Mechanics

- Fuel decreases continuously while flying
- Fuel can be replenished by flying over fuel depots
- Shooting a fuel depot destroys it
- Lives decrease upon:
  - Crashing into enemies
  - Hitting bridges
  - Colliding with riverbanks
  - Running out of fuel
- Game ends when all lives are lost

---

## 📈 Dynamic Difficulty

As the player progresses:

- Enemies spawn more frequently
- Enemy movement speed increases
- River width becomes narrower
- Fuel depots appear less often
- Game scrolling speed increases

---


## 💾 Save & Load System

The game state is saved to a `.txt` file including:

- Level
- Points
- Fuel
- Lives
- Speed
- Player position
- Active enemies (type, position, dimensions)
- Background scroll offset
- Active bullets

The game can be restored exactly from the saved state.

---

## 🏗 Object-Oriented Design

The project follows a structured OOP hierarchy:

### Core Classes

- **Drawable** → Base class for all screen objects
- **GameObject** → Movable objects with collision handling
- **Toolbar & ToolbarIcon**
- **Game** → Main controller class
- **Window** → Handles GUI interaction

### OOP Concepts Applied

- Inheritance
- Polymorphism
- Encapsulation
- Virtual functions
- Collision-based behavior override

---

## 🧪 Technical Highlights

- Real-time collision detection
- Background scrolling animation
- Dynamic enemy generation
- Memory-safe object management
- File-based state persistence
- GUI-based user interaction

---

## 🛠 Tools & Technologies

- C++
- Object-Oriented Programming
- CMU Graphics Library
- File I/O handling

---

## 👨‍💻 Author(s)

- Mohammed Soliman  
- Ahmed Akef
- Amr Hamed
- Mahmoud Tamer

---

## 📌 Key Takeaway

This project demonstrates practical application of object-oriented programming principles through the development of a complete interactive game featuring GUI interaction, collision detection, dynamic difficulty scaling, and persistent game state management.
