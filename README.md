# Focus Game Engine With Two Playable Games

A custom-built 2D game engine developed from scratch in C++ using SDL libraries, featuring two fully playable games built entirely on top of the engine architecture.

All playable builds are available in the **Releases** section of this repository.

---

## Overview

This project demonstrates the design and implementation of a reusable game engine rather than standalone game development.

The repository includes:

- A modular custom C++ game engine
- Two complete games built using the engine
- Structured separation between engine systems and gameplay logic

The primary objective was to design a scalable and reusable engine core that can support multiple game implementations.

---


### Internal

Contains the engine core systems, including:

- Scene Management
- Object Management
- Rendering System
- Physics Handling
- Input System
- Collision Detection
- Sprite Management
- UI and Sound Management
- Core Game Loop & Timing

### External

Includes required third-party libraries and dependencies used by the engine.

### Project

Contains the two games developed using the engine architecture.

---

## Engine Architecture

The engine follows a modular and system-oriented architecture with clear separation of responsibilities.

Core systems include:

- **Scene Manager** – Controls scene transitions and active scenes
- **Object Manager** – Manages lifecycle of game objects
- **Physics System** – Handles movement and collision logic
- **Rendering System** – Responsible for drawing objects to screen
- **Input System** – Processes user input
- **Game Layer** – Implements gameplay logic on top of engine systems

This separation ensures maintainability, scalability, and reusability of the engine core.

---

## Playable Games

Two distinct games are implemented using the same engine:

- **Game 1** – Cat Chase - It is a game where the player is a cat and trying to catch randomly generated rats while trying to escape from dogs continously. Use WASD for movement and SPACE to catch the rat.
- **Game 2** – Apple Catch - It is a game where the player is a colorful racoon that is changing color every 10 seconds. The aim is eating the apples that is matching the color of the racoon and gather score. Use WASD for movement.

Pre-built executables can be downloaded from the **Releases** tab.

---

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- Custom Game Loop
- Modular System Design
- SDL
- OpenGL
- Collision & Physics Handling
- Scene-Based Architecture

---


## Project Goals

- Build a reusable game engine architecture from scratch
- Separate engine core systems from gameplay logic
- Implement scalable and modular system design
- Gain low-level understanding of game engine structure

---

## Future Improvements

- Editor tools
- Improved asset management pipeline
- Advanced physics system
- Performance profiling and optimization tools
- Extended rendering capabilities

---

## Author

**Buğra Berat Kök**  
Software Engineering Student  

GitHub: https://github.com/bugraberatkok
