// game.cpp
// Main application entry point for the Alien Attack game. It initializes and
// runs the game loop.
//
// MILTON ADINA
// Programming II Final Project
// game.cpp
// 13/04/2024

#include "alienArmy.h"
#include "gameFunctions.h"
#include "gameHeader.h"
#include "pixie.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                          "Alien Attack");
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
  Pixie ship(shipTexture, WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT - 60,
             PLAYER_SHIP_PIXIE);

  AlienArmy alienArmy;
  // Populate the alien army using constants
  for (int i = 0; i < ALIEN_COUNT; i++) {
    alienArmy.addAlien(
        Pixie(alienTexture, i * ALIEN_SPACING, ALIEN_INITIAL_Y, ALIEN_PIXIE));
  }

  std::vector<Pixie> missiles;
  bool gameOver = false;
  int score = 0;
  float shipRespawnTimer = 0.0f;

  sf::Clock clock;

  while (window.isOpen() && !gameOver) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      // Handling keyboard input for firing missiles
      if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Space) {
          missiles.push_back(Pixie(
              missileTexture,
              ship.getX() + ship.getSprite().getGlobalBounds().size.x / 2 - 10,
              ship.getY(), PLAYER_MISSILE_PIXIE));
        }
      }
    }

    float deltaTime = clock.restart().asSeconds();

    // Handle ship respawn timer
    if (!ship.isVisible() && shipRespawnTimer > 0.0f) {
      shipRespawnTimer -= deltaTime;
      if (shipRespawnTimer <= 0.0f) {
        ship.setVisible(true);
      }
    }

    // Move the ship based on user input
    if (ship.isVisible()) {
      moveShip(ship, deltaTime);
    }

    // Update player missile positions
    for (auto &missile : missiles) {
      missile.move(0, -MISSILE_SPEED);
      if (missile.getY() < 0) { // Remove missiles that move off-screen
        missile.setVisible(false);
      }
    }
    missiles.erase(
        std::remove_if(missiles.begin(), missiles.end(),
                       [](const Pixie &m) { return !m.isVisible(); }),
        missiles.end());

    // Move aliens and handle alien missile firing
    alienArmy.moveArmy(deltaTime);
    alienArmy.fireMissiles(deltaTime); // Allow aliens to fire missiles
    alienArmy.updateMissiles();        // Update positions of alien missiles

    // Check for collisions between player missiles and aliens
    alienArmy.handleCollisions(missiles, &ship, shipRespawnTimer);

    // Render the scene
    window.clear();
    background.draw(window);
    ship.draw(window);
    for (auto &missile : missiles) {
      missile.draw(window);
    }
    alienArmy.drawArmy(window);
    alienArmy.drawMissiles(window); // Ensure alien missiles are drawn

    // Display the rendered frame
    window.display();

    // Check if the game should end
    if (alienArmy.isAllDestroyed()) {
      int finalScore =
          alienArmy.getScore(); // Retrieve the final score from the alienArmy
      std::cout << "Game over! Total score: " << finalScore << std::endl;
      gameOver = true; // Set game over flag to exit loop
    }
  }

  return 0;
}
