#include "HUD.h"

HUD::HUD() {
    loadTextures();
    initialize();
}
HUD::HUD(sf::RenderWindow* newWindow) : window(newWindow) {
    loadTextures();
    initialize();
}
HUD::~HUD() {
    if (BGMainT) {
        delete[] BGMainT;
        BGMainT = nullptr;
    }
    delete table;
    window = nullptr;
    currentScreen = nullptr;
}
void HUD::initialize() {
    table = new Table("first.csv", "second.csv", "third.csv");
    frame = 0;
    level = 0;
    totalFrames = 300;
    reverse = false;
    playButton.setSize(sf::Vector2f(145.0f, 60.0f));
    playButton.setOrigin(72.5f, 30.0f);
    playButton.setTexture(&buttonTexture);
    playButton.setPosition(230.f, 480.f);

    optionsButton.setSize(sf::Vector2f(175.0f, 60.0f));
    optionsButton.setOrigin(87.5f, 30.0f);
    optionsButton.setTexture(&buttonTexture);
    optionsButton.setPosition(400.f, 480.f);

    quitButton.setSize(sf::Vector2f(165.0f, 60.0f));
    quitButton.setOrigin(77.5f, 30.0f);
    quitButton.setTexture(&buttonTexture);
    quitButton.setPosition(575.f, 480.f);

    optionesShape.setSize(sf::Vector2f(525.f, 75.f));
    optionesShape.setFillColor(sf::Color(77, 77, 77));
    optionesShape.setOrigin(262.5f, 37.5f);
    optionesShape.setPosition(408.5f, 480.f);
    optionesShape.setTexture(&optionesTexture);

    scoreAndMovesShape.setSize(sf::Vector2f(200.f, 250.f));
    scoreAndMovesShape.setFillColor(sf::Color(79, 99, 103));
    scoreAndMovesShape.setOrigin(100.f, 125.f);
    scoreAndMovesShape.setPosition(600.f, 560.f);
    scoreAndMovesShape.setTexture(&scoreTexture);

    continueButton.setSize(sf::Vector2f(190.f, 60.f));
    continueButton.setOrigin(95.f, 30.f);
    continueButton.setTexture(&buttonTexture);
    continueButton.setPosition(300.f, 500.f);

    backButton.setSize(sf::Vector2f(190.f, 60.f));
    backButton.setOrigin(97.f, 30.f);
    backButton.setTexture(&buttonTexture);
    backButton.setPosition(500.f, 500.f);

    levelShape.setSize(sf::Vector2f(200.f, 60.f));
    levelShape.setFillColor(sf::Color(79, 99, 103));
    levelShape.setOrigin(100.f, 30.f);
    levelShape.setPosition(0.0f, 0.0f);
    levelShape.setTexture(&optionesTexture);

    scoreObjetiveShape.setSize(sf::Vector2f(190.f, 120.f));
    scoreObjetiveShape.setOrigin(95.f, 60.f);
    scoreObjetiveShape.setFillColor(sf::Color(79, 99, 103));
    scoreObjetiveShape.setTexture(&optionesTexture);

    filter.setSize(sf::Vector2f(800, 600));
    filter.setFillColor(sf::Color(0, 0, 0, 160));
    setTexts();
}
void HUD::loadTextures() {
    if (!font.loadFromFile("assets/fonts/m6x11plus.ttf")) {
        std::cerr << "No se pudo cargar la fuente aptos.ttf\n";
    }
    if (!buttonTexture.loadFromFile("assets/textures/PlayButton.png")) {
        buttonTexture.loadFromFile("assets/textures/thumbnail.png");
        std::cerr << "No se pudo cargar la textura PlayButton.png\n";
    }
    if (!optionesTexture.loadFromFile("assets/textures/shape.png")) {
        optionesTexture.loadFromFile("assets/textures/shape.png");
        std::cerr << "No se pudo cargar la textura backgroundLoad.png\n";
    }
    if (!BGLoadT.loadFromFile("assets/textures/backgroundLoad.png")) {
        BGLoadT.loadFromFile("assets/textures/thumbnail.png");
        std::cerr << "No se pudo cargar la textura backgroundLoad.png\n";
    }
    if (!scoreTexture.loadFromFile("assets/textures/scoreShape.png")) {
        scoreTexture.loadFromFile("assets/textures/thumbnail.png");
        std::cerr << "No se pudo cargar la textura scoreShape.png\n";
    }
}
void HUD::setTexts() {
    playTx.setString("PLAY");
    playTx.setFont(font);
    playTx.setCharacterSize(50);
    playTx.setFillColor(sf::Color::White);
    playTx.setOutlineThickness(1.0f);
    playTx.setOutlineColor(sf::Color::Black);
    sf::FloatRect bounds = playTx.getLocalBounds();
    playTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    playTx.setPosition(sf::Vector2f(230.f, 478.f));
    playTx.setStyle(sf::Text::Bold);
    
    optionsTx.setFont(font);
    optionsTx.setString("OPCIONES");
    optionsTx.setCharacterSize(40);
    optionsTx.setFillColor(sf::Color::White);
    optionsTx.setOutlineThickness(1.0f);
    optionsTx.setOutlineColor(sf::Color::Black);
    bounds = optionsTx.getLocalBounds();
    optionsTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    optionsTx.setPosition(sf::Vector2f(398.f, 478.f));
    optionsTx.setStyle(sf::Text::Bold);
    
    closeTx.setFont(font);
    closeTx.setString("CERRAR");
    closeTx.setCharacterSize(50);
    closeTx.setFillColor(sf::Color::White);
    closeTx.setOutlineThickness(1.0f);
    closeTx.setOutlineColor(sf::Color::Black);
    bounds = closeTx.getLocalBounds();
    closeTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    closeTx.setPosition(sf::Vector2f(575.f, 478.f));
    closeTx.setStyle(sf::Text::Bold);
    
    candyTx.setFont(font);
    candyTx.setString("CANDY");
    candyTx.setCharacterSize(100);
    candyTx.setFillColor(sf::Color(242, 242, 242));
    candyTx.setOutlineThickness(2.0f);
    candyTx.setOutlineColor(sf::Color::Black);
    bounds = candyTx.getLocalBounds();
    candyTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    candyTx.setPosition(sf::Vector2f(400.f, 100.f));
    candyTx.setStyle(sf::Text::Bold | sf::Text::Italic);
    
    scoresTx.setFont(font);
    scoresTx.setString("0");
    scoresTx.setCharacterSize(50);
    scoresTx.setOutlineThickness(2.f);
    scoresTx.setFillColor(sf::Color(0, 156, 253));
    scoresTx.setOutlineColor(sf::Color::Black);
    bounds = scoresTx.getLocalBounds();
    scoresTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    scoresTx.setPosition(sf::Vector2f(669.5f, 256.0f));
    scoresTx.setStyle(sf::Text::Bold);
    
    scoreTx.setFont(font);
    scoreTx.setString("Puntaje");
    scoreTx.setCharacterSize(40);
    scoreTx.setOutlineThickness(2.f);
    scoreTx.setFillColor(sf::Color(253, 160, 0));
    scoreTx.setOutlineColor(sf::Color::Black);
    bounds = scoreTx.getLocalBounds();
    scoreTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    scoreTx.setPosition(sf::Vector2f(669.5f, 206.0f));
    scoreTx.setStyle(sf::Text::Bold);
    
    movesTx.setFont(font);
    movesTx.setString("0");
    movesTx.setCharacterSize(50);
    movesTx.setOutlineThickness(2.f);
    movesTx.setFillColor(sf::Color(0, 156, 253));
    movesTx.setOutlineColor(sf::Color::Black);
    bounds = movesTx.getLocalBounds();
    movesTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    movesTx.setStyle(sf::Text::Bold);
    
    moveTx.setFont(font);
    moveTx.setString("Jugadas");
    moveTx.setCharacterSize(40);
    moveTx.setOutlineThickness(2.f);
    moveTx.setFillColor(sf::Color(253, 160, 0));
    moveTx.setOutlineColor(sf::Color::Black);
    bounds = moveTx.getLocalBounds();
    moveTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    moveTx.setStyle(sf::Text::Bold);
    
    currentLevelTx.setFont(font);
    currentLevelTx.setString("Nivel terminado");
    currentLevelTx.setCharacterSize(50);
    currentLevelTx.setOutlineThickness(2.f);
    currentLevelTx.setFillColor(sf::Color(0, 156, 253));
    currentLevelTx.setOutlineColor(sf::Color::Black);
    bounds = currentLevelTx.getLocalBounds();
    currentLevelTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    currentLevelTx.setPosition(sf::Vector2f(400.f, 202.0f));
    currentLevelTx.setStyle(sf::Text::Bold);

    scoreObjetiveTx.setFont(font);
    scoreObjetiveTx.setString("Objetivo");
    scoreObjetiveTx.setCharacterSize(40);
    scoreObjetiveTx.setOutlineThickness(2.f);
    scoreObjetiveTx.setFillColor(sf::Color(2, 201, 9));
    scoreObjetiveTx.setOutlineColor(sf::Color::Black);
    bounds = scoreObjetiveTx.getLocalBounds();
    scoreObjetiveTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    scoreObjetiveTx.setPosition(sf::Vector2f(669.5f, 156.0f));
    scoreObjetiveTx.setStyle(sf::Text::Bold);

    scoreObjetiveNumTx.setFont(font);
    scoreObjetiveNumTx.setString("0");
    scoreObjetiveNumTx.setCharacterSize(50);
    scoreObjetiveNumTx.setOutlineThickness(2.f);
    scoreObjetiveNumTx.setFillColor(sf::Color(253, 95, 85));
    scoreObjetiveNumTx.setOutlineColor(sf::Color::Black);
    bounds = scoreObjetiveNumTx.getLocalBounds();
    scoreObjetiveNumTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    scoreObjetiveNumTx.setStyle(sf::Text::Bold);

    continueTx.setFont(font);
    continueTx.setString("Continuar");
    continueTx.setCharacterSize(40);
    continueTx.setFillColor(sf::Color::White);
    continueTx.setOutlineThickness(1.0f);
    continueTx.setOutlineColor(sf::Color::Black);
    bounds = continueTx.getLocalBounds();
    continueTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    continueTx.setPosition(sf::Vector2f(300.f, 498.f));
    continueTx.setStyle(sf::Text::Bold);

    backTx.setFont(font);
    backTx.setString("Regresar");
    backTx.setCharacterSize(40);
    backTx.setFillColor(sf::Color::White);
    backTx.setOutlineThickness(1.0f);
    backTx.setOutlineColor(sf::Color::Black);
    bounds = backTx.getLocalBounds();
    backTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    backTx.setPosition(sf::Vector2f(500.f, 498.f));
    backTx.setStyle(sf::Text::Bold);

    titleTableTx.setFont(font);
    titleTableTx.setString("Tabla Mejores");
    titleTableTx.setCharacterSize(26);
    titleTableTx.setFillColor(sf::Color(0, 156, 253));
    titleTableTx.setOutlineThickness(1.5f);
    titleTableTx.setOutlineColor(sf::Color::Black);
    bounds = titleTableTx.getLocalBounds();
    titleTableTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    titleTableTx.setPosition(sf::Vector2f(680.f, 174.f));
    titleTableTx.setStyle(sf::Text::Bold);

    float position = 0.f;
    for (int i = 0; i < 10; i++) {
        position += 26.f;
        tableTx[i].setFont(font);
        tableTx[i].setString("1");
        tableTx[i].setCharacterSize(25);
        tableTx[i].setFillColor(sf::Color(0, 156, 253));
        tableTx[i].setOutlineThickness(1.5f);
        tableTx[i].setOutlineColor(sf::Color::Black);
        bounds = tableTx[i].getLocalBounds();
        tableTx[i].setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        tableTx[i].setPosition(sf::Vector2f(680.f, 185.f + position));
        tableTx[i].setStyle(sf::Text::Bold);
    }

    position += 26.f;
    currentTx.setFont(font);
    currentTx.setString("1");
    currentTx.setCharacterSize(25);
    currentTx.setFillColor(sf::Color(0, 156, 253));
    currentTx.setOutlineThickness(1.5f);
    currentTx.setOutlineColor(sf::Color::Black);
    bounds = currentTx.getLocalBounds();
    currentTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    currentTx.setPosition(sf::Vector2f(680.f, 185.f + position));
    currentTx.setStyle(sf::Text::Bold);

    position += 26.f;
    saveTx.setFont(font);
    saveTx.setString("Guardar");
    saveTx.setCharacterSize(25);
    saveTx.setFillColor(sf::Color(0, 156, 253));
    saveTx.setOutlineThickness(1.5f);
    saveTx.setOutlineColor(sf::Color::Black);
    bounds = saveTx.getLocalBounds();
    saveTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    saveTx.setPosition(sf::Vector2f(680.f, 185.f + position));
    saveTx.setStyle(sf::Text::Bold);
}
void HUD::setBackgrounds() {
    BGMainT = new sf::Texture[totalFrames];
    std::string frame = "";
    std::string loadString = "Cargando 00%";
    sf::Text loadText;
    loadText.setFont(font);
    loadText.setString(loadString);
    loadText.setCharacterSize(50);
    loadText.setFillColor(sf::Color(250, 55, 42));
    loadText.setOutlineThickness(1.5f);
    loadText.setOutlineColor(sf::Color::Black);
    sf::FloatRect bounds = loadText.getLocalBounds();
    loadText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    loadText.setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
    sf::Vector2u textureSize1 = BGLoadT.getSize();
    sf::Vector2u windowSize = window->getSize();
    BGLoad.setScale(float(windowSize.x) / textureSize1.x, float(windowSize.y) / textureSize1.y);
    BGLoad.setTexture(BGLoadT);
    for (int i = 0; i < totalFrames; i++) {
        loadString = "Cargando " + std::to_string((i * 100) / totalFrames) + "%";
        loadText.setString(loadString);
        if (i < 10) {
            frame = "00" + std::to_string(i);
        } else if (i < 100) {
            frame = "0" + std::to_string(i);
        } else {
            frame = std::to_string(i);
        }
        BGMainT[i].loadFromFile("assets/frames/gbmframes_" + frame + ".jpg");
        sf::Event ev;
        while (window->pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window->close();
        }
        window->clear();
        window->draw(BGLoad);
        window->draw(loadText);
        window->display();
    }
    sf::Vector2u textureSize2 = BGMainT[0].getSize();
    BGMain.setScale(float(windowSize.x) / textureSize2.x, float(windowSize.y) / textureSize2.y);
}

