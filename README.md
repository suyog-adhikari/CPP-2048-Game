# CPP 2048 Game
The C++ implementation of the popular 2048 game! This is a simple console-based version of the game, where you can play by moving and merging tiles to reach the ultimate 2048 tile. It runs in your terminal/console using arrow keys for interaction.

## 🎮 How to Play
1. **Objective**: The goal of the game is to combine tiles with the same number to create a tile of value 2048. You can continue playing even after you reach 2048 to see how high your score can go.
2. **Controls**: Use Arrow keys to slide and combine the tiles

   * ← Moves the tiles left
   * → Moves the tiles right
   * ↑ Moves the tiles up
   * ↓ Moves the tiles down

3. **Merging**: Tiles with same numbers merge into one when they collide with the new tile value, which is the sum of two tiles
4. **Game Over**: The game ends when the board is full and no valid moves remains
5. **Win Condition**: The game is won when the tile value of 2048 is obtained

## 🛠️ Features
* **Console Interface**: A simple, clean, and interactive minimal terminal interface
* **Score Tracking**: The score is updated as tile merge and accumulate

## 🚀 Getting Started
### Prerequisites
* **C++ Compiler**: GCC, Clang, MSVC, etc
* **Windows OS**: The game uses windows-specific libraries like `windows.h` for cursor manipulation, and `Sleep` function
* **C++17** or newer recommended
### Installation & Compilation
1. **Clone the Repository**
   
   ```bash
   git clone https://github.com/suyog-adhikari/CPP-2048-Game.git
   cd CPP-2048-Game
   ```
2. **Compile the Program**: If you are using **GCC** or **MinGW**, you can compile the code with:

   ```bash
   g++ -o 2048game main.cpp
   ```
    or if you are using **Visual Studio** or **MSVC**, make sure to use the appropriate build system.

3. **Run the Game**: After compilation, run the game with
   ```bash
   ./2048game
   ```
    The game will open with a menu where you can select:
    * **Play Game**: Start a new Game
    * **How to Play**: Instructions on how to play the game
    * **Exit Game**: Exit the game

## 🧑‍💻 Code Overview
The program is organized into several files, each serving a specific purpose:
* `game.h`: Contains the decleration of the `board` and `game` classes. The `board` class manages the grid, game state, and actions like adding tiles, checking for win, and displaying the board. The `game` class extends `board` and adds logic for running the game.
* `game.cpp`: Implements the game logic, such as initializing the board, running the game, adding new tiles, checking for a win or game-over, and handling user input for movement.
* `functions.h`: Contains helper functions managing the console interface.
* `p128.h`: A custom class that manages the game's main menu and the flow of the program. It guides the user through the choices of starting a new game, viewing the instructions, or quitting
* `main.cpp`: The entry point for the program that initializes the game and starts the main program flow.

## 🎯 Gameplay Logic
* **Board Initialization**
  * The board is a 4x4 grid initialized with two random "2" tiles.
  * Every time the player moves or merges tiles, a new "2" tile is added to an empty space on the grid.
* **Tile Merging**:
  * When two tiles with the same value collide, they merge into one, doubling the value of the merged tile.
* **Game Over Check**:
  * The game checks whether the board is full and whether there are any valid moves left. If no moves are possible, the game ends. 
* **Win Condition**:
  * The game ends and displays a "You Win" message if any tile reaches the value 2048. 
