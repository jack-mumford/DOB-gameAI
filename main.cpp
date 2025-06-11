#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

// Game Constants
const float HORIZONTAL_ACCELERATION = 300.0f;  // pixels/second²
const float HORIZONTAL_DECELERATION = 200.0f;  // pixels/second²
const float MAX_HORIZONTAL_SPEED = 300.0f;     // pixels/second
const float JUMP_VELOCITY = -400.0f;           // pixels/second (negative = upward)
const float GRAVITY = 800.0f;                  // pixels/second² (positive = downward)
const float BALL_RADIUS = 40.0f;               // pixels
const float GROUND_LEVEL = 680.0f;             // y-coordinate of ground
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// Game State Enumeration
enum class GameState {
    MainMenu,
    Playing,
    GameOver
};

// Menu Button Structure
struct MenuButton {
    sf::RectangleShape shape;
    sf::Text text;
    bool isSelected;
    
    MenuButton() : isSelected(false) {}
};

// Game Data Structure
struct GameData {
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    bool isOnGround;
    GameState currentState;
    int selectedMenuOption;
    sf::Clock deltaClock;
    
    GameData() : ballPosition(640.0f, GROUND_LEVEL), 
                 ballVelocity(0.0f, 0.0f), 
                 isOnGround(true),
                 currentState(GameState::MainMenu),
                 selectedMenuOption(0) {}
};

// Function Declarations
void initializeGraphics(sf::CircleShape& ball, 
                       sf::VertexArray& skyGradient, sf::RectangleShape& ground);
void setupMenuButtons(std::vector<MenuButton>& mainMenuButtons, 
                     std::vector<MenuButton>& gameOverButtons, sf::Font& font);
void handleEvents(sf::RenderWindow& window, GameData& gameData, 
                 const std::vector<MenuButton>& mainMenuButtons,
                 const std::vector<MenuButton>& gameOverButtons);
void updateGame(GameData& gameData, float deltaTime);
void updatePhysics(GameData& gameData, float deltaTime);
void handleCollisions(GameData& gameData);
void updateMenuSelection(GameData& gameData, const std::vector<MenuButton>& buttons);
void renderGame(sf::RenderWindow& window, const sf::CircleShape& ball,
               const sf::VertexArray& skyGradient, const sf::RectangleShape& ground,
               const GameData& gameData, const std::vector<MenuButton>& mainMenuButtons,
               const std::vector<MenuButton>& gameOverButtons);
void resetGame(GameData& gameData);

int main() {
    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing Ball");
    if (!window.isOpen()) {
        std::cerr << "Error: Failed to create SFML window" << std::endl;
        return -1;
    }
    window.setFramerateLimit(60);
    
    // Initialize game graphics
    sf::CircleShape ball;
    sf::VertexArray skyGradient;
    sf::RectangleShape ground;
    initializeGraphics(ball, skyGradient, ground);
    
    // Initialize font for menu text
    sf::Font font;
    bool fontLoaded = false;
    
    if (font.loadFromFile("/System/Library/Fonts/Helvetica.ttc")) {
        std::cout << "Successfully loaded Helvetica font" << std::endl;
        fontLoaded = true;
    } else if (font.loadFromFile("/System/Library/Fonts/Arial.ttf")) {
        std::cout << "Successfully loaded Arial font" << std::endl;
        fontLoaded = true;
    } else if (font.loadFromFile("/opt/homebrew/share/fonts/Arial.ttf")) {
        std::cout << "Successfully loaded Homebrew Arial font" << std::endl;
        fontLoaded = true;
    } else if (font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cout << "Successfully loaded Windows Arial font" << std::endl;
        fontLoaded = true;
    } else if (font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cout << "Successfully loaded DejaVu font" << std::endl;
        fontLoaded = true;
    } else {
        std::cerr << "Warning: Could not load any external font, using SFML default font" << std::endl;
        // SFML will use its default font if no font is set
    }
    
    // Initialize menu buttons
    std::vector<MenuButton> mainMenuButtons;
    std::vector<MenuButton> gameOverButtons;
    setupMenuButtons(mainMenuButtons, gameOverButtons, font);
    
    // Initialize game data
    GameData gameData;
    
    // Main game loop
    while (window.isOpen()) {
        float deltaTime = gameData.deltaClock.restart().asSeconds();
        deltaTime = std::min(deltaTime, 1.0f / 30.0f); // Cap delta time to prevent large jumps
        
        handleEvents(window, gameData, mainMenuButtons, gameOverButtons);
        updateGame(gameData, deltaTime);
        renderGame(window, ball, skyGradient, ground, gameData, mainMenuButtons, gameOverButtons);
    }
    
    return 0;
}

