#include "Game.h"

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Candy Balatrez", sf::Style::Close);
    Game gameOne(window);
    gameOne.run();
    return 0;
}