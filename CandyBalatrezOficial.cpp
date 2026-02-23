#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

class Gems {
private:
    int id;
    bool isSelected;

protected:
    int coords[2];
    sf::Vector2f position;
    sf::Texture texture;
    sf::CircleShape hitBox;

public:
    Gems() {
        id = 0;
        coords[0] = 0; coords[1] = 0;
        hitBox.setRadius(19.0f);
        hitBox.setPosition(145.f, 45.f);
        if (!texture.loadFromFile("assets/textures/Chip.png")) {
            texture.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura Chip.png\n";
        }
        hitBox.setTexture(&texture);
        hitBox.setOutlineThickness(2.f);
        isSelected = false;
    }
    Gems(int newId, int x, int y, sf::Vector2f newPosition) : id(newId) {
        coords[0] = x; coords[1] = y;
        hitBox.setRadius(19.0f);
        hitBox.setPosition(newPosition);
        position = newPosition;
        changeTexture();
        hitBox.setOutlineThickness(2.f);
        isSelected = false;
    }
    ~Gems() {}

    virtual void setId(int newId) {
        id = newId;
        changeTexture();
    }
    void setX(int x) { coords[0] = x; }
    void setY(int y) { coords[1] = y; }
    void setPosition(sf::Vector2f newPosition) {
        hitBox.setPosition(newPosition);
        position = newPosition;
    }
    void setCoords(int x, int y) {
        coords[0] = x;
        coords[1] = y;
    }

    virtual int getId() { return id; }
    int getX() { return coords[0]; }
    int getY() { return coords[1]; }
    sf::Vector2f getPosition() { return position; }
    virtual sf::CircleShape getHitBox() { return hitBox; }

