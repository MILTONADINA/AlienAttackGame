// gameHeader.h
// Definitions of global constants and game-specific types used across the Alien Attack game.
//
// MILTON ADINA
// Programming II Final Project
// gameHeader.h
// 13/04/2024

#ifndef GAME_HEADER_H
#define GAME_HEADER_H

#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;  // The width of the game window
const int WINDOW_HEIGHT = 600;  // The height of the game window
const float DISTANCE = 5.0f;  // Movement distance per frame for the ship
const float MISSILE_SPEED = 10.0f;  // Speed of the player's missiles
const float ALIEN_SPEED = 2.0f;  // Horizontal movement speed of aliens

// Number of aliens in the first row
const int ALIEN_COUNT = 10;

// Horizontal spacing between aliens
const float ALIEN_SPACING = 70.0f;

// Initial vertical position of aliens
const float ALIEN_INITIAL_Y = 50.0f;

/**
 * @brief Enumeration of different types of pixies used in the game.
 */
enum PixieType {
    UNDEFINED_PIXIE = 0,        // Undefined pixie type
    PLAYER_SHIP_PIXIE,         // Pixie type for the player's ship
    PLAYER_MISSILE_PIXIE,      // Pixie type for the player's missile
    BACKGROUND_PIXIE,          // Pixie type for the background
    ALIEN_PIXIE                // Pixie type for the aliens
};

#endif // GAME_HEADER_H
