#include "Singleplayer.h"
#include "../utils/Gamestate.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <fstream>
#include <iostream>
#include <string>

bool playSingleplayer() {
  Gamestate state = Gamestate::Title;

  std::ifstream file("../files/config/cfg");
  Config config;
  std::string line;

  // Open config file and store it in a struct
  if (file.is_open()) {
    std::getline(file, line);
    config.columns = std::stoi(line);
    std::getline(file, line);
    config.rows = std::stoi(line);
    std::getline(file, line);
    config.alienCount = std::stoi(line);
  } else {
    std::cerr << "An error occured while trying to open config files\n";
    return false;
  }
  // Now rendering the main pages
  int screenWidth = config.columns * 32;
  int screenHeight = (config.rows * 32) + 100;

  sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
                          "Aliensweeper", sf::Style::Close);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
    }
  }

  return true;
}
