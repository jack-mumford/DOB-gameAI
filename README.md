# C++ SFML Ball Game

A 2D physics-based ball game built with C++ and SFML. Control a green ball using arrow keys to move horizontally and jump. The ball bounces off screen edges and the game ends when it falls off the bottom of the screen.

## Features

- **Physics-based Movement**: Acceleration and deceleration system for smooth ball movement
- **Jumping Mechanics**: Fixed-height jumping with gravity simulation
- **Perfect Bouncing**: Ball bounces elastically off left and right screen boundaries
- **Game States**: Main menu, gameplay, and game over screens with navigation
- **Visual Design**: Beautiful sky gradient background with ground layer
- **Responsive Controls**: Smooth input handling for movement and menu navigation

## Controls

### Gameplay
- **Left Arrow**: Move ball left
- **Right Arrow**: Move ball right  
- **Up Arrow**: Jump (only when on ground)

### Menus
- **Up/Down Arrows**: Navigate menu options
- **Enter**: Select highlighted option

## Installation

### Prerequisites
You need SFML (Simple and Fast Multimedia Library) installed on your system.

#### macOS
```bash
brew install sfml
```

#### Ubuntu/Debian
```bash
sudo apt-get install libsfml-dev
```

#### Windows
Download SFML from [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php) and follow the installation instructions.

### Building the Game

1. Clone or download this repository
2. Navigate to the project directory
3. Compile using the provided Makefile:

```bash
make
```

For debug build:
```bash
make debug
```

To clean build files:
```bash
make clean
```

### Running the Game

After successful compilation, run:
```bash
./ball_game
```

## Game Physics

The game implements realistic physics with the following specifications:

- **Horizontal Acceleration**: 300 pixels/second²
- **Horizontal Deceleration**: 200 pixels/second²
- **Maximum Horizontal Speed**: 300 pixels/second
- **Jump Velocity**: 400 pixels/second upward
- **Gravity**: 800 pixels/second² downward
- **Ball Radius**: 40 pixels

## Technical Details

- **Language**: C++20
- **Graphics Library**: SFML
- **Window Size**: 1280x720 pixels
- **Frame Rate**: 60 FPS
- **Architecture**: Single source file approach

## Game Flow

1. **Main Menu**: Start the game or quit
2. **Gameplay**: Control the ball, avoid falling off screen
3. **Game Over**: Restart or quit when ball falls

## Troubleshooting

### Font Loading Issues
The game attempts to load fonts from common system locations. If you see font warnings, the game will still run using SFML's default font.

### SFML Not Found
Make sure SFML is properly installed and the library paths are correctly set for your system.

### Compilation Errors
Ensure you have a C++20 compatible compiler (GCC 10+ or Clang 10+).

## Development

This project was built following Test-Driven Development (TDD) principles with incremental feature implementation. The codebase is organized for clarity and maintainability while keeping everything in a single source file for simplicity.

## License

This project is open source and available under the MIT License.
