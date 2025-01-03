# Tales of Buzz: A Top-Down RPG on the Mbed Platform

## Project Overview

**Tales of Buzz** is a custom-built top-down role-playing game (RPG) designed for the ECE 2035 course. This project uses a gaming circuit assembled on a breadboard with a 5-switch NavSwitch, speaker, buttons, and a uLCD screen, all programmed via the Mbed platform. It features a dynamic game loop, quest system, and engaging mechanics that bring the RPG experience to life. Players embark on a quest to defeat bosses, unlock secrets, and complete challenges in the game world.

---

## Features

### Baseline Features
- **Player Motion & Map Exploration**: Navigate a 50x50 tile map using a NavSwitch, with real-time status updates displayed on-screen.
- **Quest System**: Interact with NPCs, complete quests, and learn special abilities to defeat bosses.
- **Dynamic Map Interaction**: Encounter enemies, navigate obstacles, and interact with elements such as doors and stairs.
- **Graphics**: Includes sprites, animations, and dynamic updates for seamless gameplay.
- **Speech Bubbles**: Used for dialogue, notifications, and quest progression.

### Advanced Features
- **Start Page**: A custom start page with options to view controls, start the game, and display the game's title.
- **Modes of Locomotion**: Incorporates visually distinct movement modes like running.
- **Interactive Animations**: Dynamic interactions with static map objects.
- **In-Game Menu**: Manage inventory, use potions for extra lives, and enable special abilities.
- **Inventory Management**: Collect and utilize items during gameplay.
- **Health System**: Players start with three lives, with hazards like fire reducing life count.
- **Large Blocking Objects**: Includes features like big bushes that obscure the player.
- **Multiple Bosses**: Each requires unique strategies and abilities to defeat.
- **Leveling System**: Unlocks additional abilities, such as long-distance fire attacks, upon progression.
- **Speech Enhancements**: Speech bubbles for spells and quests.

---

## Technical Details

### Hardware
- Custom-built gaming setup on a breadboard.
- Components: 5-switch NavSwitch, speaker, buttons, and a uLCD screen.

### Software
- **Platform**: Mbed OS and Keil Studio Online IDE.
- **Game Loop**: Handles input, state updates, rendering, and frame delays.
- **Map Design**: Implements a hash table for efficient storage and retrieval of map data.
- **Graphics**: Utilizes `uLCD.BLIT()` for optimized sprite rendering.

### Custom Hash Table Library
This project relies on a custom-built hash table library implemented during **P2-1** of the course. The library supports operations like inserting, deleting, and accessing entries. Automated testing using Google Test and Address Sanitizer was performed to ensure correctness and memory safety.

---

## How to Run

1. Clone this repository and follow the Mbed setup instructions.
2. Flash the compiled `.bin` file to your Mbed hardware.
3. Use the NavSwitch to move the player and buttons for interactions.
4. Explore the map, complete quests, and defeat bosses to achieve victory!

---

## Demo Video

Watch the gameplay demo on YouTube: [Tales of Buzz Demo](https://youtu.be/uHxsupJkFI8)
