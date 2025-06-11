# C++ SFML Ball Game - Development Blueprint & Test-Driven Implementation Plan

## Phase 1: High-Level Development Blueprint

### 1.1 Project Foundation
- Set up build system and dependencies
- Create basic SFML window
- Establish core game loop structure
- Implement basic error handling

### 1.2 Core Rendering System
- Implement multi-layered background (sky gradient + ground)
- Create ball rendering with proper styling
- Set up coordinate system and positioning

### 1.3 Physics Engine
- Implement ball movement with acceleration/deceleration
- Add gravity and jumping mechanics
- Create collision detection for boundaries and ground
- Handle game over conditions

### 1.4 Input System
- Implement keyboard input handling
- Add continuous vs event-based input distinction
- Create input state management

### 1.5 Game State Management
- Implement game state enum and transitions
- Create main menu system
- Add game over screen
- Handle state-specific rendering and input

### 1.6 User Interface
- Design and implement menu buttons
- Add selection highlighting and navigation
- Implement menu interaction system

### 1.7 Polish & Integration
- Performance optimization
- Error handling refinement
- Final testing and bug fixes

## Phase 2: Iterative Development Chunks

### Chunk 1: Project Setup & Basic Window
**Goal**: Create a working SFML window with basic game loop
- SFML dependency setup
- Makefile creation
- Basic window initialization
- Main game loop skeleton
- Window event handling

### Chunk 2: Background Rendering
**Goal**: Display the multi-layered background
- Sky gradient implementation using VertexArray
- Ground rectangle rendering
- Background rendering in game loop
- Color and positioning verification

### Chunk 3: Ball Rendering
**Goal**: Display a properly styled ball on screen
- CircleShape creation with correct dimensions
- Ball positioning and origin setup
- Color and outline application
- Ball rendering in game loop

### Chunk 4: Basic Movement
**Goal**: Ball responds to left/right arrow keys
- Input detection for arrow keys
- Horizontal velocity application
- Position updates based on velocity
- Basic boundary collision (stop at edges)

### Chunk 5: Advanced Movement Physics
**Goal**: Implement acceleration/deceleration system
- Acceleration constants and variables
- Velocity calculations with acceleration
- Maximum speed enforcement
- Smooth deceleration when keys released

### Chunk 6: Boundary Bouncing
**Goal**: Ball bounces perfectly off screen edges
- Collision detection refinement
- Velocity reversal on collision
- Position correction to prevent wall penetration

### Chunk 7: Jumping Mechanics
**Goal**: Ball can jump with fixed height
- Gravity implementation
- Jump input detection
- Vertical velocity and position updates
- Ground collision and landing

### Chunk 8: Game Over System
**Goal**: Detect when ball falls and trigger game over
- Game over condition detection
- Game state transition to game over
- Basic game over indication

### Chunk 9: Game State Management
**Goal**: Implement state machine for menu/game/gameover
- GameState enum implementation
- State transition logic
- State-specific update and render methods

### Chunk 10: Main Menu
**Goal**: Create functional main menu
- Menu button structure and rendering
- Menu navigation with arrow keys
- Menu selection with Enter key
- Transition from menu to gameplay

### Chunk 11: Game Over Menu
**Goal**: Create functional game over screen
- Game over menu buttons
- Menu navigation and selection
- Restart functionality
- Quit functionality

### Chunk 12: Menu Visual Effects
**Goal**: Add selection highlighting and polish
- Button glow effect implementation
- Selection state visual feedback
- Menu button styling refinement

## Phase 3: Granular Implementation Steps

### Step 1.1: SFML Setup and Makefile
- Create directory structure
- Write Makefile with proper SFML linking
- Create empty main.cpp with SFML includes
- Test compilation

### Step 1.2: Basic Window Creation
- Implement window creation with error handling
- Add basic event loop
- Handle window close events
- Test window display

### Step 1.3: Game Loop Structure
- Add frame rate limiting
- Implement update/render separation
- Add delta time calculation
- Create game loop skeleton

### Step 2.1: Sky Gradient Rendering
- Implement VertexArray for gradient
- Set correct vertex positions and colors
- Add to render loop
- Verify gradient display

