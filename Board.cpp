#include "Board.h"

Board::Board() {
    initialize();
}
Board::~Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete board[i][j];
        }
        board[i] = nullptr;
    }
    table = nullptr;
    board = nullptr;
    hud = nullptr;
    window = nullptr;
}
void Board::initialize() {
    sf::Vector2f position(0.f, 0.f); // 10.f, -23.f
    board = new Gems **[8];
    for (int i = 0; i < 8; i++) {
        board[i] = new Gems * [8];
        position.y = 20.f; // 23.f
        position.x += 60.f; // 68.f
        for (int j = 0; j < 8; j++) {
            position.y += 60.f; // 68.f
            board[i][j] = new Gems(getRandId(i, j), i, j, position);
        }
    }
    GO[0] = GO[1] = GT[0] = GT[1] = 0;
    window = nullptr;
    isOneSelect = false;
    movesAllowed = 20;
    score = 0;
    scoreObjetive = 0;
}
bool Board::levelLoad(std::string data) {
    // Formato esperado: <level>.<gems>,<moves>,<score>,<scoreObjetive>
    if (data.empty()) return true;

    size_t p1 = data.find(',');
    if (p1 == std::string::npos) return true;
    size_t p2 = data.find(',', p1 + 1);
    if (p2 == std::string::npos) return true;
    size_t p3 = data.find(',', p2 + 1);
    if (p3 == std::string::npos) return true;
    size_t p4 = data.find(',', p3 + 1);
    if (p4 == std::string::npos) return true;

    std::string gemsField = data.substr(0, p1);
    std::string movesStr  = data.substr(p1 + 1, p2 - p1 - 1);
    std::string scoreStr  = data.substr(p2 + 1, p3 - p2 - 1);
    std::string objStr    = data.substr(p3 + 1, p4 - p3 - 1);

    size_t dot = gemsField.find('.');
    if (dot != std::string::npos && dot + 1 < gemsField.size()) {
        gemsField = gemsField.substr(dot + 1);
    }

    size_t idx = 0;
    sf::Vector2f position(25.f, 0.f); // 25.f, 0.f
    for (int x = 0; x < 8; ++x) {
        position.y = 65.f; // 65.f
        position.x += 60.f; // 60.f
        for (int y = 0; y < 8; ++y) {
            position.y += 60.f; // 60.f

            char c = gemsField[idx];
            if (c == 'X') {
                board[x][y] = new Block(x, y, position);
            } else if (c == 'A') {
                board[x][y] = new Bombs(1, getRandId(x, y), x, y, position);
            } else if (c == 'B') {
                board[x][y] = new Bombs(2, getRandId(x, y), x, y, position);
            } else if (c == 'C') {
                board[x][y] = new Bombs(3, getRandId(x, y), x, y, position);
            } else {
                board[x][y] = new Gems(std::stoi(gemsField.substr(idx, 1)), x, y, position);
            }
            idx++;
        }
    }

    GO[0] = GO[1] = GT[0] = GT[1] = 0;
    isOneSelect = false;

    try {
        movesAllowed = std::stoi(movesStr);
        score = std::stoi(scoreStr);
        scoreObjetive = std::stoi(objStr);
    } catch (const std::exception&) {
        return true;
    }

    return false;
}

