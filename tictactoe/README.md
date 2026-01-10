# Tic-Tac-Toe Game with SFML

A C++ implementation of Tic-Tac-Toe with a graphical user interface built using SFML (Simple and Fast Multimedia Library).

## Features
- ✅ GUI interface with SFML
- ✅ Play against an unbeatable AI (Minimax algorithm with alpha-beta pruning)
- ✅ Score tracking across multiple games
- ✅ Choose whether to play as X or O
- ✅ Colored and styled graphics
- ✅ Hover effects on valid moves
- ✅ Winning line highlighting
- ✅ Smooth menu system

## Requirements
- C++17 or later
- SFML 2.6+ (already installed)
- g++ compiler
- Linux/Unix environment

## Building the Project

### Using Make (Recommended)
```bash
# Build the project
make

# Clean build artifacts
make clean

# Rebuild everything
make rebuild

# Build and run
make run
```

### Using VS Code
1. Open the project folder in VS Code
2. Press `Ctrl+Shift+B` to build (or select "Terminal" > "Run Build Task")
3. Press `F5` to debug

### Manual Compilation
```bash
g++ -std=c++17 -Wall -Wextra -I./include src/*.cpp -o build/tictactoe -lsfml-graphics -lsfml-window -lsfml-system
```

## Running the Game
```bash
# From the tictactoe directory
./build/tictactoe
```

## Project Structure
```
tictactoe/
├── src/               # Source files
│   ├── main.cpp       # Entry point
│   ├── Board.cpp      # Game board logic
│   ├── AI.cpp         # Minimax AI implementation
│   ├── Game.cpp       # Game state management
│   ├── Player.cpp     # Player and score tracking
│   └── GUI.cpp        # SFML graphics and rendering
├── include/           # Header files
│   ├── Board.hpp      # Board class definition
│   ├── AI.hpp         # AI class definition
│   ├── Game.hpp       # Game class definition
│   ├── Player.hpp     # Player class definition
│   └── GUI.hpp        # GUI class definition
├── build/             # Compiled binaries (not in git)
├── Makefile           # Build configuration
└── README.md          # This file
```

## Implementation Details

### Board Class (Board.hpp/cpp)
- 3x3 grid representation using `std::array`
- Move validation and tracking
- Win condition checking (rows, columns, diagonals)
- Draw detection

### AI Class (AI.hpp/cpp)
- **Minimax algorithm** with alpha-beta pruning for optimal play
- Evaluates all possible game states
- Guarantees the AI never loses (best case: win, worst case: draw)
- Depth-based scoring for faster wins

### Game Class (Game.hpp/cpp)
- Game state management (menu, playing, game over)
- Turn management between human and AI
- Score tracking across multiple games
- Player creation and management

### GUI Class (GUI.hpp/cpp)
- SFML-based rendering
- Interactive menu for choosing X or O
- Visual board with colored X's and O's
- Hover effects on valid moves
- Winning line highlighting
- Game over overlay with results

### Player Class (Player.hpp/cpp)
- Player information (name, symbol, type)
- Win/loss/draw tracking
- Score persistence across games

## VS Code Integration

The project includes VS Code configuration files:
- `.vscode/c_cpp_properties.json` - IntelliSense configuration
- `.vscode/tasks.json` - Build tasks
- `.vscode/launch.json` - Debug configuration

### Available Tasks
- **Build Tic-Tac-Toe** (`Ctrl+Shift+B`) - Compile the project
- **Clean Build** - Remove build artifacts
- **Run Tic-Tac-Toe** - Build and run the game

## Controls
- **Menu Screen**: Click top half to play as X, bottom half to play as O
- **Game Screen**: Click on empty cells to place your move
- **Game Over**: Click anywhere to play again
- **ESC**: Return to menu (or quit if at menu)
- **R**: Restart game after game over

## License
Free to use and modify.

## Author
Joshua Merz (Joshua.merz@wsu.edu)