### Step 2.2: Ground Rectangle
- Create ground RectangleShape
- Set position, size, and color
- Add to render loop
- Verify ground positioning

### Step 3.1: Ball Shape Creation
- Create CircleShape with specifications
- Set radius, colors, and outline
- Set origin to center
- Position ball at starting location

### Step 3.2: Ball Rendering
- Add ball to render loop
- Verify ball appears correctly
- Test ball positioning

### Step 4.1: Input Detection
- Implement keyboard state checking
- Add left/right arrow key detection
- Test input responsiveness

### Step 4.2: Basic Horizontal Movement
- Add velocity variables
- Update position based on input
- Implement basic collision bounds
- Test movement

### Step 5.1: Acceleration Implementation
- Add acceleration constants
- Implement velocity updates with acceleration
- Add maximum speed clamping
- Test acceleration behavior

### Step 5.2: Deceleration System
- Add deceleration when no input
- Implement smooth velocity reduction
- Test smooth stopping

### Step 6.1: Wall Collision Detection
- Implement precise collision bounds
- Add velocity reversal on collision
- Test bouncing behavior

### Step 7.1: Gravity System
- Add gravity constant and vertical velocity
- Implement gravity application each frame
- Test ball falling

### Step 7.2: Jump Implementation
- Add jump input detection
- Implement jump velocity application
- Add ground detection for jump availability
- Test jumping mechanics

### Step 8.1: Game Over Detection
- Implement fall-off-screen detection
- Add game over state transition
- Test game over triggering

### Step 9.1: State Enum and Management
- Create GameState enum
- Add state variables and transition functions
- Implement basic state machine

### Step 10.1: Main Menu Structure
- Create MenuButton struct
- Implement menu button rendering
- Add menu navigation logic

### Step 11.1: Game Over Menu
- Implement game over menu buttons
- Add restart and quit functionality
- Test menu interactions

### Step 12.1: Visual Effects
- Implement button glow effects
- Add selection visual feedback
- Polish menu appearance

## Phase 4: Test-Driven Development Prompts

### TDD Prompt 1: Project Setup & Window Creation
```
Create a C++ SFML project with the following requirements:

**Test Requirements:**
1. Test that SFML window creates successfully with dimensions 1280x720
2. Test that window title is "Bouncing Ball"
3. Test that window is resizable
4. Test that frame rate is limited to 60 FPS
5. Test that window closes properly on close event

**Implementation Requirements:**
- Use C++20 standard
- Create Makefile with proper SFML linking (-lsfml-graphics -lsfml-window -lsfml-system)
- Handle SFML initialization errors with console output
- Implement basic game loop with event handling
- Use main.cpp as single source file

**Acceptance Criteria:**
- Project compiles without errors
- Window displays correctly
- Window responds to close events
- No memory leaks or crashes

Write the code with comprehensive error handling and clear variable names.
```

### TDD Prompt 2: Background Rendering System
```
Extend the SFML ball game to render a multi-layered background system.

**Test Requirements:**
1. Test that sky gradient renders from light blue (135,206,235) at top to white at bottom
2. Test that ground rectangle is gray (128,128,128) and positioned at y=680 with height=40
3. Test that background covers full screen dimensions (1280x720)
4. Test that background renders before other game elements
5. Test that gradient uses VertexArray with 4 vertices

**Implementation Requirements:**
- Use sf::VertexArray for sky gradient with sf::Quads primitive
- Use sf::RectangleShape for ground layer
- Set proper vertex positions: (0,0), (1280,0), (1280,720), (0,720)
- Position ground from y=680 to y=720
- Render background in correct order (sky first, then ground)

**Acceptance Criteria:**
- Gradient displays smoothly from blue to white
- Ground appears as solid gray rectangle at bottom
- No rendering artifacts or gaps
- Background fills entire window

Maintain the existing window creation code and add background rendering to the game loop.
```

