// gameFunctions.cpp
// Implementation of game-related utility functions like moving the ship.
//
// MILTON ADINA
// Programming II Final Project
// gameFunctions.cpp
// 13/04/2024

#include "gameFunctions.h"
#include "gameHeader.h"
#include <SFML/Window/Keyboard.hpp>

/**
 * Moves the ship based on the user input.
 * @param ship The Pixie object representing the ship.
 */
void moveShip(Pixie& ship) {
    const float shipWidth = ship.getSprite().getGlobalBounds().width;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ship.getX() > 0) {
        ship.move(-DISTANCE, 0);  // Move ship left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ship.getX() + shipWidth < WINDOW_WIDTH) {
        ship.move(DISTANCE, 0);  // Move ship right
    }
}