void Board::saveScore(int level) {
    if (level == 1) {
        table->addToFirstOrdererByScore(new File("1", "Dom", std::to_string(score)));
    } else if (level == 2) {
        table->addToSecondOrdererByScore(new File("1", "Dom", std::to_string(score)));
    } else {
        table->addToThirdOrdererByScore(new File("1", "Dom", std::to_string(score)));
    }
}
void Board::saveBoard(int level) {
    std::string gems = "";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->getId() == -1) gems += "X";
            else if (board[i][j]->getId() == -2) {

                if (board[i][j]->getType() == 1) gems += "A";
                else if (board[i][j]->getType() == 2) gems += "B";
                else gems += "C";

            }
            else gems += std::to_string(board[i][j]->getId());
        }
    }
    try {
        std::ofstream outFile("level.csv");
        if (outFile.is_open()) {
            outFile << level << "." << gems << "," << movesAllowed << "," << score << "," << scoreObjetive << ",|";
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

void Board::setHUD(HUD* newHUD) {
    hud = newHUD;
}
void Board::setRenderWindow(sf::RenderWindow* newRenderWindow) { window = newRenderWindow; }
void Board::setTable(Table* newTable) { table = newTable; }

int Board::getMovesAllowed() const { return movesAllowed; }
int Board::getScore() const { return score; }
int Board::getScoreObjetive() const { return scoreObjetive; }
bool Board::getIsLevelComplete() const { return score >= scoreObjetive; }
int* Board::getScorePTR() { return &score;}

void Board::levelOne() {
    sf::Vector2f position(25.f, 0.f); // 25.f, 0.f
    for (int i = 0; i < 8; i++) {
        position.y = 65.f; // 65.f
        position.x += 60.f; // 60.f
        for (int j = 0; j < 8; j++) {
            position.y += 60.f; // 60.f
            board[i][j] = new Gems(getRandId(i, j), i, j, position);
        }
    }
    score = GO[0] = GO[1] = GT[0] = GT[1] = 0;
    isOneSelect = false;
    movesAllowed = 3;
    scoreObjetive = 100;
}
void Board::levelTwo() {
    sf::Vector2f position(25.f, 0.f);
    for (int i = 0; i < 8; i++) {
        position.y = 65.f;
        position.x += 60.f;
        for (int j = 0; j < 8; j++) {
            position.y += 60.f;
            if (j == 3 && (i == 2 || i == 5)) {
                board[i][j] = new Block(i, j, position);
            } else {
                board[i][j] = new Gems(getRandId(i, j), i, j, position);
            }
        }
    }
    score = GO[0] = GO[1] = GT[0] = GT[1] = 0;
    isOneSelect = false;
    movesAllowed = 3;
    scoreObjetive = 100;
}
void Board::levelThree() {
    sf::Vector2f position(25.f, 0.f);
    for (int i = 0; i < 8; i++) {
        position.y = 65.f;
        position.x += 60.f;
        for (int j = 0; j < 8; j++) {
            position.y += 60.f;
            if (j == 3 && (i >= 2 && i < 6)) {
                board[i][j] = new Block(i, j, position);
            } else {
                board[i][j] = new Gems(getRandId(i, j), i, j, position);
            }
        }
    }
    score = GO[0] = GO[1] = GT[0] = GT[1] = 0;
    isOneSelect = false;
    movesAllowed = 3;
    scoreObjetive = 100;
}
int Board::getRandId(int i, int j) {
    int id;
    do {
        id = (rand() % 5) + 1;
    } while ((j >= 2 && id == board[i][j - 2]->getId()) || (i >= 2 && id == board[i - 2][j]->getId()));
    return id;
}
void Board::printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->getId() != 0) {
                window->draw(board[i][j]->getHitBox());
            }
        }
    }
}
void Board::ifMouseIsOn(sf::Vector2f mousePosition) {
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
void Board::select(sf::Vector2f mousePosition) {
    if (movesAllowed == 0) {
        std::cout << "No quedan movimientos" << std::endl;
        return;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->getHitBox().getGlobalBounds().contains(mousePosition) && board[i][j]->getId() == -1) {
                animateShake(i, j);
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
void Board::verifyChange() {
    int X = board[GO[0]][GO[1]]->getX() - board[GT[0]][GT[1]]->getX();
    int Y = board[GO[0]][GO[1]]->getY() - board[GT[0]][GT[1]]->getY();
    bool isX = (X == 1 || X == -1);
    bool isY = (Y == 1 || Y == -1);
    bool isBombSelected = board[GO[0]][GO[1]]->getType() != -1 || board[GT[0]][GT[1]]->getType() != -1;
    if ((isX && Y == 0) || (isY && X == 0)) {
        changeGemsPositions();
        if (findMacht() || isBombSelected) {
            movesAllowed--;
            hud->setMovesText(movesAllowed);
            deselectAll();
            macht();
        } else {
            changeGemsPositions();
            animateShakeTwoGems();
            deselectAll();
        }
    } else {
        if (!(GO[0] == GT[0] && GO[1] == GT[1])) {
            animateShakeTwoGems();
        }
        deselectAll();
    }
}
void Board::deleteGemAt(int x, int y) {
    if (board[x][y]->getType() != -1) {
        bombExplode(x, y, x, y);
    } else if (board[x][y]->getId() != 0 && board[x][y]->getId() != -1) {
        animateGemDisappearance(x, y);
        board[x][y]->setId(0);
        score += 10;
        hud->setScoreText();
    }
}
bool Board::isBombslefts() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[j][i]->getType() != -1) {
                return true;
            }
        }
    }
    return false;
}
void Board::explodeBombsLefts() {
    while (isBombslefts()) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[j][i]->getType() != -1) {
                    bombExplode(j, i, j, i);
                    macht();
                }
            }
        }
    }
}
void Board::bombExplode(int x1, int y1, int x2, int y2) {
    deselectAll();
    if (board[x1][y1]->getType() == 1) {
        if (x1 == x2 && y1 == y2) {
            board[x1][y1] = new Gems(0, x1, y1, board[x1][y1]->getPosition());
        } else {
            board[x1][y1] = new Gems(board[x2][y2]->getId(), x1, y1, board[x1][y1]->getPosition());
        }
        for (int h = 0; h < 8; h++) {
            if (x2 - h > -1) {
                deleteGemAt(x2 - h, y2);
            }
            if (x2 + h < 8) {
                deleteGemAt(x2 + h, y2);
            }
        }
    } else if (board[x1][y1]->getType() == 2) {
        if (x1 == x2 && y1 == y2) {
            board[x1][y1] = new Gems(0, x1, y1, board[x1][y1]->getPosition());
        } else {
            board[x1][y1] = new Gems(board[x2][y2]->getId(), x1, y1, board[x1][y1]->getPosition());
        }
        deleteGemAt(x2, y2);
        for (int h = 1; h < 8; h++) {
            if (y2 - h > -1) {
                deleteGemAt(x2, y2 - h);
            }
            if (y2 + h < 8) {
                deleteGemAt(x2, y2 + h);
            }
        }
        if (confirmIsColRellyEmpty(x2)) {
            fillCol(x2);
        }
    } else if (board[x1][y1]->getType() == 3) {
        if (x1 == x2 && y1 == y2) {
            board[x1][y1] = new Gems(0, x1, y1, board[x1][y1]->getPosition());
        } else {
            board[x1][y1] = new Gems(board[x2][y2]->getId(), x1, y1, board[x1][y1]->getPosition());
        }
        deleteGemAt(x2, y2);
        for (int h = 1; h < 8; h++) {
            if (y2 - h > -1) {
                deleteGemAt(x2, y2 - h);
            }
            if (y2 + h < 8) {
                deleteGemAt(x2, y2 + h);
            }
            if (x2 - h > -1) {
                deleteGemAt(x2 - h, y2);
            }
            if (x2 + h < 8) {
                deleteGemAt(x2 + h, y2);
            }
        }
        if (confirmIsColRellyEmpty(x2)) {
            fillCol(x2);
        }
    }
}
bool Board::confirmIsColRellyEmpty(int x) {
    for (int j = 0; j < 8; j++) {
        if (board[x][j]->getId() != 0) {
            if (board[x][j]->getId() == -1) continue;
            return false;
        }
    }
    return true;
}
void Board::fillCol(int x) {
    for (int j = 7; j >= 0; j--) {
        try {
            if (board[x][j]->getId() == -1) throw(1);
            else {
                board[x][j]->setId(getRandId(x, j));
                animateGemSwap(x, 0, x, j, 0.07f);
            }
        } catch(int e) {
            if (e == 1) {
                std::cerr << "Intento de modificacion de Bloque" << std::endl;
            }
        }
    }
}
void Board::animateShake(int x, int y) {
    try {
        if (window == nullptr) throw(1);
        else {
            const float duration = 0.18f;
            sf::Clock clock;
            sf::Vector2f startPos = board[x][y]->getPosition();
            while (true) {
                hud->loadBGFrame(20.0f);
                float elapsed = clock.getElapsedTime().asSeconds();
                float progress = elapsed / duration;
                if (progress > 1.0f) progress = 1.0f;
                float shakeOffset = 5.0f * sin(progress * 3.14f * 4); // Oscilación
                board[x][y]->setPosition(startPos + sf::Vector2f(shakeOffset, shakeOffset));
                sf::Event ev;
                while (window->pollEvent(ev)) {
                    if (ev.type == sf::Event::Closed) window->close();
                }
                window->clear();
                hud->drawBackGround();
                hud->drawLevel();
                printBoard();
                window->display();
                if (progress >= 1.0f) break;
                sf::sleep(sf::milliseconds(16));
            }
            board[x][y]->setPosition(startPos);
        }
    } catch(int i) {
        if (i == 1) {
            std::cerr << "Ventana no encontrada" << '\n';
            return;
        }
    }
}
void Board::animateShakeTwoGems() {
    try {
        if (window == nullptr) throw(1);
        else {
            const float duration = 0.2f;
            sf::Clock clock;
            sf::Vector2f startPosOne = board[GO[0]][GO[1]]->getPosition();
            sf::Vector2f startPosTwo = board[GT[0]][GT[1]]->getPosition();
            while (true) {
                hud->loadBGFrame(20.0f);
                float elapsed = clock.getElapsedTime().asSeconds();
                float progress = elapsed / duration;
                if (progress > 1.0f) progress = 1.0f;
                float shakeOffset = 5.0f * sin(progress * 3.14f * 4); // Oscilación
                board[GO[0]][GO[1]]->setPosition(startPosOne + sf::Vector2f(shakeOffset, shakeOffset));
                board[GT[0]][GT[1]]->setPosition(startPosTwo + sf::Vector2f(-shakeOffset, -shakeOffset));
                sf::Event ev;
                while (window->pollEvent(ev)) {
                    if (ev.type == sf::Event::Closed) window->close();
                }
                window->clear();
                hud->drawBackGround();
                hud->drawLevel();
                printBoard();
                window->display();
                if (progress >= 1.0f) break;
                sf::sleep(sf::milliseconds(16));
            }
            board[GO[0]][GO[1]]->setPosition(startPosOne);
            board[GT[0]][GT[1]]->setPosition(startPosTwo);
        }
    } catch(int i) {
        if (i == 1) {
            std::cerr << "Ventana no encontrada" << '\n';
            return;
        }
    }
}
void Board::animategemAppear(int x, int y) {
    try {
        if (window == nullptr) throw(1);
        else {
            const float duration = 0.07f;
            sf::Clock clock;
            while (true) {
                hud->loadBGFrame(20.0f);
                float elapsed = clock.getElapsedTime().asSeconds();
                float progress = elapsed / duration;
                if (progress > 1.0f) progress = 1.0f;
                board[x][y]->setFillColor(sf::Color(255, 255, 255, 255 * progress));
                sf::Event ev;
                while (window->pollEvent(ev)) {
                    if (ev.type == sf::Event::Closed) window->close();
                }
                window->clear();
                hud->drawBackGround();
                hud->drawLevel();
                printBoard();
                window->display();
                if (progress >= 1.0f) break;
                sf::sleep(sf::milliseconds(16));
            }
            board[x][y]->setFillColor(sf::Color(255, 255, 255, 255));
        }
    } catch(int i) {
        if (i == 1) {
            std::cerr << "Ventana no encontrada" << '\n';
            return;
        }
    }
}
void Board::animateGemDisappearance(int x, int y) {
    try {
        if (window == nullptr) throw(1);
        else {
            const float duration = 0.06f;
            sf::Clock clock;
            while (true) {
                hud->loadBGFrame(20.0f);
                float elapsed = clock.getElapsedTime().asSeconds();
                float progress = elapsed / duration;
                if (progress > 1.0f) progress = 1.0f;
                board[x][y]->setFillColor(sf::Color(255, 255, 255, 255 * (1 - progress)));
                sf::Event ev;
                while (window->pollEvent(ev)) {
                    if (ev.type == sf::Event::Closed) window->close();
                }
                window->clear();
                hud->drawBackGround();
                hud->drawLevel();
                printBoard();
                window->display();
                if (progress >= 1.0f) break;
                sf::sleep(sf::milliseconds(16));
            }
            board[x][y]->setFillColor(sf::Color(255, 255, 255, 255));
        }
    } catch(int i) {
        if (i == 1) {
            std::cerr << "Ventana no encontrada" << '\n';
            return;
        }
    }
}
void Board::animateGemSwap(int x1, int y1, int x2, int y2, float customDuration) {
    try {
        if (window == nullptr) throw(1);
        else {
            const float duration = 0.18f - customDuration;
            sf::Clock clock;
            sf::Vector2f startPosOne = board[x1][y1]->getPosition();
            sf::Vector2f startPosTwo = board[x2][y2]->getPosition();
            while (true) {
                hud->loadBGFrame(23.0f);
                float elapsed = clock.getElapsedTime().asSeconds();
                float progress = elapsed / duration;
                if (progress > 1.0f) progress = 1.0f;
                board[x1][y1]->setPosition(lerp(startPosOne, startPosTwo, progress));
                board[x2][y2]->setPosition(lerp(startPosTwo, startPosOne, progress));
                sf::Event ev;
                while (window->pollEvent(ev)) {
                    if (ev.type == sf::Event::Closed) window->close();
                }
                window->clear();
                hud->drawBackGround();
                hud->drawLevel();
                printBoard();
                window->display();
                if (progress >= 1.0f) break;
                sf::sleep(sf::milliseconds(16));
            }
            board[x1][y1]->setPosition(startPosOne);
            board[x2][y2]->setPosition(startPosTwo);
        }
    } catch(int i) {
        if (i == 1) {
            std::cerr << "Ventana no encontrada" << '\n';
            return;
        }
    }
}
void Board::animateGemFall(int x1, int y1, int x2, int y2) {
    try {
        if (window == nullptr) throw(1);
        else {
            const float duration = 0.07f;
            sf::Clock clock;
            sf::Vector2f startPosOne = board[x1][y1]->getPosition();
            sf::Vector2f startPosTwo = board[x2][y2]->getPosition();
            while (true) {
                hud->loadBGFrame(24.0f);
                float elapsed = clock.getElapsedTime().asSeconds();
                float progress = elapsed / duration;
                if (progress > 1.0f) progress = 1.0f;
                board[x1][y1]->setPosition(lerp(startPosOne, startPosTwo, progress));
                sf::Event ev;
                while (window->pollEvent(ev)) {
                    if (ev.type == sf::Event::Closed) window->close();
                }
                window->clear();
                hud->drawBackGround();
                hud->drawLevel();
                printBoard();
                window->display();
                if (progress >= 1.0f) break;
                sf::sleep(sf::milliseconds(16));
            }
            board[x1][y1]->setPosition(startPosOne);
        }
        
    } catch(int i) {
        if (i == 1) {
            std::cerr << "Ventana no encontrada" << '\n';
            return;
        }
    }
}
sf::Vector2f Board::lerp(sf::Vector2f start, sf::Vector2f end, float t) {
    return start + t * (end - start);
}
void Board::changeGemsPositions() {
    animateGemSwap(GT[0], GT[1], GO[0], GO[1], 0.07f);
    if (board[GT[0]][GT[1]]->getType() != -1) {
        bombExplode(GT[0], GT[1], GO[0], GO[1]);
    } else if (board[GO[0]][GO[1]]->getType() != -1) {
        bombExplode(GO[0], GO[1], GT[0], GT[1]);
    } else {
        int GemId = board[GO[0]][GO[1]]->getId();
        board[GO[0]][GO[1]]->setId(board[GT[0]][GT[1]]->getId());
        board[GT[0]][GT[1]]->setId(GemId);
    }
}
void Board::changeByIndex(int i, int j, int k, int h) {
    animateGemFall(k, h, i, j);
    if (board[i][j]->getType() != -1) {
        bombExplode(i, j, k, h);
    } else if (board[k][h]->getType() != -1) {
        bombExplode(k, h, i, j);
    } else {
        int GemId = board[i][j]->getId();
        board[i][j]->setId(board[k][h]->getId());
        board[k][h]->setId(GemId);
    }
}
void Board::deselectAll() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->getId() != -1) {
                board[i][j]->deselect();
            }
            board[i][j]->mouseIsNotOn();
        }
    }
    isOneSelect = false;
    for (int i = 0; i < 2; i++) {
        GO[i] = 0;
        GT[i] = 0;
    }
}
bool Board::findMacht() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (j < 6) {
                if (board[j][i]->getId() != -1 && board[j][i]->getId() == board[j + 1][i]->getId() && board[j][i]->getId() == board[j + 2][i]->getId()) {
                    deleteGems();
                    return true;
                }
            }
            if (i < 6) {
                if (board[j][i]->getId() != -1 && board[j][i]->getId() == board[j][i + 1]->getId() && board[j][i]->getId() == board[j][i + 2]->getId()) {
                    return true;
                }
            }
        }
    }
    return false;
}
void Board::deleteGems() {
    int countJ, countI;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            countJ, countI = 0;
            if (j < 7 && board[j][i]->getId() != -1 && board[j][i]->getId() != 0) {
                deleteJ(i, j);
            }
            if (i < 7 && board[j][i]->getId() != -1 && board[j][i]->getId() != 0) {
                deleteI(i, j);
            }
        }
    }
}
void Board::deleteJ(int i, int j) {
    int count = 0;
    for (int k = j + 1; k < 8 && board[j][i]->getId() == board[k][i]->getId(); k++) {
        count++;
    }
    if (board[j][i]->getId() != -1 && 1 < count) {
        if (count == 3) {
            animateGemDisappearance(j, i);
            board[j][i] = new Bombs(1, getRandId(i, j), j, i, board[j][i]->getPosition());
            j++;
            score += 20;
            hud->setScoreText();
        } else if (count > 3) {
            animateGemDisappearance(j, i);
            board[j][i] = new Bombs(3, getRandId(i, j), j, i, board[j][i]->getPosition());
            j++;
            score += 30;
            hud->setScoreText();
        }
        for (int k = j; k <= j + count; k++) {
            if (k < 8 && board[k][i]->getId() != -1) {
                deleteGemAt(k, i);
            }
        }
    }
}
void Board::deleteI(int i, int j) {
    int count = 0;
    for (int k = i + 1; k < 8 && board[j][i]->getId() == board[j][k]->getId(); k++) {
        count++;
    }
    if (board[j][i]->getId() != -1 && 1 < count) {
        for (int h = i; h <= i + count; h++) {
            if (h < 8 && board[j][h]->getId() != -1) {
                deleteGemAt(j, h);
            }
        }
        if (count == 3) {
            board[j][i + count] = new Bombs(2, getRandId(i + count, j), j, i + count, board[j][i + count]->getPosition());
            score += 20;
            hud->setScoreText();
        } else if (count > 3) {
            board[j][i + count] = new Bombs(3, getRandId(i + count, j), j, i + count, board[j][i + count]->getPosition());
            score += 30;
            hud->setScoreText();
        }
    }
}
void Board::macht() {
    while (findMacht()) {
        deleteGems();
        while (findZeros()) {
            gravity();
        }
    }
}
void Board::fillUp() {
    for (int i = 0; i < 8; i++) {
        if (board[i][0]->getId() == 0) {
            board[i][0]->setId(getRandId(0, i));
            animategemAppear(i, 0);
        }
    }
}
bool Board::findZeros() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->getId() == 0) {
                fillUp();
                return true;
            }
        }
    }
    return false;
}
void Board::gravity() {
    for (int j = 0; j < 4; j++) {
        for (int i = 7; i > -1; i--) {
            if (board[j][i]->getId() == 0) {
                fall(i, j);
            }
            if (board[7 - j][i]->getId() == 0) {
                fall(i, 7 - j);
            }
        }
    }
}
void Board::fall(int i, int j) {
    for (int k = i; k > 0; k--) {
        if (board[j][k]->getId() == -1) {
            return;
        } else if (board[j][k - 1]->getId() == -1) {
            if (j > 3) {
                changeByIndex(j, k, j + 1, k);
                fall(k, j + 1);
            } else {
                changeByIndex(j, k, j - 1, k);
                fall(k, j - 1);
            }
        } else {
            changeByIndex(j, k, j, k - 1);
        }
    }
}