void HUD::setWindow(sf::RenderWindow* newWindow) {
    window = newWindow;
}
void HUD::setScore(int* newScore) {
    score = newScore;
}
void HUD::setCurrentScreen(int* newCurrentScreen) {
    currentScreen = newCurrentScreen;
}
void HUD::setCurrentLevel(int* newCurrentLevel) {
    currentLevel = newCurrentLevel;
}
void HUD::setMovesText(int moves) {
    movesTx.setString(std::to_string(moves));
    sf::FloatRect bounds = movesTx.getLocalBounds();
    movesTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}
void HUD::setScoreText() {
    scoresTx.setString(std::to_string(*score));
    sf::FloatRect bounds = scoresTx.getLocalBounds();
    scoresTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}
void HUD::setCurrentLevelTextGameScreen(int level) {
    currentLevelTx.setString("Nivel " + std::to_string(level));
    sf::FloatRect bounds = currentLevelTx.getLocalBounds();
    currentLevelTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    if (level == 1) {
        currentLevelTx.setFillColor(sf::Color(253, 236, 0));
    } else if (level == 2) {
        currentLevelTx.setFillColor(sf::Color(253, 162, 0));
    } else if (level == 3) {
        currentLevelTx.setFillColor(sf::Color(253, 95, 85));
    }
}