### TDD Prompt 3: Ball Rendering Implementation
```
Add ball rendering to the SFML game with exact specifications.

**Test Requirements:**
1. Test that ball is a circle with 40-pixel radius
2. Test that ball fill color is green (sf::Color::Green)
3. Test that ball outline is dark green (0,128,0) with 3-pixel thickness
4. Test that ball origin is set to center (40,40)
5. Test that ball initial position is (640,680) - center screen on ground
6. Test that ball renders correctly in the game loop

**Implementation Requirements:**
- Use sf::CircleShape for ball creation
- Set radius to 40 pixels using setRadius()
- Apply green fill color and dark green outline
- Set outline thickness to 3 pixels
- Configure origin to center using setOrigin(40,40)
- Position ball at starting coordinates (640,680)
- Add ball rendering after background in render loop

**Acceptance Criteria:**
- Ball appears as green circle with dark green border
- Ball is positioned correctly on ground at screen center
- Ball maintains proper proportions and colors
- No visual artifacts around ball edges

Extend the existing code without modifying the background rendering system.
```

### TDD Prompt 4: Basic Input and Movement
```
Implement basic horizontal movement for the ball using arrow keys.

**Test Requirements:**
1. Test that left arrow key moves ball leftward
2. Test that right arrow key moves ball rightward
3. Test that ball stops at screen boundaries (x=40 to x=1240)
4. Test that movement is smooth and continuous while key is held
5. Test that ball stops moving when keys are released
6. Test that multiple keys can be handled simultaneously

**Implementation Requirements:**
- Use sf::Keyboard::isKeyPressed() for continuous input detection
- Check for sf::Keyboard::Left and sf::Keyboard::Right
- Implement basic velocity system with ballVelocity variable
- Set movement speed to 200 pixels/second
- Add boundary collision to prevent ball leaving screen
- Update ball position each frame based on velocity and deltaTime
- Use sf::Clock for delta time calculation

**Acceptance Criteria:**
- Ball moves smoothly in response to arrow keys
- Ball cannot move beyond screen edges
- Movement feels responsive and consistent
- Ball position updates correctly each frame

Add input handling and basic physics while preserving existing rendering code.
```

### TDD Prompt 5: Advanced Physics - Acceleration System
```
Replace basic movement with acceleration-based physics system.

**Test Requirements:**
1. Test that ball accelerates at 300 pixels/second² when arrow key pressed
2. Test that ball decelerates at 200 pixels/second² when key released
3. Test that maximum horizontal speed is 300 pixels/second
4. Test that acceleration applies correctly with delta time
5. Test that deceleration brings ball to complete stop
6. Test that velocity direction changes correctly

**Implementation Requirements:**
- Replace direct velocity setting with acceleration system
- Add constants: HORIZONTAL_ACCELERATION (300.0f), HORIZONTAL_DECELERATION (200.0f), MAX_HORIZONTAL_SPEED (300.0f)
- Apply acceleration when keys are pressed
- Apply deceleration when no keys are pressed
- Clamp velocity to maximum speed using std::min/std::max
- Use proper delta time calculations for frame-rate independence

**Physics Formulas:**
```cpp
// When accelerating
if (leftPressed || rightPressed) {
    velocity += acceleration * deltaTime * direction;
}
// When decelerating  
else {
    velocity *= (1.0f - deceleration * deltaTime);
}
velocity = std::clamp(velocity, -MAX_SPEED, MAX_SPEED);
```

**Acceptance Criteria:**
- Ball accelerates smoothly from rest
- Ball reaches maximum speed and maintains it
- Ball decelerates smoothly to stop
- Physics feel natural and responsive

Modify existing movement code to use acceleration instead of direct velocity.
```

### TDD Prompt 6: Boundary Collision - Perfect Bouncing
```
Implement perfect bouncing off screen edges.

**Test Requirements:**
1. Test that ball bounces off left edge (x ≤ 40) by reversing velocity
2. Test that ball bounces off right edge (x ≥ 1240) by reversing velocity
3. Test that ball maintains full speed after bounce (no energy loss)
4. Test that ball position is corrected to prevent wall penetration
5. Test that bouncing works at all speeds and angles
6. Test that continuous bouncing works correctly

**Implementation Requirements:**
- Check collision conditions: (ballPosition.x - ballRadius ≤ 0) and (ballPosition.x + ballRadius ≥ 1280)
- Reverse horizontal velocity: ballVelocity.x = -ballVelocity.x
- Correct position to prevent penetration: ballPosition.x = ballRadius or ballPosition.x = 1280 - ballRadius
- Maintain velocity magnitude (perfect elastic collision)
- Apply collision detection after position updates

**Collision Logic:**
```cpp
// Left wall collision
if (ballPosition.x - ballRadius <= 0) {
    ballPosition.x = ballRadius;
    ballVelocity.x = -ballVelocity.x;
}
// Right wall collision  
if (ballPosition.x + ballRadius >= 1280) {
    ballPosition.x = 1280 - ballRadius;
    ballVelocity.x = -ballVelocity.x;
}
```

**Acceptance Criteria:**
- Ball bounces cleanly off both walls
- No velocity is lost in collisions
- Ball never penetrates walls
- Bouncing feels natural and consistent

Replace boundary stopping with perfect bouncing collision system.
```

