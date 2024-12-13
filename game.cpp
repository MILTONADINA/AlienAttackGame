// game.cpp
// Main application entry point for the Alien Attack game. It initializes and runs the game loop.
//
// MILTON ADINA
// Programming II Final Project
// game.cpp
// 13/04/2024

#include "gameHeader.h"
#include "pixie.h"
#include "alienArmy.h"
#include "gameFunctions.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Alien Attack");
    window.setFramerateLimit(60);

    // Load textures
    sf::Texture shipTexture, backgroundTexture, alienTexture, missileTexture;
    if (!shipTexture.loadFromFile("ship.png") ||
        !backgroundTexture.loadFromFile("stars.jpg") ||
        !alienTexture.loadFromFile("alien.bmp") ||
        !missileTexture.loadFromFile("missile.png")) {
        std::cerr << "Error loading textures" << std::endl;
        return -1; // Exit if any texture fails to load
    }

    // Initialize game entities
    Pixie background(backgroundTexture, 0, 0, BACKGROUND_PIXIE);
    Pixie ship(shipTexture, WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT - 60, PLAYER_SHIP_PIXIE);

    AlienArmy alienArmy;
    // Populate the alien army using constants
    for (int i = 0; i < ALIEN_COUNT; i++) {
        alienArmy.addAlien(Pixie(alienTexture, i * ALIEN_SPACING, ALIEN_INITIAL_Y, ALIEN_PIXIE));
    }

    std::vector<Pixie> missiles;
    bool gameOver = false;
    int score = 0;

    sf::Clock clock;

    while (window.isOpen() && !gameOver) {
        alienArmy.handleCollisions(missiles, &ship);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handling keyboard input for firing missiles
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                missiles.push_back(Pixie(missileTexture, ship.getX() + ship.getSprite().getGlobalBounds().width / 2 - 10, ship.getY(), PLAYER_MISSILE_PIXIE));
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Move the ship based on user input
        moveShip(ship);

        // Update player missile positions
        auto missileIt = missiles.begin();
        while (missileIt != missiles.end()) {
            missileIt->move(0, -MISSILE_SPEED);
            if (missileIt->getY() < 0) { // Remove missiles that move off-screen
                missileIt = missiles.erase(missileIt);
            }
            else {
                ++missileIt;
            }
        }

        // Move aliens and handle alien missile firing
        alienArmy.moveArmy();
        alienArmy.fireMissiles(deltaTime); // Allow aliens to fire missiles
        alienArmy.updateMissiles(); // Update positions of alien missiles

        // Check for collisions between player missiles and aliens
        alienArmy.handleCollisions(missiles, &ship);


        // Render the scene
        window.clear();
        background.draw(window);
        ship.draw(window);
        for (auto& missile : missiles) {
            missile.draw(window);
        }
        alienArmy.drawArmy(window);
        alienArmy.drawMissiles(window); // Ensure alien missiles are drawn

        // Display the rendered frame
        window.display();

        // Check if the game should end
        if (alienArmy.isAllDestroyed()) {
            int finalScore = alienArmy.getScore(); // Retrieve the final score from the alienArmy
            std::cout << "Game over! Total score: " << finalScore << std::endl;
            gameOver = true; // Set game over flag to exit loop
        }
    }

    return 0;
}
