// MILTON ADINA
// Programming II Final Project
// // pixie.h
// 13/04/2024
#ifndef PIXIE_H
#define PIXIE_H

#include <SFML/Graphics.hpp>
#include "gameHeader.h"

//claas to create pixie objects

class Pixie {
private:
    sf::Sprite sprite;// Sprite for the pixie
    int pixieType;       // Using PixieType enum
    bool visible = true;  // Add visibility control

public:
    // Constructor that sets sprite properties using an existing texture
    Pixie(sf::Texture& texture, float x, float y, PixieType type);// Constructor that sets sprite properties using an existing texture
    void setVisible(bool vis) { visible = vis; }// Set visibility
    bool isVisible() const { return visible; }// Get visibility

    void draw(sf::RenderWindow& window) const;// Draw the pixie
    void move(float dx, float dy);// Move the pixie
    void setPosition(float x, float y);// Set the position of the pixie
    float getX() const;// Get the horizontal position of the pixie
    float getY() const;// Get the verticle position of the pixie
    const sf::Sprite& getSprite() const;//Get the sprite
};

#endif // PIXIE_H