void initializeGraphics(sf::CircleShape& ball, 
                       sf::VertexArray& skyGradient, sf::RectangleShape& ground) {
    // Initialize sky gradient background
    skyGradient.setPrimitiveType(sf::Quads);
    skyGradient.resize(4);
    skyGradient[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color(135, 206, 235));           // Top-left: Light blue
    skyGradient[1] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH, 0), sf::Color(135, 206, 235)); // Top-right: Light blue
    skyGradient[2] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT), sf::Color::White); // Bottom-right: White
    skyGradient[3] = sf::Vertex(sf::Vector2f(0, WINDOW_HEIGHT), sf::Color::White);       // Bottom-left: White
    
    // Initialize ground rectangle
    ground.setSize(sf::Vector2f(WINDOW_WIDTH, 40));
    ground.setPosition(0, GROUND_LEVEL);
    ground.setFillColor(sf::Color(128, 128, 128)); // Gray
    
    // Initialize ball
    ball.setRadius(BALL_RADIUS);
    ball.setFillColor(sf::Color::Green);
    ball.setOutlineColor(sf::Color(0, 128, 0)); // Dark green
    ball.setOutlineThickness(3);
    ball.setOrigin(BALL_RADIUS, BALL_RADIUS); // Center origin
}

void setupMenuButtons(std::vector<MenuButton>& mainMenuButtons, 
                     std::vector<MenuButton>& gameOverButtons, sf::Font& font) {
    // Main menu buttons
    mainMenuButtons.resize(2);
    
    // Start Game button
    mainMenuButtons[0].shape.setSize(sf::Vector2f(200, 50));
    mainMenuButtons[0].shape.setPosition(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 50);
    mainMenuButtons[0].shape.setFillColor(sf::Color::White);
    mainMenuButtons[0].shape.setOutlineColor(sf::Color::Black);
    mainMenuButtons[0].shape.setOutlineThickness(2);
    
    // Only set font if it's loaded, otherwise SFML will use default
    if (font.getInfo().family != "") {
        mainMenuButtons[0].text.setFont(font);
    }
    mainMenuButtons[0].text.setString("Start Game");
    mainMenuButtons[0].text.setCharacterSize(24);
    mainMenuButtons[0].text.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = mainMenuButtons[0].text.getLocalBounds();
    mainMenuButtons[0].text.setPosition(
        WINDOW_WIDTH/2 - textBounds.width/2,
        WINDOW_HEIGHT/2 - 50 + 25 - textBounds.height/2
    );
    
    // Quit button
    mainMenuButtons[1].shape.setSize(sf::Vector2f(200, 50));
    mainMenuButtons[1].shape.setPosition(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 20);
    mainMenuButtons[1].shape.setFillColor(sf::Color::White);
    mainMenuButtons[1].shape.setOutlineColor(sf::Color::Black);
    mainMenuButtons[1].shape.setOutlineThickness(2);
    
    if (font.getInfo().family != "") {
        mainMenuButtons[1].text.setFont(font);
    }
    mainMenuButtons[1].text.setString("Quit");
    mainMenuButtons[1].text.setCharacterSize(24);
    mainMenuButtons[1].text.setFillColor(sf::Color::Black);
    textBounds = mainMenuButtons[1].text.getLocalBounds();
    mainMenuButtons[1].text.setPosition(
        WINDOW_WIDTH/2 - textBounds.width/2,
        WINDOW_HEIGHT/2 + 20 + 25 - textBounds.height/2
    );
    
    // Game over menu buttons
    gameOverButtons.resize(2);
    
    // Restart button
    gameOverButtons[0].shape.setSize(sf::Vector2f(200, 50));
    gameOverButtons[0].shape.setPosition(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 50);
    gameOverButtons[0].shape.setFillColor(sf::Color::White);
    gameOverButtons[0].shape.setOutlineColor(sf::Color::Black);
    gameOverButtons[0].shape.setOutlineThickness(2);
    
    if (font.getInfo().family != "") {
        gameOverButtons[0].text.setFont(font);
    }
    gameOverButtons[0].text.setString("Restart");
    gameOverButtons[0].text.setCharacterSize(24);
    gameOverButtons[0].text.setFillColor(sf::Color::Black);
    textBounds = gameOverButtons[0].text.getLocalBounds();
    gameOverButtons[0].text.setPosition(
        WINDOW_WIDTH/2 - textBounds.width/2,
        WINDOW_HEIGHT/2 - 50 + 25 - textBounds.height/2
    );
    
    // Quit button
    gameOverButtons[1].shape.setSize(sf::Vector2f(200, 50));
    gameOverButtons[1].shape.setPosition(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 20);
    gameOverButtons[1].shape.setFillColor(sf::Color::White);
    gameOverButtons[1].shape.setOutlineColor(sf::Color::Black);
    gameOverButtons[1].shape.setOutlineThickness(2);
    
    if (font.getInfo().family != "") {
        gameOverButtons[1].text.setFont(font);
    }
    gameOverButtons[1].text.setString("Quit");
    gameOverButtons[1].text.setCharacterSize(24);
    gameOverButtons[1].text.setFillColor(sf::Color::Black);
    textBounds = gameOverButtons[1].text.getLocalBounds();
    gameOverButtons[1].text.setPosition(
        WINDOW_WIDTH/2 - textBounds.width/2,
        WINDOW_HEIGHT/2 + 20 + 25 - textBounds.height/2
    );
}

