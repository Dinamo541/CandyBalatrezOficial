#include "Game.h"

Game::Game(sf::RenderWindow& newWindow) : window(newWindow) {
    currentScreen = 1;
    currentLevel = 1;
    theresIsARun = false;
    theresIsABoard = false;
    setWindow();
    hud.setWindow(&newWindow);
    hud.setCurrentScreen(&currentScreen);
    hud.setCurrentLevel(&currentLevel);
    board.setRenderWindow(&window);
    board.setHUD(&hud);
    board.setTable(hud.getTable());
    hud.setScore(board.getScorePTR());
    loadSavedGame();
}
    
Game::Game(sf::RenderWindow& newWindow, int newCurrentScreen) : window(newWindow) {
    currentScreen = newCurrentScreen;
    currentLevel = 1;
    theresIsARun = false;
    theresIsABoard = false;
    setWindow();
    hud.setWindow(&newWindow);
    hud.setCurrentScreen(&currentScreen);
    hud.setCurrentLevel(&currentLevel);
    board.setRenderWindow(&window);
    board.setHUD(&hud);
    board.setTable(hud.getTable());
    hud.setScore(board.getScorePTR());
    loadSavedGame();
}
Game::~Game() {
    if (theresIsABoard) board.saveBoard(currentLevel);
    else if (theresIsARun) {
        try {
            std::ofstream outFile("level.csv");
            if (outFile.is_open()) {
                outFile << currentLevel << ".N";
                outFile.close();
            }
            else {
                throw(-1);
            }
        }
        catch (int error) {
            if (error == -1) {
                std::cerr << "No se pudo abrir el archivo para leer.\n";
            }
        }
    }
    else {
        try {
            std::ofstream outFile("level.csv");
            if (outFile.is_open()) {
                outFile << "N";
                outFile.close();
            } else {
                throw(-1);
            }
        } catch (int error) {
            if (error == -1) {
                std::cerr << "No se pudo abrir el archivo para leer.\n";
            }
        }
    }
    printf("Gracias por jugar");
}
void Game::setWindow() {
    sf::Image icon;
    if (!icon.loadFromFile("assets/textures/icon.png")) {
        icon.loadFromFile("assets/textures/thumbnail.png");
        std::cerr << "No se pudo cargar la textura icon.png\n";
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
void Game::loadSavedGame() {
    std::string line;
    try {
        std::ifstream inFile("level.csv");
        if (inFile.is_open()) {
            std::getline(inFile, line);
            if (line == "N") return;
            theresIsABoard = true;
            theresIsARun = true;
            if (line[0] == '1') {
                currentLevel = 1;
                if (board.levelLoad(line.substr(line.find(".") + 1, line.length() - 3))) {
                    board.levelOne();
                }
            } else if (line[0] == '2') {
                currentLevel = 2;
                if (board.levelLoad(line.substr(line.find(".") + 1, line.length() - 3))) {
                    board.levelTwo();
                }
            } else if (line[0] == '3') {
                currentLevel = 3;
                if (board.levelLoad(line.substr(line.find(".") + 1, line.length() - 3))) {
                    board.levelThree();
                }
            }
            inFile.close();
        } else {
            throw(-1);
        }
    } catch (int error) {
        if (error == -1) {
            std::cerr << "No se pudo abrir el archivo para leer.\n";
        }
    }
}

sf::RenderWindow& Game::getRenderWindow() {
    return window;
}

void Game::run() {
    int SB = 0;
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        if (SB == 0) {
            hud.setBackgrounds();
            SB = 1;
        }
        mousePosInt = sf::Mouse::getPosition(window);
        mousePosition.x = static_cast<float>(mousePosInt.x);
        mousePosition.y = static_cast<float>(mousePosInt.y);

        if (currentScreen == 0) {
            hud.loadBGFrame(20.0f);
            optionsScreen();
        } else if (currentScreen == 1) {
            hud.loadBGFrame(30.0f);
            mainMenuScreen();
        } else if (currentScreen == 2) {
            hud.loadBGFrame(30.0f);
            gameScreen();
        } else if (currentScreen == 3) {
            hud.loadBGFrame(15.0f);
            gameOverScreen();
        }

        drawScreen();
    }
}
void Game::optionsScreen() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if ((event.type == sf::Event::Closed)) {
            window.close();
        } else if (event.mouseButton.button == sf::Keyboard::Escape) {
            currentScreen = 1;
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            
        }
    }
}
void Game::mainMenuScreen() {
    sf::Event event;

    hud.mouseIsOverMenu(mousePosition);

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (hud.isPlayButtonPressed(mousePosition)) {
                currentScreen = 2;
                if (currentLevel == 1) {
                    if (!theresIsARun) {
                        board.levelOne();
                        theresIsABoard = true;
                    }
                }
            } else if (hud.isOptionsButtonPressed(mousePosition)) {
                currentLevel = 1;
                theresIsARun = false;
                theresIsABoard = false;
                currentScreen = 0;
            } else if (hud.isQuitButtonPressed(mousePosition)) {
                window.close();
            }
        }
    }
}
void Game::gameScreen() {
    if (board.getMovesAllowed() == 0) {
        board.saveScore(currentLevel);
        board.explodeBombsLefts();
        currentScreen = 3;
        board.deselectAll();
        theresIsARun = board.getIsLevelComplete();
        hud.isLevelWasCompleted(board.getIsLevelComplete());
        hud.setGameOverScreen();
        theresIsABoard = false;
        return;
    }
    sf::Event event;

    hud.setGameScreen(std::to_string(board.getMovesAllowed()), std::to_string(board.getScoreObjetive()));
    board.ifMouseIsOn(mousePosition);
    theresIsABoard = true;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            currentScreen = 1;
        } else if (event.type == sf::Event::MouseButtonPressed) {
            board.select(mousePosition);
            theresIsARun = true;
        }
    }
}
void Game::gameOverScreen() {
    sf::Event event;

    hud.mouseIsOverGameOver(mousePosition, board.getIsLevelComplete());

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (hud.isContinueButtonPressed(mousePosition)) {
                currentScreen = 2;
                if (currentLevel == 1) {
                    board.levelOne();
                } else if (currentLevel == 2) {
                    board.levelTwo();
                } else if (currentLevel == 3) {
                    board.levelThree();
                }
                theresIsABoard = true;
            } else if (hud.isBackButtonPressed(mousePosition)) {
                currentScreen = 1;
                if (currentLevel == 1) {
                    board.levelOne();
                } else if (currentLevel == 2) {
                    board.levelTwo();
                } else if (currentLevel == 3) {
                    board.levelThree();
                }
                theresIsABoard = true;
            }
        }
    }
}
void Game::drawScreen() {
    window.clear();
    hud.drawBackGround();

    if (currentScreen == 2 || currentScreen == 3) { // Game , Game over
        board.printBoard();
    }

    hud.drawLevel();
    window.display();
}