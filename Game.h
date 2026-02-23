#pragma once
#include "Board.h"
#include "HUD.h"

class Game {
private:
    Board board;
    HUD hud;
    sf::RenderWindow& window;
    sf::Vector2i mousePosInt;
    sf::Vector2f mousePosition;
    bool theresIsARun;
    bool theresIsABoard;
    int currentScreen;
    int currentLevel;

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    Game(sf::RenderWindow& newWindow);
    Game(sf::RenderWindow& newWindow, int newCurrentScreen);
    ~Game();
    void setWindow();
    void loadSavedGame();
    
    sf::RenderWindow& getRenderWindow();

    void run();
    void optionsScreen();
    void mainMenuScreen();
    void gameScreen();
    void gameOverScreen();
    void drawScreen();
};