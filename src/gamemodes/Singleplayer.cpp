#include "Singleplayer.h"
#include "../utils/Gamestate.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <fstream>
#include <iostream>
#include <string>

bool playSingleplayer(Config &config) {
  Gamestate state = Gamestate::Title;

  // Now rendering the main pages
  int screenWidth = config.columns * 32;
  int screenHeight = (config.rows * 32) + 100;

  sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
                          "Aliensweeper", sf::Style::Close);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }

  return true;
}