    virtual void mouseIsOn() {
        if (!isSelected) {
            hitBox.setOutlineColor(sf::Color::Yellow);
        }
    }
    virtual void mouseIsNotOn() {
        if (!isSelected) {
            hitBox.setOutlineColor(sf::Color::Transparent);
        }
    }
    virtual void select() {
        isSelected = true;
        hitBox.setFillColor(sf::Color(152, 250, 140));
    }
    virtual void deselect() {
        hitBox.setFillColor(sf::Color::White);
        isSelected = false;
    }
    void changeTexture() {
        switch (id) {
        case 0:
            if (!texture.loadFromFile("assets/textures/Chip.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura Chip.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        case 1:
            if (!texture.loadFromFile("assets/textures/ChipOne.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura ChipOne.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        case 2:
            if (!texture.loadFromFile("assets/textures/ChipTwo.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura ChipTwo.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        case 3:
            if (!texture.loadFromFile("assets/textures/ChipThree.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura ChipThree.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        case 4:
            if (!texture.loadFromFile("assets/textures/ChipFour.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura ChipFour.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        case 5:
            if (!texture.loadFromFile("assets/textures/ChipFive.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura ChipFive.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        default:
            texture.loadFromFile("assets/textures/thumbnail.png");
            hitBox.setTexture(&texture);
            break;
        }
    }
};

class Block : public Gems {
private:
    static const int id = -1;
    static const bool isSelected;

public:
    Block() {
        coords[0] = 0; coords[1] = 0;
        hitBox.setRadius(19.0f);
        hitBox.setPosition(145.f, 45.f);
        hitBox.setOutlineThickness(2.f);
        if (!texture.loadFromFile("assets/textures/Block.png")) {
            texture.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura Block.png\n";
        }
        hitBox.setTexture(&texture);
    }
    Block(int x, int y, sf::Vector2f newPosition) {
        coords[0] = x; coords[1] = y;
        hitBox.setRadius(19.0f);
        hitBox.setPosition(newPosition);
        hitBox.setOutlineThickness(2.f);
        position = newPosition;
        if (!texture.loadFromFile("assets/textures/Block.png")) {
            texture.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura Block.png\n";
        }
        hitBox.setTexture(&texture);
    }
    ~Block() {}

    int getId() override { return id; }
    void setId(int newId) override {
        std::cout << "(St) Esta accion no esta permitida\n";
    }
    sf::CircleShape getHitBox() override { return hitBox; }

    void mouseIsOn() override {
        hitBox.setOutlineColor(sf::Color::Red);
    }
    void mouseIsNotOn() override {
        hitBox.setOutlineColor(sf::Color::Transparent);
    }
    void select() override {
        std::cout << "(Se) Esta accion no es posible\n";
    }
    void deselect() override {
        std::cout << "(De) Esta accion no es posible\n";
    }
};

template <class T>
class Board {
private:
    T* game;
    sf::RenderWindow* window;
    Gems*** board;
    bool isOneSelect;
    bool isLevelComplete;
    int movesAllowed;
    int GO[2];
    int GT[2];
    int score;
    int scoreObjetive;

public:
    Board() {
        initialize();
    }
    ~Board() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                delete board[i][j];
            }
            board[i] = nullptr;
        }
        board = nullptr;
    }
    void initialize() {
        game = nullptr;
        window = nullptr;
        isLevelComplete = false;
        sf::Vector2f position(10.f, -23.f); // 77.f, -23.f
        board = new Gems * *[8];
        for (int i = 0; i < 8; i++) {
            board[i] = new Gems * [8];
            position.y = 20.f; // 23.f
            position.x += 60.f; // 68.f
            for (int j = 0; j < 8; j++) {
                position.y += 60.f; // 68.f
                board[i][j] = new Gems(getRandId(i, j), i, j, position);
            }
        }
        for (int i = 0; i < 2; i++) {
            GO[i] = 0;
            GT[i] = 0;
        }
        isOneSelect = false;
        movesAllowed = 5;
        score = 0;
        scoreObjetive = 0;
    }

    void setRenderWindow(sf::RenderWindow* newRenderWindow) { window = newRenderWindow; }
    void setGame(T newGame) { game = newGame; }

    int getMovesAllowed() const { return movesAllowed; }
    int getScore() const { return score; }
    bool getIsLevelComplete() const { return isLevelComplete; }

    void levelOne() {
        isLevelComplete = false;
        sf::Vector2f position(10.f, -23.f); // 77.f, -23.f
        for (int i = 0; i < 8; i++) {
            position.y = 20.f; // 23.f
            position.x += 60.f; // 68.f
            for (int j = 0; j < 8; j++) {
                position.y += 60.f; // 68.f
                if (i == 4 && j == 4) {
                    board[i][j] = new Block(i, j, position);
                } else {
                    board[i][j] = new Gems(getRandId(i, j), i, j, position);
                }
            }
        }
        for (int i = 0; i < 2; i++) {
            GO[i] = 0;
            GT[i] = 0;
        }
        isOneSelect = false;
        movesAllowed = 5;
        score = 0;
        scoreObjetive = 1000;
    }
    void levelTwo() {
        isLevelComplete = false;
        sf::Vector2f position(10.f, -23.f); // 77.f, -23.f
        for (int i = 0; i < 8; i++) {
            position.y = 20.f; // 23.f
            position.x += 60.f; // 68.f
            for (int j = 0; j < 8; j++) {
                position.y += 60.f; // 68.f
                if (i == 4 && (j == 3 || j == 5)) {
                    board[i][j] = new Block(i, j, position);
                } else {
                    board[i][j] = new Gems(getRandId(i, j), i, j, position);
                }
            }
        }
        for (int i = 0; i < 2; i++) {
            GO[i] = 0;
            GT[i] = 0;
        }
        isOneSelect = false;
        movesAllowed = 10;
        score = 0;
        scoreObjetive = 2000;
    }
    void levelThree() {
        isLevelComplete = false;
        sf::Vector2f position(10.f, -23.f); // 77.f, -23.f
        for (int i = 0; i < 8; i++) {
            position.y = 20.f; // 23.f
            position.x += 60.f; // 68.f
            for (int j = 0; j < 8; j++) {
                position.y += 60.f; // 68.f
                board[i][j] = new Gems(getRandId(i, j), i, j, position);
            }
        }
        for (int i = 0; i < 2; i++) {
            GO[i] = 0;
            GT[i] = 0;
        }
        isOneSelect = false;
        movesAllowed = 15;
        score = 0;
        scoreObjetive = 5000;
    }
    int getRandId(int i, int j) {
        int id;
        do {
            id = (rand() % 5) + 1;
        } while ((j >= 2 && id == board[i][j - 2]->getId()) || (i >= 2 && id == board[i - 2][j]->getId()));
        return id;
    }
    void printBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                window->draw(board[i][j]->getHitBox());
            }
        }
    }
    void ifMouseIsOn(sf::Vector2f mousePosition) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j]->getHitBox();
                if (board[i][j]->getHitBox().getGlobalBounds().contains(mousePosition)) {
                    board[i][j]->mouseIsOn();
                } else {
                    board[i][j]->mouseIsNotOn();
                }
            }
        }
    }
    void verifyWin() {
        if (score >= scoreObjetive) isLevelComplete = true;
    }
    void select(sf::Vector2f mousePosition) {
        if (movesAllowed == 0) {
            std::cout << "No quedan movimientos" << std::endl;
            return;
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j]->getHitBox().getGlobalBounds().contains(mousePosition) && board[i][j]->getId() == -1) {
                    return;
                } else if (board[i][j]->getHitBox().getGlobalBounds().contains(mousePosition) && !isOneSelect) {
                    board[i][j]->select();
                    isOneSelect = true;
                    GO[0] = i;
                    GO[1] = j;
                } else if (board[i][j]->getHitBox().getGlobalBounds().contains(mousePosition) && isOneSelect) {
                    board[i][j]->select();
                    GT[0] = i;
                    GT[1] = j;
                    verifyChange();
                    return;
                }
            }
        }
    }
    void verifyChange() {
        int X = board[GO[0]][GO[1]]->getX() - board[GT[0]][GT[1]]->getX();
        int Y = board[GO[0]][GO[1]]->getY() - board[GT[0]][GT[1]]->getY();
        bool isX = (X == 1 || X == -1);
        bool isY = (Y == 1 || Y == -1);
        if ((isX && Y == 0) || (isY && X == 0)) {
            changeGemsPositions();
            if (findMacht()) {
                movesAllowed--;
                deselectAll();
                macht();
                return;
            }
            changeGemsPositions();
            deselectAll();
            verifyWin();
            return;
        } else {
            deselectAll();
            verifyWin();
            return;
        }
    }
    void changeGemsPositions() {
        int GemId = board[GO[0]][GO[1]]->getId();
        board[GO[0]][GO[1]]->setId(board[GT[0]][GT[1]]->getId());
        board[GT[0]][GT[1]]->setId(GemId);
        animateGemSwap(GO[0], GO[1], GT[0], GT[1]);
    }
    void animateGemSwap(int x1, int y1, int x2, int y2) {
        if (window == nullptr) return;

        const float duration = 0.25f; // segundos
        sf::Clock clock;
        sf::Vector2f startPos1 = board[x1][y1]->getPosition();
        sf::Vector2f startPos2 = board[x2][y2]->getPosition();

        // Animar hasta duration; procesar eventos y dibujar cada frame
        while (true) {
            float elapsed = clock.getElapsedTime().asSeconds();
            float progress = elapsed / duration;
            if (progress > 1.0f) progress = 1.0f;

            board[x1][y1]->setPosition(lerp(startPos1, startPos2, progress));
            board[x2][y2]->setPosition(lerp(startPos2, startPos1, progress));

            // Procesar eventos para evitar que la ventana deje de responder
            sf::Event ev;
            while (window->pollEvent(ev)) {
                if (ev.type == sf::Event::Closed) window->close();
            }

            // Dibujar solo el tablero (mínimo), puedes ajustar para dibujar UI si lo necesitas
            game->drawScreen();

            if (progress >= 1.0f) break;

            // Pequeña espera para limitar CPU (aprox 60 FPS)
            sf::sleep(sf::milliseconds(16));
        }

        // Asegurar posiciones exactas finales
        board[x1][y1]->setPosition(startPos2);
        board[x2][y2]->setPosition(startPos1);
    }
    sf::Vector2f lerp(sf::Vector2f start, sf::Vector2f end, float t) {
        return start + t * (end - start);
    }
    void changeByIndex(int i, int j, int k, int h) {
        int GemId = board[i][j]->getId();
        board[i][j]->setId(board[k][h]->getId());
        board[k][h]->setId(GemId);
    }
    void deselectAll() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j]->deselect();
            }
        }
        isOneSelect = false;
        for (int i = 0; i < 2; i++) {
            GO[i] = 0;
            GT[i] = 0;
        }
    }
    bool findMacht() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (j < 6) {
                    if (board[j][i]->getId() == board[j + 1][i]->getId() && board[j][i]->getId() == board[j + 2][i]->getId()) {
                        return true;
                    }
                }
                if (i < 6) {
                    if (board[j][i]->getId() == board[j][i + 1]->getId() && board[j][i]->getId() == board[j][i + 2]->getId()) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    void deleteGems() {
        int countJ, countI;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                countJ, countI = 0;
                if (j < 7) {
                    deleteJ(i, j);
                }
                if (i < 7) {
                    deleteI(i, j);
                }
            }
        }
    }
    void deleteJ(int i, int j) {
        int count = 0;
        for (int k = j + 1; k < 8 && board[j][i]->getId() == board[k][i]->getId(); k++) {
            count++;
        }
        if (1 < count) {
            for (int k = j; k <= j + count; k++) {
                if (board[k][i]->getId() != -1) {
                    board[k][i]->setId(0);
                    score += 10;
                }
            }
        }
    }
    void deleteI(int i, int j) {
        int count = 0;
        for (int k = i + 1; k < 8 && board[j][i]->getId() == board[j][k]->getId(); k++) {
            count++;
        }
        if (1 < count) {
            for (int h = i; h <= i + count; h++) {
                if (board[j][h]->getId() != -1) {
                    board[j][h]->setId(0);
                    score += 10;
                }
            }
        }
    }
    void macht() {
        while (findMacht()) {
            deleteGems();
            while (findZeros()) {
                gravity();
            }
        }
    }
    bool findZeros() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j]->getId() == 0) {
                    return true;
                }
            }
        }
        return false;
    }
    void gravity() {
        int count, move;
        for (int i = 0; i < 8; i++) {
            if (board[i][0]->getId() == 0) {
                board[i][0]->setId(getRandId(0, i));
            }
        }
        for (int j = 0; j < 8; j++) {
            for (int i = 7; i > -1; i--) {
                count = 0, move = 0;
                for (int k = i; k > 0 && board[j + move][k]->getId() == 0; k--) {
                    while (k != 0 && board[j + move][k - 1]->getId() == -1 && j > 4) {
                        move == move + 1;
                    }
                    while (k != 0 && board[j + move][k - 1]->getId() == -1 && j <= 4) {
                        move == move - 1;
                    }
                    count++;
                }
                changeByIndex(j, i, j + move, i - count);
            }
        }
    }
};

