// alienArmy.cpp
// Implementation of the AlienArmy class for managing alien entities in the
// game.
//
// MILTON ADINA
// Programming II Final Project
// alienArmy.cpp
// 13/04/2024

#include "alienArmy.h"
#include <algorithm> // For std::remove_if
#include <chrono>
#include <iostream>
#include <thread> // Include this for std::thread


// constructor for the alien army
/**
 * @brief Constructs an instance of the AlienArmy class.
 * Initializes the `alienTexture` to an empty texture, `timeSinceLastFire` to
 * 0.0f, and `fireRate` to 1.0f.
 */
AlienArmy::AlienArmy()
    : timeSinceLastFire(0.0f), fireRate(1.0f), score(0),
      rng(std::random_device{}()), distribution(0.0f, 1.0f) {
  loadMissileTexture("missile.png");
}

// load the missile texture
/**
 * @brief Loads the missile texture from the specified file.
 *
 * @param filename The name of the file containing the missile texture.
 * @return True if the texture is loaded successfully, false otherwise.
 */
bool AlienArmy::loadMissileTexture(const std::string &filename) {
  return missileTexture.loadFromFile(filename);
}

// add an alien to the army
/**
 * @brief Adds an alien to the alien army.
 *
 * @param alien The alien to be added.
 */
void AlienArmy::addAlien(const Pixie &alien) { aliens.push_back(alien); }

/**
 * Moves the alien army horizontally and vertically.
 * Reverses the direction of movement when the edge is reached.
 */
void AlienArmy::moveArmy(float deltaTime) {
  static bool movingRight = true; // Bool to move right
  bool edgeReached = false;       // Bool to check if edge is reached

  // Loop to move the aliens
  for (auto &alien : aliens) {
    float moveX =
        movingRight
            ? ALIEN_SPEED * deltaTime
            : -ALIEN_SPEED * deltaTime; // Calculate the horizontal movement
    alien.move(moveX, 0);               // Move the alien horizontally

    // Check if the edge is reached
    if (movingRight &&
            alien.getX() + alien.getSprite().getGlobalBounds().size.x >=
                WINDOW_WIDTH ||
        !movingRight && alien.getX() <= 0) {
      edgeReached = true; // Set edgeReached to true
    }
  }

  // Move the aliens down and reverse the direction if the edge is reached
  if (edgeReached) {
    for (auto &alien : aliens) {
      alien.move(0, 10); // Move the alien down by a step
    }
    movingRight = !movingRight; // Reverse the direction
  }
}

/**
 * Fires missiles from the alien army.
 *
 * @param deltaTime The time elapsed since the last frame.
 */
void AlienArmy::fireMissiles(float deltaTime) {
  // Increase the time since the last shot
  timeSinceLastFire += deltaTime;

  // Check if it's time to fire based on the firing rate
  if (timeSinceLastFire >= fireRate) {
    timeSinceLastFire = 0.0f; // Reset the time since the last fire

    // Iterate through each alien to determine if it should fire
    for (const auto &alien : aliens) {
      // Randomly determine whether the alien should fire
      float randomValue = distribution(rng);
      float firingProbability = 0.05f; // Adjust this probability as needed

      if (randomValue < firingProbability) {
        missiles.push_back(Pixie(
            missileTexture,
            alien.getX() + alien.getSprite().getGlobalBounds().size.x / 2,
            alien.getY() + alien.getSprite().getGlobalBounds().size.y,
            PLAYER_MISSILE_PIXIE)); // Create a missile and add it to the vector
      }
    }
  }
}

/**
 * Updates the position of the missiles fired by the alien army.
 * Removes the missiles that have gone out of the window.
 */
void AlienArmy::updateMissiles() {
  for (auto &missile : missiles) {
    missile.move(0, MISSILE_SPEED); // Move the missile vertically
    if (missile.getY() >
        WINDOW_HEIGHT) {         // Check if the missile is out of the window
      missile.setVisible(false); // Mark for deletion
    }
  }

  // Actually remove them
  missiles.erase(std::remove_if(missiles.begin(), missiles.end(),
                                [](const Pixie &m) { return !m.isVisible(); }),
                 missiles.end());
}

/**
 * Handles collisions between player missiles, aliens, and the ship.
 *
 * @param playerMissiles The vector of player missiles.
 * @param ship The pointer to the ship object.
 */
void AlienArmy::handleCollisions(std::vector<Pixie> &playerMissiles,
                                 Pixie *ship, float &respawnTimer) {
  // Collision detection between player missiles and aliens
  for (auto &alien : aliens) {
    if (!alien.isVisible())
      continue;

    for (auto &missile : playerMissiles) {
      if (!missile.isVisible())
        continue;

      if (alien.getSprite()
              .getGlobalBounds()
              .findIntersection(missile.getSprite().getGlobalBounds())
              .has_value()) {
        score += 10;
        std::cout << "Alien hit! Score: " << score << std::endl;

        // Mark both for deletion
        alien.setVisible(false);
        missile.setVisible(false);

        break; // A missile can only hit one alien, and this alien is now dead
      }
    }
  }

  // Check collisions between alien missiles and the ship
  if (ship && ship->isVisible()) {
    for (auto &missile : missiles) {
      if (!missile.isVisible())
        continue;

      if (missile.getSprite()
              .getGlobalBounds()
              .findIntersection(ship->getSprite().getGlobalBounds())
              .has_value()) {
        std::cout << "Ship hit by alien missile!" << std::endl;
        ship->setVisible(false);
        respawnTimer = 1.0f; // Set respawn delay to 1 second

        missile.setVisible(false); // The missile is destroyed on impact
      }
    }
  }

  // Sweep the dead entities efficiently from vector memory
  aliens.erase(std::remove_if(aliens.begin(), aliens.end(),
                              [](const Pixie &a) { return !a.isVisible(); }),
               aliens.end());
  missiles.erase(std::remove_if(missiles.begin(), missiles.end(),
                                [](const Pixie &m) { return !m.isVisible(); }),
                 missiles.end());
  playerMissiles.erase(
      std::remove_if(playerMissiles.begin(), playerMissiles.end(),
                     [](const Pixie &m) { return !m.isVisible(); }),
      playerMissiles.end());
}

/**
 * Draws the alien army on the specified window.
 *
 * @param window The SFML RenderWindow to draw the aliens on.
 */
void AlienArmy::drawArmy(sf::RenderWindow &window) {
  // Loop through each alien in the army
  for (auto &alien : aliens) {
    alien.draw(window); // Draw the alien on the window
  }
}

/**
 * Draws the missiles fired by the alien army on the specified window.
 *
 * @param window The SFML RenderWindow to draw the missiles on.
 */
void AlienArmy::drawMissiles(sf::RenderWindow &window) {
  for (auto &missile : missiles) {
    missile.draw(window);
  }
}

/**
 * Checks if all aliens in the army have been destroyed.
 *
 * @return True if all aliens are destroyed, false otherwise.
 */
bool AlienArmy::isAllDestroyed() const { return aliens.empty(); }
