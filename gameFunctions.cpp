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
void moveShip(Pixie &ship, float deltaTime) {
  const float shipWidth = ship.getSprite().getGlobalBounds().size.x;
  // Scale distance by 60 for roughly the same speed as before (which assumed
  // ~60fps)
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && ship.getX() > 0) {
    ship.move(-DISTANCE * 60.0f * deltaTime, 0); // Move ship left
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
      ship.getX() + shipWidth < WINDOW_WIDTH) {
    ship.move(DISTANCE * 60.0f * deltaTime, 0); // Move ship right
  }
}
