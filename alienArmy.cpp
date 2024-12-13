// alienArmy.cpp
// Implementation of the AlienArmy class for managing alien entities in the game.
//
// MILTON ADINA
// Programming II Final Project
// alienArmy.cpp
// 13/04/2024

#include "alienArmy.h"
#include <iostream>
#include <thread>  // Include this for std::thread
#include <chrono>


//constructor for the alien army
/**
 * @brief Constructs an instance of the AlienArmy class.
 * Initializes the elapsedTimeSinceLastFire and score variables.
 * Loads the missile texture from the specified file.
 */
AlienArmy::AlienArmy() : elapsedTimeSinceLastFire(0.0f), score(0) {
    loadMissileTexture("missile.png"); 
}

//load the missile texture
/**
 * @brief Loads the missile texture from the specified file.
 * 
 * @param filename The name of the file containing the missile texture.
 * @return True if the texture is loaded successfully, false otherwise.
 */
bool AlienArmy::loadMissileTexture(const std::string& filename) {
    return missileTexture.loadFromFile(filename);
}

//add an alien to the army
/**
 * @brief Adds an alien to the alien army.
 * 
 * @param alien The alien to be added.
 */
void AlienArmy::addAlien(const Pixie& alien) {
    aliens.push_back(alien);
}



/**
 * Moves the alien army horizontally and vertically.
 * Reverses the direction of movement when the edge is reached.
 */
void AlienArmy::moveArmy() {
    static bool movingRight = true; // Bool to move right
    bool edgeReached = false; // Bool to check if edge is reached

    // Loop to move the aliens
    for (auto& alien : aliens) {
        float moveX = movingRight ? ALIEN_SPEED : -ALIEN_SPEED; // Calculate the horizontal movement
        alien.move(moveX, 0); // Move the alien horizontally

        // Check if the edge is reached
        if (movingRight && alien.getX() + alien.getSprite().getGlobalBounds().width >= WINDOW_WIDTH ||
            !movingRight && alien.getX() <= 0) {
            edgeReached = true; // Set edgeReached to true
        }
    }

    // Move the aliens down and reverse the direction if the edge is reached
    if (edgeReached) {
        for (auto& alien : aliens) {
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
    elapsedTimeSinceLastFire += deltaTime; // Update the time since the last fire
    if (elapsedTimeSinceLastFire >= fireRate) {
        std::random_device rd; // Create a random device
        std::mt19937 gen(rd()); // Create a random number generator
        std::uniform_int_distribution<> dis(0, aliens.size() - 1); // Create a uniform distribution of aliens

        elapsedTimeSinceLastFire = 0.0f; // Reset the time since the last fire

        for (int i = 0; i < 2; ++i) {
            int alienIndex = dis(gen); // Get a random alien index
            missiles.push_back(Pixie(missileTexture, aliens[alienIndex].getX(), aliens[alienIndex].getY(), PLAYER_MISSILE_PIXIE)); // Create a missile and add it to the vector
        }
    }
}


/**
 * Updates the position of the missiles fired by the alien army.
 * Removes the missiles that have gone out of the window.
 */
void AlienArmy::updateMissiles() {
    auto it = missiles.begin();
    while (it != missiles.end()) {
        it->move(0, MISSILE_SPEED); // Move the missile vertically
        if (it->getY() > WINDOW_HEIGHT) { // Check if the missile is out of the window
            it = missiles.erase(it); // Remove the missile from the vector
        }
        else {
            ++it;
        }
    }
}


/**
 * Handles collisions between player missiles, aliens, and the ship.
 * 
 * @param playerMissiles The vector of player missiles.
 * @param ship The pointer to the ship object.
 */
void AlienArmy::handleCollisions(std::vector<Pixie>& playerMissiles, Pixie* ship) {
    // Collision detection between player missiles and aliens
    for (auto itAlien = aliens.begin(); itAlien != aliens.end();) {
        bool alienHit = false;
        for (auto itMissile = playerMissiles.begin(); itMissile != playerMissiles.end();) {
            if (itAlien->getSprite().getGlobalBounds().intersects(itMissile->getSprite().getGlobalBounds())) {
                score += 10;
                std::cout << "Alien hit! Score: " << score << std::endl;
                alienHit = true;
                // Remove the missile that hit the alien
                itMissile = playerMissiles.erase(itMissile);
                break; // Exit the loop after the hit to avoid invalid iterator use
            }
            else {
                ++itMissile;
            }
        }
        if (alienHit) {
            itAlien = aliens.erase(itAlien); // Remove the hit alien
        }
        else {
            ++itAlien;
        }
    }

    // Check collisions between alien missiles and the ship
    if (ship) {
        for (auto itMissile = missiles.begin(); itMissile != missiles.end();) {
            if (itMissile->getSprite().getGlobalBounds().intersects(ship->getSprite().getGlobalBounds())) {
                std::cout << "Ship hit by alien missile!" << std::endl;
                ship->setVisible(false);
                itMissile = missiles.erase(itMissile);  // Remove the missile that hit the ship

                // Delay to respawn the ship
                std::thread([ship]() {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    ship->setVisible(true);
                    }).detach();
            }
            else {
                ++itMissile;
            }
        }
    }
}


/**
 * Draws the alien army on the specified window.
 * 
 * @param window The SFML RenderWindow to draw the aliens on.
 */
void AlienArmy::drawArmy(sf::RenderWindow& window) {
    // Loop through each alien in the army
    for (auto& alien : aliens) {
        alien.draw(window); // Draw the alien on the window
    }
}

/**
 * Draws the missiles fired by the alien army on the specified window.
 * 
 * @param window The SFML RenderWindow to draw the missiles on.
 */
void AlienArmy::drawMissiles(sf::RenderWindow& window) {
    for (auto& missile : missiles) {
        missile.draw(window);
    }
}

/**
 * Checks if all aliens in the army have been destroyed.
 * 
 * @return True if all aliens are destroyed, false otherwise.
 */
bool AlienArmy::isAllDestroyed() const {
    return aliens.empty();
}
