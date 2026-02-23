#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Gems {
private:
    int id;
    bool isSelected;

    Gems(const Gems&) = delete;
    Gems& operator=(const Gems&) = delete;

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
        hitBox.setOrigin(19.0f, 19.0f);
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
        hitBox.setOrigin(19.0f, 19.0f);
        hitBox.setPosition(newPosition);
        position = newPosition;
        changeTexture();
        hitBox.setOutlineThickness(2.f);
        hitBox.setOutlineColor(sf::Color::Transparent);
        isSelected = false;
    }
    ~Gems() = default;

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
    void setFillColor(sf::Color newColor) {
        hitBox.setFillColor(newColor);
    }

    virtual int getId() { return id; }
    virtual int getType() { return -1; }
    int getX() { return coords[0]; }
    int getY() { return coords[1]; }
    sf::Vector2f getPosition() { return position; }
    virtual sf::CircleShape getHitBox() { return hitBox; }
    bool getIsSelected() { return isSelected; }

    virtual void mouseIsOn() {
        if (!isSelected) {
            hitBox.setOutlineColor(sf::Color::Yellow);
        }
        hitBox.setScale(1.05f, 1.05f);
    }
    virtual void mouseIsNotOn() {
        if (!isSelected) {
            hitBox.setOutlineColor(sf::Color::Transparent);
        }
        hitBox.setScale(1.0f, 1.0f);
    }
    virtual void select() {
        isSelected = true;
        hitBox.setFillColor(sf::Color(152, 250, 140));
    }
    virtual void deselect() {
        hitBox.setFillColor(sf::Color::White);
        isSelected = false;
    }
    virtual void changeTexture() {
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