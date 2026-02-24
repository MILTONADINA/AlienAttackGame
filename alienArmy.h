/**
 * @file alienArmy.h
 * @brief Declaration of the AlienArmy class.
 */

#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "gameHeader.h"
#include "pixie.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

/**
 * @class AlienArmy
 * @brief Represents an army of aliens in a game.
 */
class AlienArmy {
private:
  std::vector<Pixie> aliens;   /**< The vector of aliens in the army. */
  std::vector<Pixie> missiles; /**< The vector of missiles fired by aliens. */
  sf::Texture missileTexture;  /**< The texture for the missiles. */
  float fireRate =
      1.0f; /**< The time in seconds between checks to fire missiles. */
  float timeSinceLastFire =
      0.0f;      /**< The elapsed time since the last missile was fired. */
  int score = 0; /**< The score of the player. */

  std::mt19937 rng; // Random number generator
  std::uniform_real_distribution<float>
      distribution; // Uniform distribution for random floats

public:
  /**
   * @brief Default constructor for AlienArmy.
   */
  AlienArmy();

  /**
   * @brief Loads the texture for the missiles.
   * @param filename The filename of the texture.
   * @return True if the texture is loaded successfully, false otherwise.
   */
  bool loadMissileTexture(const std::string &filename);

  /**
   * @brief Adds an alien to the army.
   * @param alien The alien to add.
   */
  void addAlien(const Pixie &alien);

  /**
   * @brief Moves the entire army of aliens.
   * @param deltaTime The time since the last frame.
   */
  void moveArmy(float deltaTime);

  /**
   * @brief Fires missiles from the aliens.
   * @param deltaTime The time since the last frame.
   */
  void fireMissiles(float deltaTime);

  /**
   * @brief Updates the positions of the missiles.
   */
  void updateMissiles();

  /**
   * @brief Handles collisions between player missiles and the ship.
   * @param playerMissiles The vector of player missiles.
   * @param ship The ship object.
   */
  void handleCollisions(std::vector<Pixie> &playerMissiles, Pixie *ship,
                        float &respawnTimer);

  /**
   * @brief Draws the army of aliens on the window.
   * @param window The SFML render window.
   */
  void drawArmy(sf::RenderWindow &window);

  /**
   * @brief Draws the missiles on the window.
   * @param window The SFML render window.
   */
  void drawMissiles(sf::RenderWindow &window);

  /**
   * @brief Checks if all aliens in the army are destroyed.
   * @return True if all aliens are destroyed, false otherwise.
   */
  bool isAllDestroyed() const;

  /**
   * @brief Gets the score of the player.
   * @return The score of the player.
   */
  int getScore() const { return score; }
};

#endif // ALIEN_ARMY_H
