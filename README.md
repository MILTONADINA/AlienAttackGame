# Alien Attack Game – C++ 2D Space Shooter

A classic 2D arcade-style alien shooter game built using C++ with graphics rendered through Windows GDI or a minimal pixel buffer engine. The game features a player-controlled ship, an alien army, and missile interactions with visual effects.

---

## 🧠 Key Skills Demonstrated

- **C++ Programming:** Object-oriented design, memory handling, and header implementation
- **2D Game Logic:** Collision detection, animation timing, and rendering loop
- **Custom Graphics Management:** Integration of `.bmp` and `.png` assets into a game buffer
- **Game Architecture:** Clean separation across `game.cpp`, `gameFunctions.cpp`, and modular headers
- **Project Management in Visual Studio:** `.sln` and `.vcxproj` files for reproducibility and debugging

---

## 🧱 Tech Stack

- **Language:** C++
- **IDE:** Visual Studio
- **Graphics:** GDI-based pixel rendering with raw image buffers (`alien.bmp`, `missile.png`, etc.)
- **File Types:**
  - `.cpp`, `.h`: Game logic and definitions
  - `.bmp`, `.png`, `.jpg`: Sprite and background assets
  - `.sln`, `.vcxproj`: Visual Studio solution and project files

---

## 🎮 Game Features

- 🚀 Player-controlled ship fires missiles at descending alien invaders
- 👾 Enemy formation with movement logic and respawn behavior
- 💥 Collision detection between missiles and enemies
- 🖼 Uses bitmap and PNG assets for retro-style game feel
- 🧩 Modular design with `alienArmy`, `pixie`, and `gameFunctions` classes

---

## 🚀 How to Build and Run

### 🔧 Using Visual Studio (Recommended)

1. Open `Alien Attack Project.sln` in Visual Studio
2. Ensure image assets are in the working directory (same as executable output)
3. Build the solution
4. Run the game

---

## 📁 Project Structure

AlienAttackGame/
├── alienArmy.cpp / .h → Controls alien movements and behavior
├── pixie.cpp / .h → Handles low-level pixel drawing or image rendering
├── game.cpp → Main loop and event management
├── gameFunctions.cpp / .h → Utility logic for game physics and events
├── *.bmp / *.png / *.jpg → Sprite and background assets
├── *.sln / *.vcxproj → Visual Studio project files