void handleEvents(sf::RenderWindow& window, GameData& gameData, 
                 const std::vector<MenuButton>& mainMenuButtons,
                 const std::vector<MenuButton>& gameOverButtons) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (gameData.currentState == GameState::MainMenu) {
                if (event.key.code == sf::Keyboard::Up) {
                    gameData.selectedMenuOption = (gameData.selectedMenuOption - 1 + mainMenuButtons.size()) % mainMenuButtons.size();
                } else if (event.key.code == sf::Keyboard::Down) {
                    gameData.selectedMenuOption = (gameData.selectedMenuOption + 1) % mainMenuButtons.size();
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (gameData.selectedMenuOption == 0) {
                        gameData.currentState = GameState::Playing;
                        resetGame(gameData);
                    } else if (gameData.selectedMenuOption == 1) {
                        window.close();
                    }
                }
            } else if (gameData.currentState == GameState::GameOver) {
                if (event.key.code == sf::Keyboard::Up) {
                    gameData.selectedMenuOption = (gameData.selectedMenuOption - 1 + gameOverButtons.size()) % gameOverButtons.size();
                } else if (event.key.code == sf::Keyboard::Down) {
                    gameData.selectedMenuOption = (gameData.selectedMenuOption + 1) % gameOverButtons.size();
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (gameData.selectedMenuOption == 0) {
                        gameData.currentState = GameState::Playing;
                        resetGame(gameData);
                    } else if (gameData.selectedMenuOption == 1) {
                        window.close();
                    }
                }
            } else if (gameData.currentState == GameState::Playing) {
                // Handle jump input (event-based for single jump)
                if (event.key.code == sf::Keyboard::Up && gameData.isOnGround) {
                    gameData.ballVelocity.y = JUMP_VELOCITY;
                    gameData.isOnGround = false;
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

void updateGame(GameData& gameData, float deltaTime) {
    if (gameData.currentState == GameState::Playing) {
        updatePhysics(gameData, deltaTime);
        handleCollisions(gameData);
        
        // Check for game over condition
        if (gameData.ballPosition.y > GROUND_LEVEL + BALL_RADIUS) {
            gameData.currentState = GameState::GameOver;
            gameData.selectedMenuOption = 0; // Reset to first option
        }
    }
}

void updatePhysics(GameData& gameData, float deltaTime) {
    // Handle horizontal movement (continuous input)
    bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    
    // Apply horizontal acceleration/deceleration
    if (leftPressed && !rightPressed) {
        gameData.ballVelocity.x -= HORIZONTAL_ACCELERATION * deltaTime;
    } else if (rightPressed && !leftPressed) {
        gameData.ballVelocity.x += HORIZONTAL_ACCELERATION * deltaTime;
    } else {
        // Apply deceleration when no keys are pressed
        if (gameData.ballVelocity.x > 0) {
            gameData.ballVelocity.x = std::max(0.0f, gameData.ballVelocity.x - HORIZONTAL_DECELERATION * deltaTime);
        } else if (gameData.ballVelocity.x < 0) {
            gameData.ballVelocity.x = std::min(0.0f, gameData.ballVelocity.x + HORIZONTAL_DECELERATION * deltaTime);
        }
    }
    
    // Clamp horizontal velocity to maximum speed
    gameData.ballVelocity.x = std::max(-MAX_HORIZONTAL_SPEED, std::min(MAX_HORIZONTAL_SPEED, gameData.ballVelocity.x));
    
    // Apply gravity
    if (!gameData.isOnGround) {
        gameData.ballVelocity.y += GRAVITY * deltaTime;
    }
    
    // Update position based on velocity
    gameData.ballPosition.x += gameData.ballVelocity.x * deltaTime;
    gameData.ballPosition.y += gameData.ballVelocity.y * deltaTime;
}

void handleCollisions(GameData& gameData) {
    // Horizontal boundary collisions (perfect bounce)
    if (gameData.ballPosition.x - BALL_RADIUS <= 0) {
        gameData.ballPosition.x = BALL_RADIUS;
        gameData.ballVelocity.x = -gameData.ballVelocity.x;
    } else if (gameData.ballPosition.x + BALL_RADIUS >= WINDOW_WIDTH) {
        gameData.ballPosition.x = WINDOW_WIDTH - BALL_RADIUS;
        gameData.ballVelocity.x = -gameData.ballVelocity.x;
    }
    
    // Ground collision
    if (gameData.ballPosition.y >= GROUND_LEVEL) {
        gameData.ballPosition.y = GROUND_LEVEL;
        gameData.ballVelocity.y = 0;
        gameData.isOnGround = true;
    } else {
        gameData.isOnGround = false;
    }
}

void renderGame(sf::RenderWindow& window, const sf::CircleShape& ball,
               const sf::VertexArray& skyGradient, const sf::RectangleShape& ground,
               const GameData& gameData, const std::vector<MenuButton>& mainMenuButtons,
               const std::vector<MenuButton>& gameOverButtons) {
    window.clear();
    
    // Always render background
    window.draw(skyGradient);
    window.draw(ground);
    
    if (gameData.currentState == GameState::Playing || gameData.currentState == GameState::GameOver) {
        // Render ball
        sf::CircleShape renderBall = ball;
        renderBall.setPosition(gameData.ballPosition);
        window.draw(renderBall);
    }
    
    if (gameData.currentState == GameState::MainMenu) {
        // Render main menu
        for (size_t i = 0; i < mainMenuButtons.size(); ++i) {
            sf::RectangleShape buttonShape = mainMenuButtons[i].shape;
            if (i == static_cast<size_t>(gameData.selectedMenuOption)) {
                buttonShape.setOutlineColor(sf::Color::White);
                buttonShape.setOutlineThickness(6);
            }
            window.draw(buttonShape);
            window.draw(mainMenuButtons[i].text);
        }
    } else if (gameData.currentState == GameState::GameOver) {
        // Render game over menu
        for (size_t i = 0; i < gameOverButtons.size(); ++i) {
            sf::RectangleShape buttonShape = gameOverButtons[i].shape;
            if (i == static_cast<size_t>(gameData.selectedMenuOption)) {
                buttonShape.setOutlineColor(sf::Color::White);
                buttonShape.setOutlineThickness(6);
            }
            window.draw(buttonShape);
            window.draw(gameOverButtons[i].text);
        }
    }
    
    window.display();
}

void resetGame(GameData& gameData) {
    gameData.ballPosition = sf::Vector2f(640.0f, GROUND_LEVEL);
    gameData.ballVelocity = sf::Vector2f(0.0f, 0.0f);
    gameData.isOnGround = true;
}
