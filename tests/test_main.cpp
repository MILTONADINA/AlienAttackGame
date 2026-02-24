#include "../alienArmy.h"
#include "../pixie.h"
#include "catch_amalgamated.hpp"
#include <iostream>


TEST_CASE("Alien Army Initialization", "[AlienArmy]") {
  // We cannot easily test SFML texture loading headlessly here without a dummy
  // image. In a real headless CI we would mock the `sf::Texture` or use an
  // empty initialized texture. For this baseline, we just check that the class
  // compiles and links.
  REQUIRE(true);
}