class Game {
private:
    sf::RenderWindow& window;
    Board<Game> board;
    sf::Font font;
    sf::Text playText;
    sf::Text closeText;
    sf::Text optionsText;
    sf::Text candyText;
    sf::Text movesText;
    sf::Text scoresText;
    sf::Text moveText;
    sf::Text scoreText;
    sf::Text gameFinish;
    sf::Sprite BGMain;
    sf::Sprite BGLoad;
    sf::Texture BGLoadT;
    sf::Texture optionesTexture;
    sf::Texture scoreTexture;
    sf::Texture buttonTexture;
    sf::Texture* BGMainT;
    sf::RectangleShape filter;
    sf::RectangleShape playButton;
    sf::RectangleShape optionsButton;
    sf::RectangleShape quitButton;
    sf::RectangleShape optionesShape;
    sf::RectangleShape scoreAndMovesShape;
    sf::Vector2i mousePosInt;
    sf::Vector2f mousePosition;
    sf::Clock BGClock;
    int currentScreen;
    int currentLevel;
    int frame;

public:
    Game(sf::RenderWindow& newWindow) : window(newWindow) {
        loadTextures();
        initialize();
        currentScreen = 1;
        currentLevel = 1;
    }
    Game(sf::RenderWindow& newWindow, int newCurrentScreen) : window(newWindow) {
        loadTextures();
        initialize();
        currentScreen = newCurrentScreen;
        currentLevel = 1;
    }
    ~Game() {}
    void initialize() {
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

        scoreAndMovesShape.setSize(sf::Vector2f(300.f, 300.f));
        scoreAndMovesShape.setFillColor(sf::Color(79, 99, 103));
        scoreAndMovesShape.setOrigin(150.f, 50.f);
        scoreAndMovesShape.setPosition(600.f, 560.f);
        scoreAndMovesShape.setTexture(&scoreTexture);

        filter.setSize(sf::Vector2f(800, 600));
        filter.setFillColor(sf::Color(0, 0, 0, 160));
    }
    void loadTextures() {
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
        setBackgrounds();
        setTexts();
    }
    void setBackgrounds() {
        BGMainT = new sf::Texture[300];
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
        loadText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        sf::Vector2u textureSize1 = BGLoadT.getSize();
        sf::Vector2u windowSize = window.getSize(); \
            BGLoad.setScale(float(windowSize.x) / textureSize1.x, float(windowSize.y) / textureSize1.y);
        BGLoad.setTexture(BGLoadT);
        for (int i = 0; i < 300; i++) {
            loadString = "Cargando " + std::to_string((i * 100) / 300) + "%";
            loadText.setString(loadString);
            if (i < 10) {
                frame = "00" + std::to_string(i);
            } else if (i < 100) {
                frame = "0" + std::to_string(i);
            } else {
                frame = std::to_string(i);
            }
            BGMainT[i].loadFromFile("assets/frames/gbmframes_" + frame + ".jpg");
            window.clear();
            window.draw(BGLoad);
            window.draw(loadText);
            window.display();
        }
        sf::Vector2u textureSize2 = BGMainT[0].getSize();
        BGMain.setScale(float(windowSize.x) / textureSize2.x, float(windowSize.y) / textureSize2.y);
    }
    void setTexts() {
    playText.setString("PLAY");
        playText.setFont(font);
        playText.setCharacterSize(50);
        playText.setFillColor(sf::Color::White);
        playText.setOutlineThickness(1.0f);
        playText.setOutlineColor(sf::Color::Black);
        sf::FloatRect bounds = playText.getLocalBounds();
        playText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        playText.setPosition(sf::Vector2f(230.f, 478.f));
        playText.setStyle(sf::Text::Bold);

        optionsText.setFont(font);
        optionsText.setString("OPCIONES");
        optionsText.setCharacterSize(40);
        optionsText.setFillColor(sf::Color::White);
        optionsText.setOutlineThickness(1.0f);
        optionsText.setOutlineColor(sf::Color::Black);
        bounds = optionsText.getLocalBounds();
        optionsText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        optionsText.setPosition(sf::Vector2f(398.f, 478.f));
        optionsText.setStyle(sf::Text::Bold);

        closeText.setFont(font);
        closeText.setString("CERRAR");
        closeText.setCharacterSize(50);
        closeText.setFillColor(sf::Color::White);
        closeText.setOutlineThickness(1.0f);
        closeText.setOutlineColor(sf::Color::Black);
        bounds = closeText.getLocalBounds();
        closeText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        closeText.setPosition(sf::Vector2f(575.f, 478.f));
        closeText.setStyle(sf::Text::Bold);

        candyText.setFont(font);
        candyText.setString("CANDY");
        candyText.setCharacterSize(100);
        candyText.setFillColor(sf::Color(242, 242, 242));
        candyText.setOutlineThickness(2.0f);
        candyText.setOutlineColor(sf::Color::Black);
        bounds = candyText.getLocalBounds();
        candyText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        candyText.setPosition(sf::Vector2f(400.f, 100.f));
        candyText.setStyle(sf::Text::Bold | sf::Text::Italic);

        scoresText.setFont(font);
        scoresText.setString("0");
        scoresText.setCharacterSize(50);
        scoresText.setOutlineThickness(2.f);
        scoresText.setFillColor(sf::Color(0, 156, 253));
        scoresText.setOutlineColor(sf::Color::Black);
        bounds = scoresText.getLocalBounds();
        scoresText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        scoresText.setPosition(sf::Vector2f(669.5f, 256.0f));
        scoresText.setStyle(sf::Text::Bold);

        scoreText.setFont(font);
        scoreText.setString("Puntaje");
        scoreText.setCharacterSize(40);
        scoreText.setOutlineThickness(2.f);
        scoreText.setFillColor(sf::Color(253, 160, 0));
        scoreText.setOutlineColor(sf::Color::Black);
        bounds = scoreText.getLocalBounds();
        scoreText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        scoreText.setPosition(sf::Vector2f(669.5f, 206.0f));
        scoreText.setStyle(sf::Text::Bold);

        movesText.setFont(font);
        movesText.setString("0");
        movesText.setCharacterSize(50);
        movesText.setOutlineThickness(2.f);
        movesText.setFillColor(sf::Color(0, 156, 253));
        movesText.setOutlineColor(sf::Color::Black);
        bounds = movesText.getLocalBounds();
        movesText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        movesText.setPosition(sf::Vector2f(669.5f, 376.0f));
        movesText.setStyle(sf::Text::Bold);

        moveText.setFont(font);
        moveText.setString("Jugadas");
        moveText.setCharacterSize(40);
        moveText.setOutlineThickness(2.f);
        moveText.setFillColor(sf::Color(253, 160, 0));
        moveText.setOutlineColor(sf::Color::Black);
        bounds = moveText.getLocalBounds();
        moveText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        moveText.setPosition(sf::Vector2f(669.0f, 324.0f));
        moveText.setStyle(sf::Text::Bold);

        gameFinish.setFont(font);
        gameFinish.setString("Nivel terminado");
        gameFinish.setCharacterSize(50);
        gameFinish.setOutlineThickness(2.f);
        gameFinish.setFillColor(sf::Color(0, 156, 253));
        gameFinish.setOutlineColor(sf::Color::Black);
        bounds = gameFinish.getLocalBounds();
        gameFinish.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        gameFinish.setPosition(sf::Vector2f(400.f, 216.0f));
        gameFinish.setStyle(sf::Text::Bold | sf::Text::Italic);
    }
    sf::RenderWindow& getRenderWindow() {
        return window;
    }