### TDD Prompt 7: Jumping and Gravity Physics
```
Implement jumping mechanics with gravity system.

**Test Requirements:**
1. Test that up arrow key triggers jump with -400 pixels/second initial velocity
2. Test that gravity applies at 800 pixels/second² downward acceleration
3. Test that ball can only jump when on ground (y = 680)
4. Test that ball lands correctly on ground and stops vertical motion
5. Test that jump height reaches approximately 150 pixels above ground
6. Test that gravity affects ball continuously when airborne

**Implementation Requirements:**
- Add gravity constant: GRAVITY (800.0f pixels/second²)
- Add jump velocity constant: JUMP_VELOCITY (-400.0f pixels/second)
- Add vertical velocity component to ballVelocity
- Implement ground detection: isOnGround boolean
- Use event-based input for jump (sf::Event::KeyPressed)
- Apply gravity continuously when ball is airborne
- Handle ground collision for landing

**Physics Implementation:**
```cpp
// Jump input (event-based)
if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Up && isOnGround) {
        ballVelocity.y = JUMP_VELOCITY;
        isOnGround = false;
    }
}

// Gravity application
if (!isOnGround) {
    ballVelocity.y += GRAVITY * deltaTime;
}

// Ground collision
if (ballPosition.y >= 680) {
    ballPosition.y = 680;
    ballVelocity.y = 0;
    isOnGround = true;
}
```

**Acceptance Criteria:**
- Ball jumps to correct height when up arrow pressed
- Ball falls naturally due to gravity
- Ball can only jump when touching ground
- Landing is smooth and stops vertical motion

Add vertical physics while maintaining horizontal movement and bouncing.
```

### TDD Prompt 8: Game Over Detection System
```
Implement game over condition when ball falls off screen.

**Test Requirements:**
1. Test that game over triggers when ball falls below y = 680 + ballRadius (720)
2. Test that game state changes from Playing to GameOver
3. Test that physics updates stop during game over
4. Test that ball position is preserved when game over occurs
5. Test that game over detection works regardless of horizontal position

**Implementation Requirements:**
- Add GameState enum: MainMenu, Playing, GameOver
- Add currentGameState variable initialized to MainMenu
- Implement game over detection: ballPosition.y > 680 + ballRadius
- Stop physics updates when not in Playing state
- Preserve game visuals during game over state
- Add state transition logic

**State Management:**
```cpp
enum class GameState {
    MainMenu,
    Playing, 
    GameOver
};

// Game over detection
if (currentGameState == GameState::Playing) {
    if (ballPosition.y > 680 + ballRadius) {
        currentGameState = GameState::GameOver;
    }
}

// Conditional physics updates
if (currentGameState == GameState::Playing) {
    // Apply physics, input, collision detection
}
```

**Acceptance Criteria:**
- Game over triggers reliably when ball falls
- Game state transitions work correctly
- Physics stop during game over
- Visual state is preserved

Add game state management while preserving all existing gameplay mechanics.
```

### TDD Prompt 9: Main Menu Implementation
```
Create a functional main menu system with navigation.

**Test Requirements:**
1. Test that main menu displays "Start Game" and "Quit" buttons
2. Test that buttons are rectangular (200x50) with white background and black borders
3. Test that arrow keys navigate between menu options
4. Test that Enter key selects highlighted option
5. Test that "Start Game" transitions to Playing state
6. Test that "Quit" exits the application
7. Test that selected button shows white glow effect

**Implementation Requirements:**
- Create MenuButton struct with sf::RectangleShape, sf::Text, and glow effect
- Position buttons centered horizontally and vertically on screen
- Implement menu navigation with arrow keys (wrap around)
- Add selection highlighting with 6-pixel white outline
- Handle Enter key for menu selection
- Load default font or handle font loading failure gracefully
- Render menu over same background as gameplay

**Menu Structure:**
```cpp
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

