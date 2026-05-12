# Tower_defense
# Tower Defense Game

## Overview

This project is a 2D Tower Defense game developed in C++ using the Raylib graphics library.
The player must place different towers strategically to stop enemies from reaching the end of the path.

The game includes:

* Multiple enemy types
* Different tower classes
* Multiple maps
* Upgrade system
* Health and gold management
* Wave-based gameplay
* Background music and textures

---

# GUI Library Used

This project uses the Raylib library for:

* Graphics rendering
* Window handling
* Keyboard and mouse input
* Audio playback

GitHub Repository for Raylib:

https://github.com/raysan5/raylib

---

# Installing Raylib

## Step 1: Download Raylib

Download Raylib from the official GitHub repository:

https://github.com/raysan5/raylib

---

## Step 2: Setup Raylib

### For Visual Studio

1. Extract the Raylib files.
2. Create a C++ project.
3. Add Raylib include and library directories in project settings.
4. Link the required Raylib libraries.

---

## Step 3: Copy Required Files

Place the following files in the project directory:

* start_screen.png
* map_background.png
* tower_info.png
* enemy_barbarian.png
* enemy_hogrider.png
* enemy_canon.png
* enemy_peka.png
* tower_canon.png
* tower_machinegun.png
* tower_wizard.png
* tower_archer.png
* background_music.mp3

---

# How to Compile

Compile all `.cpp` source files together with Raylib linked.

Example command using g++:

```bash
g++ *.cpp -o game -lraylib -lopengl32 -lgdi32 -lwinmm
```

---

# How to Run

After successful compilation:

```bash
./game
```

Or run the generated executable file from Visual Studio.

---

# Controls

| Key              | Action                 |
| ---------------- | ---------------------- |
| ENTER            | Start Game             |
| T                | Open Tower Information |
| 1 - 4            | Select Towers          |
| Left Mouse Click | Place Tower            |
| U                | Upgrade Tower          |
| ESC              | Exit / Back            |

# Tower Types

1. Canon Tower
2. Machine Gun Tower
3. Wizard Tower
4. Archer Tower
# Enemy Types
1. Barbarian
2. Hog Rider
3. Canon Enemy
4. Peka

# Known Issues / Limitations
* Enemy balancing may require further tuning.
* Collision and tower placement system can occasionally feel restrictive near corners.
* The game currently uses fixed screen resolution.
* Some textures may not load if resource files are missing from the project folder.
* Audio may fail if Raylib audio device initialization fails.
# Author
Developed in C++ using Object-Oriented Programming concepts and Raylib.