Table* HUD::getTable() { return table; }

bool HUD::isPlayButtonPressed(sf::Vector2f mousePosition) {
    if (playButton.getGlobalBounds().contains(mousePosition)) {
        scoreAndMovesShape.setSize(sf::Vector2f(200.f, 250.f));
        scoreAndMovesShape.setFillColor(sf::Color(79, 99, 103));
        scoreAndMovesShape.setOrigin(100.f, 125.f);
        scoreAndMovesShape.setPosition(600.f, 560.f);
        return true;
    }
    return false;
}
bool HUD::isOptionsButtonPressed(sf::Vector2f mousePosition) { return optionsButton.getGlobalBounds().contains(mousePosition); }
bool HUD::isQuitButtonPressed(sf::Vector2f mousePosition) { return quitButton.getGlobalBounds().contains(mousePosition); }
bool HUD::isContinueButtonPressed(sf::Vector2f mousePosition) { return continueButton.getGlobalBounds().contains(mousePosition); }
bool HUD::isBackButtonPressed(sf::Vector2f mousePosition) { return backButton.getGlobalBounds().contains(mousePosition); }

void HUD::mouseIsOverMenu(sf::Vector2f mousePosition) {
    if (playButton.getGlobalBounds().contains(mousePosition)) {
        playButton.setFillColor(sf::Color(213, 55, 45));
        optionsButton.setFillColor(sf::Color(0, 156, 253));
        quitButton.setFillColor(sf::Color(253, 162, 0));
    } else if (optionsButton.getGlobalBounds().contains(mousePosition)) {
        optionsButton.setFillColor(sf::Color(0, 116, 213));
        playButton.setFillColor(sf::Color(253, 95, 85));
        quitButton.setFillColor(sf::Color(253, 162, 0));
    } else if (quitButton.getGlobalBounds().contains(mousePosition)) {
        quitButton.setFillColor(sf::Color(213, 122, 0));
        playButton.setFillColor(sf::Color(253, 95, 85));
        optionsButton.setFillColor(sf::Color(0, 156, 253));
    } else {
        playButton.setFillColor(sf::Color(253, 95, 85));
        optionsButton.setFillColor(sf::Color(0, 156, 253));
        quitButton.setFillColor(sf::Color(253, 162, 0));
    }
}
void HUD::mouseIsOverGameOver(sf::Vector2f mousePosition, bool levelCompleted) {
    if (levelCompleted) {
        if (continueButton.getGlobalBounds().contains(mousePosition)) {
            continueButton.setFillColor(sf::Color(0, 116, 213));
            backButton.setFillColor(sf::Color(253, 162, 0));
        }  else if (backButton.getGlobalBounds().contains(mousePosition)) {
            backButton.setFillColor(sf::Color(213, 122, 0));
            continueButton.setFillColor(sf::Color(0, 156, 253));
        } else {
            continueButton.setFillColor(sf::Color(0, 156, 253));
            backButton.setFillColor(sf::Color(253, 162, 0));
        }
    } else {
        if (continueButton.getGlobalBounds().contains(mousePosition)) {
            continueButton.setFillColor(sf::Color(213, 55, 45));
            backButton.setFillColor(sf::Color(253, 162, 0));
        } else if (backButton.getGlobalBounds().contains(mousePosition)) {
            backButton.setFillColor(sf::Color(213, 122, 0));
            continueButton.setFillColor(sf::Color(253, 95, 85));
        } else {
            continueButton.setFillColor(sf::Color(253, 95, 85));
            backButton.setFillColor(sf::Color(253, 162, 0));
        } 
    }
}
void HUD::setGameScreen(std::string moves, std::string scoreObjetive) {
    setCurrentLevelTextGameScreen(*currentLevel);
    scoresTx.setString(std::to_string(*score));
    movesTx.setString(moves);
    scoreObjetiveNumTx.setString(scoreObjetive);

    sf::FloatRect bounds = scoresTx.getLocalBounds();
    scoresTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    bounds = movesTx.getLocalBounds();
    movesTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    bounds = scoreObjetiveNumTx.getLocalBounds();
    scoreObjetiveNumTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    setScoreMovesGameFinishGS();
    scoreObjetiveTx.setPosition(sf::Vector2f(669.5f, 136.0f));
    scoreObjetiveNumTx.setPosition(sf::Vector2f(669.5f, 186.0f));
    scoreTx.setPosition(sf::Vector2f(669.5f, 276.0f));
    scoresTx.setPosition(sf::Vector2f(669.5f, 326.0f));
    moveTx.setPosition(sf::Vector2f(669.0f, 394.0f));
    movesTx.setPosition(sf::Vector2f(669.5f, 446.0f));

    levelShape.setSize(sf::Vector2f(200.f, 60.f));
    levelShape.setOrigin(100.f, 30.f);
    levelShape.setPosition(300.0f, 50.0f);
    currentLevelTx.setPosition(sf::Vector2f(305.0f, 50.0f));
}
void HUD::setScoreMovesGameFinishGS() {
    scoreAndMovesShape.setSize(sf::Vector2f(200.f, 250.f));
    scoreAndMovesShape.setFillColor(sf::Color(79, 99, 103));
    scoreAndMovesShape.setOrigin(100.f, 125.f);
    scoreAndMovesShape.setPosition(670.0f, 370.0f);
    scoreObjetiveShape.setPosition(670.0f, 160.0f);
}
void HUD::setGameOverScreen() {
    setScoreText();

    scoreObjetiveTx.setPosition(sf::Vector2f(400.f, 207.0f));
    scoreObjetiveNumTx.setPosition(sf::Vector2f(400.f, 257.0f));
    scoreTx.setPosition(sf::Vector2f(400.f, 323.0f));
    scoresTx.setPosition(sf::Vector2f(400.f, 373.0f));

    scoreAndMovesShape.setSize(sf::Vector2f(300.f, 250.f));
    scoreAndMovesShape.setFillColor(sf::Color(79, 99, 103));
    scoreAndMovesShape.setOrigin(150.f, 125.f);
    scoreAndMovesShape.setPosition(400.f, 300.f);
}
void HUD::loadBGFrame(float GBFps) {
    GBFps = GBFps / 2.1f;
    if (BGClock.getElapsedTime().asSeconds() > 1.0f / GBFps && !reverse) { // 15 FPS normalmente
        frame++;
        BGMain.setTexture(BGMainT[frame]);
        BGClock.restart();
        if (frame == totalFrames - 1) {
            reverse = true;
        }
    } else if (BGClock.getElapsedTime().asSeconds() > 1.0f / GBFps && reverse) {
        frame--;
        BGMain.setTexture(BGMainT[frame]);
        BGClock.restart();
        if (frame == 0) {
            frame = 0;
            reverse = false;
        }
    }
}
void HUD::isLevelWasCompleted(bool isLeveleCompleted) {
    levelShape.setSize(sf::Vector2f(450.f, 60.f));
    levelShape.setOrigin(225.f, 30.f);
    levelShape.setPosition(400.0f, 120.0f);

    continueTx.setString("Continuar");
    sf::FloatRect bounds = continueTx.getLocalBounds();
    continueTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    continueTx.setPosition(sf::Vector2f(300.f, 498.f));
    setTable();

    if (isLeveleCompleted && *currentLevel == 1) {
        *currentLevel = 2;
        currentLevelTx.setString("Nivel 1 Completado");
        bounds = currentLevelTx.getLocalBounds();
        currentLevelTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        currentLevelTx.setFillColor(sf::Color(2, 17, 224));
        scoresTx.setFillColor(sf::Color(43, 224, 7));
    } else if (isLeveleCompleted && *currentLevel == 2) {
        *currentLevel = 3;
        currentLevelTx.setString("Nivel 2 Completado");
        bounds = currentLevelTx.getLocalBounds();
        currentLevelTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        currentLevelTx.setFillColor(sf::Color(2, 17, 224));
        scoresTx.setFillColor(sf::Color(43, 224, 7));
    } else if (isLeveleCompleted && *currentLevel == 3) {
        *currentLevel = 1;
        currentLevelTx.setString("Juego Completado");
        bounds = currentLevelTx.getLocalBounds();
        currentLevelTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        continueTx.setString("Reintentar");
        sf::FloatRect bounds = continueTx.getLocalBounds();
        continueTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        continueTx.setPosition(sf::Vector2f(300.f, 498.f));
        currentLevelTx.setFillColor(sf::Color(2, 17, 224));
        scoresTx.setFillColor(sf::Color(43, 224, 7));
    } else if (!isLeveleCompleted) {
        *currentLevel = 1;
        currentLevelTx.setString("Nivel Fallido");
        bounds = currentLevelTx.getLocalBounds();
        currentLevelTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        continueTx.setString("Reintentar");
        sf::FloatRect bounds = continueTx.getLocalBounds();
        continueTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        continueTx.setPosition(sf::Vector2f(300.f, 498.f));
        currentLevelTx.setFillColor(sf::Color(213, 55, 45));
        scoresTx.setFillColor(sf::Color(213, 55, 45));
        levelShape.setSize(sf::Vector2f(300.f, 60.f));
        levelShape.setOrigin(150.f, 30.f);
        levelShape.setPosition(400.0f, 120.0f);
    }
    currentLevelTx.setPosition(sf::Vector2f(400.f, 121.0f));
}
void HUD::setTable() { // En proceso --------------------------
    level = *currentLevel;
    if (level == 1) {
        for (int i = 1; i < 11; i++) {
            File* file = table->getFileByIndexFi(std::to_string(i));
            if (file == nullptr) {
                tableTx[i-1].setString(std::to_string(i) + " - Sin Puntaje");
                sf::FloatRect bounds = tableTx[i-1].getLocalBounds();
                tableTx[i-1].setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
            } else {
                tableTx[i-1].setString(file->getId() + " - " + file->getName()+ ": " + file->getScore() );
                sf::FloatRect bounds = tableTx[i-1].getLocalBounds();
                tableTx[i-1].setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
            }
        }
    } else if (level == 2) {
        for (int i = 1; i < 11; i++) {
            File* file = table->getFileByIndexSe(std::to_string(i));
            if (file == nullptr) {
                tableTx[i-1].setString(std::to_string(i) + " - Sin Puntaje");
                sf::FloatRect bounds = tableTx[i-1].getLocalBounds();
                tableTx[i-1].setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
            } else {
                tableTx[i-1].setString(file->getId() + " - " + file->getName()+ ": " + file->getScore() );
                sf::FloatRect bounds = tableTx[i-1].getLocalBounds();
                tableTx[i-1].setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
            }
        }
    } else if (level == 3) {
        for (int i = 1; i < 11; i++) {
            File* file = table->getFileByIndexTh(std::to_string(i));
            if (file == nullptr) {
                tableTx[i-1].setString(std::to_string(i) + " - Sin Puntaje");
                sf::FloatRect bounds = tableTx[i-1].getLocalBounds();
                tableTx[i-1].setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
            } else {
                tableTx[i-1].setString(file->getId() + " - " + file->getName()+ ": " + file->getScore() );
                sf::FloatRect bounds = tableTx[i-1].getLocalBounds();
                tableTx[i-1].setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
            }
        }
    }
    currentTx.setString("Actual: " + std::to_string(*score));
    sf::FloatRect bounds = currentTx.getLocalBounds();
    currentTx.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
} // En proceso --------------------------
void HUD::drawBackGround() {
    window->draw(BGMain);
}
void HUD::drawLevel() {
    if (*currentScreen == 0) { // Options
        window->draw(optionesShape);
        window->draw(playButton);
        window->draw(optionsButton);
        window->draw(quitButton);
        window->draw(playTx);
        window->draw(optionsTx);
        window->draw(closeTx);
        window->draw(candyTx);
        window->draw(filter);
    } else if (*currentScreen == 1) { // Main menu
        window->draw(optionesShape);
        window->draw(playButton);
        window->draw(optionsButton);
        window->draw(quitButton);
        window->draw(playTx);
        window->draw(optionsTx);
        window->draw(closeTx);
        window->draw(candyTx);
    } else if (*currentScreen == 2) { // Game
        window->draw(levelShape);
        window->draw(scoreObjetiveShape);
        window->draw(scoreAndMovesShape);
        window->draw(moveTx);
        window->draw(movesTx);
        window->draw(scoreTx);
        window->draw(scoresTx);
        window->draw(scoreObjetiveTx);
        window->draw(scoreObjetiveNumTx);
        window->draw(currentLevelTx);
    } else if (*currentScreen == 3) { // Game over
        window->draw(filter);
        window->draw(continueButton);
        window->draw(backButton);
        window->draw(levelShape);
        window->draw(scoreAndMovesShape);
        window->draw(scoreTx);
        window->draw(scoresTx);
        window->draw(scoreObjetiveTx);
        window->draw(scoreObjetiveNumTx);
        window->draw(currentLevelTx);
        window->draw(continueTx);
        window->draw(backTx);
        window->draw(titleTableTx);
        window->draw(currentTx);
        for (int i = 0; i < 10; i++) {
            window->draw(tableTx[i]);
        }
        if (level == 1 && table->getFileByIndexFi("10") != nullptr) {
            if (table->getFileByIndexFi("10")->getScoreToCompare() <= *score) {
                window->draw(saveTx);
            }
        } else if (level == 2 && table->getFileByIndexSe("10") != nullptr) {
            if (table->getFileByIndexSe("10")->getScoreToCompare() <= *score) {
                window->draw(saveTx);
            }
        } else if (level == 3 && table->getFileByIndexTh("10") != nullptr) {
            if (table->getFileByIndexTh("10")->getScoreToCompare() <= *score) {
                window->draw(saveTx);
            }
        } else {
            window->draw(saveTx);
        }
    }
}