// MILTON ADINA
// Programming II Final Project
// // pixie.cpp
// 13/04/2024
#include "pixie.h"

Pixie::Pixie(sf::Texture &texture, float x, float y, PixieType type)
    : sprite(texture), pixieType(type) {
  sprite.setPosition({x, y});
}

/**
 * @brief Draws the pixie on the specified window.
 *
 * @param window The SFML RenderWindow to draw the pixie on.
 */
void Pixie::draw(sf::RenderWindow &window) const {
  if (visible) {
    window.draw(sprite);
  }
}

/**
 * @brief Moves the pixie by the specified amount in the x and y directions.
 *
 * @param dx The amount to move the pixie in the x direction.
 * @param dy The amount to move the pixie in the y direction.
 */
void Pixie::move(float dx, float dy) { sprite.move({dx, dy}); }

/**
 * @brief Sets the position of the pixie to the specified coordinates.
 *
 * @param x The x-coordinate to set the position to.
 * @param y The y-coordinate to set the position to.
 */
void Pixie::setPosition(float x, float y) { sprite.setPosition({x, y}); }

/**
 * @brief Gets the x-coordinate of the pixie's current position.
 *
 * @return The x-coordinate of the pixie's current position.
 */
float Pixie::getX() const { return sprite.getPosition().x; }

/**
 * @brief Gets the y-coordinate of the pixie's current position.
 *
 * @return The y-coordinate of the pixie's current position.
 */
float Pixie::getY() const { return sprite.getPosition().y; }

/**
 * @brief Gets a constant reference to the sprite of the pixie.
 *
 * @return A constant reference to the sprite of the pixie.
 */
const sf::Sprite &Pixie::getSprite() const { return sprite; }
