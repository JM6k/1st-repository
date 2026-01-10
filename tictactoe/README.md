# Tic-Tac-Toe Game with SFML

A C++ implementation of Tic-Tac-Toe with a graphical user interface built using SFML (Simple and Fast Multimedia Library).

## Features (Planned)
- ✅ GUI interface with SFML
- ✅ Play against an unbeatable AI (Minimax algorithm)
- ✅ Score tracking across multiple games
- ✅ Choose whether to play as X or O
- ✅ Colored and styled output

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
│   └── main.cpp       # Entry point (currently a test program)
├── include/           # Header files (to be added)
├── build/             # Compiled binaries
├── Makefile           # Build configuration
└── README.md          # This file
```

## Development Status

### Completed
- ✅ SFML installation and setup
- ✅ Project structure created
- ✅ Build system (Makefile) configured
- ✅ VS Code configuration (IntelliSense, tasks, debugging)
- ✅ Basic SFML test program

### To Do
- [ ] Implement Board class
- [ ] Implement AI with Minimax algorithm
- [ ] Implement Game logic
- [ ] Implement GUI rendering
- [ ] Add score tracking
- [ ] Add main menu
- [ ] Polish and styling

## VS Code Integration

The project includes VS Code configuration files:
- `.vscode/c_cpp_properties.json` - IntelliSense configuration
- `.vscode/tasks.json` - Build tasks
- `.vscode/launch.json` - Debug configuration

### Available Tasks
- **Build Tic-Tac-Toe** (`Ctrl+Shift+B`) - Compile the project
- **Clean Build** - Remove build artifacts
- **Run Tic-Tac-Toe** - Build and run the game

## Controls (To be implemented)
- Mouse click to place X or O
- ESC to close window
- Menu for selecting X or O at game start

## License
Free to use and modify.

## Author
Joshua Merz (Joshua.merz@wsu.edu)
