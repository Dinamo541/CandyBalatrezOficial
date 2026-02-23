#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gems.h"

class Block : public Gems {
private:
    static const int id = -1;
    static const bool isSelected = false;

    Block(const Block&) = delete;
    Block& operator=(const Block&) = delete;

public:
    Block() {
        coords[0] = 0; coords[1] = 0;
        hitBox.setRadius(19.0f);
        hitBox.setOrigin(19.0f, 19.0f);
        hitBox.setPosition(145.f, 45.f);
        hitBox.setOutlineThickness(2.f);
        hitBox.setOutlineColor(sf::Color::Transparent);
        if (!texture.loadFromFile("assets/textures/Block.png")) {
            texture.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura Block.png\n";
        }
        hitBox.setTexture(&texture);
    }
    Block(int x, int y, sf::Vector2f newPosition) {
        coords[0] = x; coords[1] = y;
        hitBox.setRadius(19.0f);
        hitBox.setOrigin(19.0f, 19.0f);
        hitBox.setPosition(newPosition);
        hitBox.setOutlineThickness(2.f);
        hitBox.setOutlineColor(sf::Color::Transparent);
        position = newPosition;
        if (!texture.loadFromFile("assets/textures/Block.png")) {
            texture.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura Block.png\n";
        }
        hitBox.setTexture(&texture);
    }
    ~Block() = default;

    int getId() override { return id; }
    void setId(int newId) override {
        std::cout << "(St/Bl) Esta accion no esta permitida\n";
    }
    sf::CircleShape getHitBox() override { return hitBox; }

    void mouseIsOn() override {
        hitBox.setOutlineColor(sf::Color::Red);
    }
    void mouseIsNotOn() override {
        hitBox.setOutlineColor(sf::Color::Transparent);
    }
    void select() override {
        std::cout << "(Se/Bl) Esta accion no es posible\n";
    }
    void deselect() override {
        std::cout << "(De/Bl) Esta accion no es posible\n";
    }
};