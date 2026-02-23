#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gems.h"

class Bombs : public Gems {
private:
    int type;
    int id;

    Bombs(const Bombs&) = delete;
    Bombs& operator=(const Bombs&) = delete;

public:
    Bombs() : Gems() {
        id = 0;
        type = 0;
    }
    Bombs(int newType, int newId, int x, int y, sf::Vector2f newPosition) : type(newType), id(newId) {
        coords[0] = x; coords[1] = y;
        hitBox.setRadius(19.0f);
        hitBox.setOrigin(19.0f, 19.0f);
        hitBox.setPosition(newPosition);
        hitBox.setOutlineThickness(2.f);
        hitBox.setOutlineColor(sf::Color::Transparent);
        position = newPosition;
        changeTexture();
    }
    ~Bombs() = default;

    int getId() override { return -2; }
    void setId(int newId) override { /* No hacer nada */ }
    int getType() override { return type; }
    void setType(int newType) { type = newType; }
    sf::CircleShape getHitBox() const { return hitBox; }

    void mouseIsOn() override {
        if (!getIsSelected()) {
            hitBox.setOutlineColor(sf::Color::Green);
        }
        hitBox.setScale(1.05f, 1.05f);
    }
    void mouseIsNotOn() override {
        if (!getIsSelected()) {
            hitBox.setOutlineColor(sf::Color::Transparent);
        }
        hitBox.setScale(1.0f, 1.0f);
    }
    void select() override {
        hitBox.setFillColor(sf::Color(190, 190, 190));
    }
    void deselect() override {
        hitBox.setFillColor(sf::Color::White);
    }
    void changeTexture() override {
        switch (type) {
        case 1:
            if (!texture.loadFromFile("assets/textures/Bomb.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura Bomb.png\n";
            }
            hitBox.setTexture(&texture);
            hitBox.setRotation(-45.0f);
            break;
        case 2:
            if (!texture.loadFromFile("assets/textures/Bomb.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura Bomb.png\n";
            }
            hitBox.setTexture(&texture);
            hitBox.setRotation(45.0f);
            break;
        case 3:
            if (!texture.loadFromFile("assets/textures/UltraBomb.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura UltraBomb.png\n";
            }
            hitBox.setTexture(&texture);
            hitBox.setRotation(45.0f);
            break;
        default:
            if (!texture.loadFromFile("assets/textures/thumbnail.png")) {
                std::cerr << "No se pudo cargar la textura thumbnail.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        }
    }
};