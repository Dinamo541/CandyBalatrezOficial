#pragma once
#include <cstdlib>
#include "Gems.h"
#include "Block.h"
#include "Bombs.h"
#include "HUD.h"

class Board {
private:
    sf::RenderWindow* window = nullptr;
    Gems*** board = nullptr;
    Table* table = nullptr;
    HUD* hud = nullptr;
    bool isOneSelect;
    int movesAllowed;
    int GO[2];
    int GT[2];
    int score;
    int scoreObjetive;

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

public:
    Board();
    ~Board();
    void initialize();
    bool levelLoad(std::string data);

    void saveScore(int level);
    void saveBoard(int level);

    void setHUD(HUD* newHUD);
    void setRenderWindow(sf::RenderWindow* newRenderWindow);
    void setTable(Table* newTable);

    int getMovesAllowed() const;
    int getScore() const;
    int getScoreObjetive() const;
    bool getIsLevelComplete() const;
    int* getScorePTR();

    void levelOne();
    void levelTwo();
    void levelThree();
    int getRandId(int i, int j);
    void printBoard();
    void ifMouseIsOn(sf::Vector2f mousePosition);
    void select(sf::Vector2f mousePosition);
    void verifyChange();
    void deleteGemAt(int x, int y);
    bool isBombslefts();
    void explodeBombsLefts();
    void bombExplode(int x1, int y1, int x2, int y2);
    bool confirmIsColRellyEmpty(int x);
    void fillCol(int x);
    void animateShake(int x, int y);
    void animateShakeTwoGems();
    void animategemAppear(int x, int y);
    void animateGemDisappearance(int x, int y);
    void animateGemSwap(int x1, int y1, int x2, int y2, float customDuration);
    void animateGemFall(int x1, int y1, int x2, int y2);
    sf::Vector2f lerp(sf::Vector2f start, sf::Vector2f end, float t);
    void changeGemsPositions();
    void changeByIndex(int i, int j, int k, int h);
    void deselectAll();
    bool findMacht();
    void deleteGems();
    void deleteJ(int i, int j);
    void deleteI(int i, int j);
    void macht();
    void fillUp();
    bool findZeros();
    void gravity();
    void fall(int i, int j);
};