# C++ SFML Ball Game - Complete Developer Specification

## Project Overview

### Game Description
A 2D physics-based ball game built with C++ and SFML. The player controls a green ball using arrow keys to move horizontally and jump. The ball bounces off screen edges and the game ends when it falls off the bottom of the screen.

### Core Gameplay
- **Movement**: Left/right arrow keys for horizontal movement with acceleration physics
- **Jumping**: Up arrow key for fixed-height jumping with gravity
- **Boundaries**: Ball bounces perfectly off left and right screen edges
- **Win/Lose**: Game over when ball falls below ground level

## Technical Architecture

### Development Environment
- **Language**: C++20
- **Graphics Framework**: SFML (Simple and Fast Multimedia Library)
- **Project Structure**: Single source file approach (main.cpp)
- **Build System**: Makefile
- **Target Platforms**: Cross-platform (Windows, macOS, Linux)

### Dependencies and Setup
```bash
# Required SFML modules
- sfml-graphics
- sfml-window  
- sfml-system

# Installation examples:
# Ubuntu/Debian: sudo apt-get install libsfml-dev
# macOS: brew install sfml
# Windows: Download from SFML website
```

### Build Configuration
```makefile
# Makefile
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = ball_game
SOURCE = main.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean debug
```

## System Requirements

### Window Configuration
| Property | Value | SFML Implementation |
|----------|-------|-------------------|
| Dimensions | 1280x720 pixels | `sf::VideoMode(1280, 720)` |
| Title | "Bouncing Ball" | `window.create(mode, "Bouncing Ball")` |
| Style | Resizable | `sf::Style::Default` |
| Frame Rate | 60 FPS | `window.setFramerateLimit(60)` |

### Coordinate System
- **Origin**: Top-left corner (0, 0)
- **X-axis**: Increases rightward (0 to 1280)
- **Y-axis**: Increases downward (0 to 720)
- **Ground Level**: y = 680 (ball center when on ground)
- **Ball Starting Position**: (640, 680) - center of screen on ground

## Visual Design Specifications

### Background System (Multi-layered)
```cpp
// Sky Background - Gradient Implementation
sf::VertexArray skyGradient(sf::Quads, 4);
skyGradient[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color(135, 206, 235));      // Top-left: Light blue
skyGradient[1] = sf::Vertex(sf::Vector2f(1280, 0), sf::Color(135, 206, 235));  // Top-right: Light blue  
skyGradient[2] = sf::Vertex(sf::Vector2f(1280, 720), sf::Color::White);        // Bottom-right: White
skyGradient[3] = sf::Vertex(sf::Vector2f(0, 720), sf::Color::White);           // Bottom-left: White

// Ground Layer - Solid Rectangle
sf::RectangleShape ground(sf::Vector2f(1280, 40));
ground.setPosition(0, 680);
ground.setFillColor(sf::Color(128, 128, 128)); // Gray
```

### Ball Design
| Property | Value | Implementation |
|----------|-------|----------------|
| Shape | Circle with outline | `sf::CircleShape` |
| Radius | 40 pixels | `ball.setRadius(40)` |
| Fill Color | Green | `sf::Color::Green` |
| Outline Color | Dark Green | `sf::Color(0, 128, 0)` |
| Outline Thickness | 3 pixels | `ball.setOutlineThickness(3)` |
| Origin | Center | `ball.setOrigin(40, 40)` |

## Physics Engine Specifications

### Movement System - Acceleration Based
```cpp
// Constants
const float HORIZONTAL_ACCELERATION = 300.0f;  // pixels/second²
const float HORIZONTAL_DECELERATION = 200.0f;  // pixels/second²
const float MAX_HORIZONTAL_SPEED = 300.0f;     // pixels/second
const float JUMP_VELOCITY = -400.0f;           // pixels/second (negative = upward)
const float GRAVITY = 800.0f;                  // pixels/second² (positive = downward)
const float JUMP_HEIGHT = 150.0f;              // pixels above ground

// Physics Variables
sf::Vector2f ballPosition(640.0f, 680.0f);     // Starting position
sf::Vector2f ballVelocity(0.0f, 0.0f);         // Starting velocity
bool isOnGround = true;                         // Jump availability
```

