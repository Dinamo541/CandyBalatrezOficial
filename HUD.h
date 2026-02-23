#pragma once
#include <SFML/Graphics.hpp>
#include "Table.h"

class HUD {
private:
    sf::RenderWindow* window = nullptr;
    Table* table = nullptr;
    sf::Font font;
    sf::Text playTx;
    sf::Text closeTx;
    sf::Text optionsTx;
    sf::Text candyTx;
    sf::Text movesTx;
    sf::Text scoresTx;
    sf::Text moveTx;
    sf::Text scoreTx;
    sf::Text currentLevelTx;
    sf::Text scoreObjetiveTx;
    sf::Text scoreObjetiveNumTx;
    sf::Text continueTx;
    sf::Text backTx;
    sf::Text titleTableTx;
    sf::Text tableTx[10];
    sf::Text currentTx;
    sf::Text saveTx;
    sf::Sprite BGMain;
    sf::Sprite BGLoad;
    sf::Texture BGLoadT;
    sf::Texture optionesTexture;
    sf::Texture scoreTexture;
    sf::Texture buttonTexture;
    sf::Texture* BGMainT = nullptr;
    sf::RectangleShape filter;
    sf::RectangleShape playButton;
    sf::RectangleShape optionsButton;
    sf::RectangleShape quitButton;
    sf::RectangleShape optionesShape;
    sf::RectangleShape scoreAndMovesShape;
    sf::RectangleShape continueButton;
    sf::RectangleShape backButton;
    sf::RectangleShape levelShape;
    sf::RectangleShape scoreObjetiveShape;
    sf::Clock BGClock;
    int* currentScreen = nullptr;
    int* currentLevel = nullptr;
    int* score = nullptr;
    int frame;
    int totalFrames;
    bool reverse;
    int level;

    HUD(const HUD&) = delete;
    HUD& operator=(const HUD&) = delete;

public:
    HUD();
    HUD(sf::RenderWindow* newWindow);
    ~HUD();
    void initialize();
    void loadTextures();
    void setTexts();
    void setBackgrounds();
    void setWindow(sf::RenderWindow* newWindow);
    void setScore(int* newScore);
    void setCurrentScreen(int* newCurrentScreen);
    void setCurrentLevel(int* newCurrentLevel);
    void setMovesText(int moves);
    void setScoreText();
    void setCurrentLevelTextGameScreen(int level);

    Table* getTable();

    bool isPlayButtonPressed(sf::Vector2f mousePosition);
    bool isOptionsButtonPressed(sf::Vector2f mousePosition);
    bool isQuitButtonPressed(sf::Vector2f mousePosition);
    bool isContinueButtonPressed(sf::Vector2f mousePosition);
    bool isBackButtonPressed(sf::Vector2f mousePosition);

    void mouseIsOverMenu(sf::Vector2f mousePosition);
    void mouseIsOverGameOver(sf::Vector2f mousePosition, bool levelCompleted);
    void setGameScreen(std::string moves, std::string scoreObjetive);
    void setScoreMovesGameFinishGS();
    void setGameOverScreen();
    void loadBGFrame(float GBFps);
    void isLevelWasCompleted(bool isLeveleCompleted);
    void setTable();
    void drawBackGround();
    void drawLevel();
};