    void run(Game* currentGame) {
        board.setRenderWindow(&window);
        board.setGame(*currentGame);
        window.setFramerateLimit(60);
        while (window.isOpen()) {
            mousePosInt = sf::Mouse::getPosition(window);
            mousePosition.x = static_cast<float>(mousePosInt.x);
            mousePosition.y = static_cast<float>(mousePosInt.y);

            if (currentScreen == 0) {
                loadBGFrame(20.0f);
                optionsScreen();
            } else if (currentScreen == 1) {
                loadBGFrame(30.0f);
                mainMenuScreen();
            } else if (currentScreen == 2) {
                loadBGFrame(30.0f);
                gameScreen();
            } else if (currentScreen == 3) {
                loadBGFrame(15.0f);
                gameOverScreen();
            }

            drawScreen();
        }
    }
    void loadBGFrame(float GBFps) {
        if (BGClock.getElapsedTime().asSeconds() > 1.0f / GBFps) { // 30 FPS normalmente
            frame = (frame + 1) % 300;
            BGMain.setTexture(BGMainT[frame]);
            BGClock.restart();
        }
    }
    void optionsScreen() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if ((event.type == sf::Event::Closed)) {
                window.close();
                printf("Gracias por jugar");
            } else if (event.mouseButton.button == sf::Keyboard::Escape) {
                currentScreen = 1;
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (playButton.getGlobalBounds().contains(mousePosition)) {

                }
            }
        }
    }
    void mainMenuScreen() {
        sf::Event event;

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
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                printf("Gracias por jugar");
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (playButton.getGlobalBounds().contains(mousePosition)) {
                    currentScreen = 2;
                    if (currentLevel == 1) {
                        board.levelOne();
                    } else if (currentLevel == 2) {
                        board.levelTwo();
                    } else if (currentLevel == 3) {
                        board.levelThree();
                    }
                } else if (optionsButton.getGlobalBounds().contains(mousePosition)) {
                    currentScreen = 0;
                } else if (quitButton.getGlobalBounds().contains(mousePosition)) {
                    window.close();
                    printf("Gracias por jugar");
                }
            }
        }
    }
    void gameScreen() {
        if (board.getMovesAllowed() == 0) {
            currentScreen = 3;
        }
        sf::Event event;
        std::string score = std::to_string(board.getScore());
        std::string moves = std::to_string(board.getMovesAllowed());

        scoresText.setString(score);
        movesText.setString(moves);
        sf::FloatRect bounds = scoresText.getLocalBounds();
        scoresText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        bounds = movesText.getLocalBounds();
        movesText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        scoreAndMovesShape.setPosition(670.0f, 300.0f);
        scoresText.setPosition(sf::Vector2f(669.5f, 256.0f));

        board.ifMouseIsOn(mousePosition);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                currentScreen = 1;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                board.select(mousePosition);
            }
        }
    }
    void gameOverScreen() {
        sf::Event event;
        if (board.getIsLevelComplete() && currentLevel == 1) {
            currentLevel = 2;
        } else if (board.getIsLevelComplete() && currentLevel == 2) {
            currentLevel = 3;
        } else {
            currentLevel = 1;
        }

        scoresText.setString(std::to_string(board.getScore()));
        sf::FloatRect bounds = scoresText.getLocalBounds();
        scoresText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        scoreAndMovesShape.setPosition(400.0f, 300.0f);
        scoresText.setPosition(sf::Vector2f(400.f, 256.0f));

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                currentScreen = 1;
            }
        }
    }
    void drawScreen() {
        window.clear();
        window.draw(BGMain);

        if (currentScreen == 0) { // Options
            window.draw(optionesShape);
            window.draw(playButton);
            window.draw(optionsButton);
            window.draw(quitButton);
            window.draw(playText);
            window.draw(optionsText);
            window.draw(closeText);
            window.draw(candyText);
            window.draw(filter);
        } else if (currentScreen == 1) { // Main menu
            window.draw(optionesShape);
            window.draw(playButton);
            window.draw(optionsButton);
            window.draw(quitButton);
            window.draw(playText);
            window.draw(optionsText);
            window.draw(closeText);
            window.draw(candyText);
        } else if (currentScreen == 2) { // Game
            board.printBoard();
            window.draw(scoreAndMovesShape);
            window.draw(movesText);
            window.draw(scoresText);
            window.draw(moveText);
            window.draw(scoreText);
        } else if (currentScreen == 3) { // Game over
            board.printBoard();
            window.draw(filter);
            window.draw(scoreAndMovesShape);
            window.draw(scoresText);
            window.draw(gameFinish);
        }

        window.display();
    }
};

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Candy Balatrez");
    Game gameOne(window);
    gameOne.run(&gameOne);
    return 0;
}