### Collision Detection
```cpp
// Boundary Collision (Perfect Bounce)
if (ballPosition.x - ballRadius <= 0) {
    ballPosition.x = ballRadius;
    ballVelocity.x = -ballVelocity.x;  // Reverse direction
}
if (ballPosition.x + ballRadius >= 1280) {
    ballPosition.x = 1280 - ballRadius;
    ballVelocity.x = -ballVelocity.x;  // Reverse direction
}

// Ground Collision
if (ballPosition.y >= 680) {
    ballPosition.y = 680;
    ballVelocity.y = 0;
    isOnGround = true;
} else {
    isOnGround = false;
}

// Game Over Condition
if (ballPosition.y > 680 + ballRadius) {
    // Trigger game over state
}
```

## Input System Architecture

### Control Mapping
| Input | Action | Implementation |
|-------|--------|----------------|
| Left Arrow | Move Left | `sf::Keyboard::Left` |
| Right Arrow | Move Right | `sf::Keyboard::Right` |
| Up Arrow | Jump | `sf::Keyboard::Up` |
| Enter | Menu Select | `sf::Keyboard::Enter` |
| Escape | Pause/Menu | `sf::Keyboard::Escape` |

### Input Handling Strategy
```cpp
// Continuous Input (held keys)
bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

// Event-based Input (single presses)
if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Up && isOnGround) {
        ballVelocity.y = JUMP_VELOCITY;
        isOnGround = false;
    }
}
```

## User Interface System

### Game State Management
```cpp
enum class GameState {
    MainMenu,
    Playing,
    GameOver
};
```

### Menu System Specifications
| Element | Style | Dimensions | Colors |
|---------|-------|------------|--------|
| Buttons | Rectangle | 200x50 pixels | White bg, black border |
| Text | Arial/Default | 24pt | Black |
| Selection Glow | Outline | 6px radius | White |
| Position | Center screen | N/A | N/A |

### Menu Implementation
```cpp
// Button Structure
struct MenuButton {
    sf::RectangleShape shape;
    sf::Text text;
    sf::RectangleShape glowEffect;
    bool isSelected;
    
    void updateGlow() {
        if (isSelected) {
            glowEffect.setOutlineThickness(6);
            glowEffect.setOutlineColor(sf::Color::White);
        } else {
            glowEffect.setOutlineThickness(0);
        }
    }
};
```

## Data Management

### Game State Data
```cpp
struct GameData {
    // Ball physics
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    bool isOnGround;
    
    // Game state
    GameState currentState;
    int selectedMenuItem;
    
    // Timing
    sf::Clock gameClock;
    float deltaTime;
    
    // UI elements
    std::vector<MenuButton> mainMenuButtons;
    std::vector<MenuButton> gameOverButtons;
};
```

### Resource Management
```cpp
// Resource Loading
sf::Font gameFont;
if (!gameFont.loadFromFile("arial.ttf")) {
    // Fallback to default font
}

// Memory Management
- Use stack allocation for game objects where possible
- Minimize dynamic allocation in game loop
- Clear unused resources between state transitions
```

## Error Handling Strategy

### Critical Error Handling
```cpp
// SFML Initialization
sf::RenderWindow window;
if (!window.create(sf::VideoMode(1280, 720), "Bouncing Ball")) {
    std::cerr << "Error: Failed to create SFML window" << std::endl;
    return -1;
}

// Font Loading
sf::Font font;
if (!font.loadFromFile("font.ttf")) {
    std::cerr << "Warning: Could not load custom font, using default" << std::endl;
    // Continue with default font
}
```

### Runtime Error Handling
| Error Type | Handling Strategy | Implementation |
|------------|------------------|----------------|
| Window Creation Failure | Exit with error message | Console output + return -1 |
| Font Loading Failure | Use default font + warning | Continue execution |
| Window Resize | Recalculate scaling | Handle resize event |
| Lost Focus | Pause game state | Handle focus events |

### Defensive Programming
```cpp
// Bounds checking
ballPosition.x = std::max(ballRadius, std::min(ballPosition.x, 1280.0f - ballRadius));
ballPosition.y = std::max(0.0f, ballPosition.y);

// Delta time clamping
deltaTime = std::min(deltaTime, 1.0f/30.0f); // Cap at 30 FPS minimum
```