**Acceptance Criteria:**
- Main menu appears when game starts
- Navigation works smoothly with arrow keys
- Button selection is visually clear
- Menu functions lead to correct actions

Implement main menu as initial game state, transitioning to gameplay on "Start Game".
```

### TDD Prompt 10: Game Over Menu System
```
Implement game over screen with restart functionality.

**Test Requirements:**
1. Test that game over menu displays "Restart" and "Quit" buttons
2. Test that menu appears when ball falls off screen
3. Test that arrow key navigation works in game over state
4. Test that "Restart" resets ball position, velocity, and returns to Playing state
5. Test that "Quit" exits the application
6. Test that game over menu uses same styling as main menu
7. Test that background shows frozen game state

**Implementation Requirements:**
- Create game over menu buttons with identical styling to main menu
- Position menu centered on screen
- Implement restart functionality that resets all game variables
- Handle menu navigation and selection identical to main menu
- Reset ball to starting position (640, 680) and zero velocity
- Transition back to Playing state on restart
- Preserve background rendering during game over

**Reset Logic:**
```cpp
void resetGame() {
    ballPosition = sf::Vector2f(640.0f, 680.0f);
    ballVelocity = sf::Vector2f(0.0f, 0.0f);
    isOnGround = true;
    currentGameState = GameState::Playing;
}
```

**Menu Integration:**
- Use same MenuButton struct and navigation logic
- Handle state-specific rendering (show frozen game + menu overlay)
- Implement menu selection handling for game over state

**Acceptance Criteria:**
- Game over menu appears when ball falls
- Restart completely resets game state
- Menu navigation works identically to main menu
- Visual presentation is consistent

Complete the game loop by adding restart functionality and game over menu system.
```

### TDD Prompt 11: Final Integration and Polish
```
Complete the game with final integration, polish, and comprehensive testing.

**Test Requirements:**
1. Test complete game flow: MainMenu → Playing → GameOver → restart loop
2. Test that all physics values match specification exactly
3. Test that window resize handling works correctly
4. Test that performance maintains 60 FPS during gameplay
5. Test that memory usage remains stable across multiple game cycles
6. Test that all input combinations work correctly
7. Test that error handling prevents crashes

**Implementation Requirements:**
- Add comprehensive bounds checking for all physics calculations
- Implement window resize event handling to maintain aspect ratio
- Add delta time clamping to prevent large time steps
- Optimize rendering to minimize draw calls
- Add final error handling for edge cases
- Verify all constants match specification values
- Clean up any unused variables or code

**Performance Optimizations:**
- Cache frequently used calculations
- Minimize object creation in game loop
- Use efficient collision detection
- Proper resource cleanup

**Final Verification:**
```cpp
// Verify all specification constants
const float HORIZONTAL_ACCELERATION = 300.0f;
const float HORIZONTAL_DECELERATION = 200.0f; 
const float MAX_HORIZONTAL_SPEED = 300.0f;
const float JUMP_VELOCITY = -400.0f;
const float GRAVITY = 800.0f;
const float BALL_RADIUS = 40.0f;
const float GROUND_LEVEL = 680.0f;
```

**Acceptance Criteria:**
- Game runs smoothly at 60 FPS
- All physics match specifications exactly
- Complete game cycle works flawlessly
- No memory leaks or performance issues
- Robust error handling prevents crashes

Finalize the implementation with thorough testing and optimization.
```

## Summary

This blueprint provides a comprehensive, test-driven approach to building the C++ SFML Ball Game. Each prompt builds incrementally on the previous implementation, ensuring a solid foundation at each step. The TDD approach ensures that each feature is thoroughly tested before moving to the next phase, resulting in a robust, maintainable codebase that exactly matches the original specification.

The prompts are designed to be used with a code-generation LLM, providing clear requirements, implementation guidance, and acceptance criteria for each development phase.