## Performance Optimization

### Frame Rate Management
```cpp
// Delta time implementation
sf::Clock deltaClock;
float deltaTime = deltaClock.restart().asSeconds();

// Apply physics with delta time
ballVelocity.x += acceleration * deltaTime;
ballPosition.x += ballVelocity.x * deltaTime;
```

### Rendering Optimization
- Use `sf::RenderStates` for batch rendering
- Minimize texture switches
- Cache frequently used calculations
- Avoid unnecessary object creation in game loop

### Memory Optimization
- Reuse objects between frames
- Use object pooling for particles/effects
- Minimize string operations in game loop
- Prefer stack allocation over heap allocation

## Testing Plan

### Unit Testing Checklist

#### Physics System
- [ ] Ball accelerates correctly with left/right input
- [ ] Ball decelerates when no input is provided
- [ ] Maximum speed is enforced
- [ ] Jump height matches specification (150 pixels)
- [ ] Gravity applies correctly
- [ ] Ball cannot jump while in air
- [ ] Perfect bounce off left and right walls

#### Collision Detection
- [ ] Ball stops at ground level (y = 680)
- [ ] Ball bounces off left edge at x = 0
- [ ] Ball bounces off right edge at x = 1280
- [ ] Game over triggers when ball falls below ground
- [ ] Collision detection works at all frame rates

#### Input Handling
- [ ] Continuous movement with held arrow keys
- [ ] Immediate response to key press/release
- [ ] Simultaneous input handling (move + jump)
- [ ] Menu navigation with arrow keys
- [ ] Enter key selects menu items

#### User Interface
- [ ] Main menu displays correctly
- [ ] Game over menu displays correctly
- [ ] Button selection visual feedback works
- [ ] Menu navigation cycles properly
- [ ] State transitions function correctly

#### Visual Rendering
- [ ] Gradient background renders correctly
- [ ] Ground layer displays properly
- [ ] Ball renders with correct colors and outline
- [ ] Menu buttons display with proper styling
- [ ] Window resizing maintains aspect ratio
- [ ] 60 FPS maintained during gameplay

### Integration Testing

#### Game Flow
- [ ] Complete game cycle: Menu → Game → Game Over → Menu
- [ ] Restart functionality resets all game state
- [ ] Quit functionality exits cleanly
- [ ] Window close button works properly

#### Performance Testing
- [ ] Consistent frame rate under normal conditions
- [ ] Memory usage remains stable during extended play
- [ ] No memory leaks after multiple game cycles
- [ ] Responsive input even during intensive rendering

### Platform Testing
- [ ] Windows compilation and execution
- [ ] macOS compilation and execution  
- [ ] Linux compilation and execution
- [ ] Different screen resolutions
- [ ] Different SFML versions compatibility

## Deployment Considerations

### Distribution Requirements
```bash
# Required files for distribution
- ball_game(.exe)           # Main executable
- SFML runtime libraries    # Platform-specific
- README.txt               # Installation instructions
```

### Platform-Specific Notes
- **Windows**: Include SFML DLLs in same directory as executable
- **macOS**: Consider code signing for distribution
- **Linux**: Document dependency installation commands

## Code Quality Standards

### Naming Conventions
- **Variables**: camelCase (ballPosition, horizontalVelocity)
- **Functions**: camelCase (updatePhysics, handleInput)
- **Constants**: UPPER_SNAKE_CASE (MAX_HORIZONTAL_SPEED)
- **Classes/Structs**: PascalCase (GameData, MenuButton)

### Code Organization
```cpp
// Suggested file structure within main.cpp
1. Includes and constants
2. Data structures and enums
3. Function declarations
4. Main game loop
5. Function implementations
6. Helper functions
```

### Documentation Requirements
- Comment complex physics calculations
- Document all magic numbers with named constants
- Explain state transition logic
- Include performance considerations in comments

## Success Criteria

The implementation is considered complete when:
1. All physics behaviors match specification exactly
2. All menu systems function correctly
3. Game runs stably at 60 FPS
4. All input controls work as specified
5. Visual design matches requirements
6. Error handling prevents crashes
7. Code passes all test cases
8. Game compiles and runs on target platforms

This specification provides complete implementation guidance for creating the C++ SFML ball game with all discussed features and requirements.