#include "gamemodes/Singleplayer.h"
#include "screens/Screen.h"
#include "utils/Gamestate.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <fstream>
#include <iostream>

int main() {

  Gamestate mainState = Gamestate::Selection;

  Config config;

  // Loading config for sizing

  std::ifstream file("files/config.cfg");
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
    return 1;
  }

  int choice = 0;

  sf::RenderWindow window(
      sf::VideoMode(config.columns * 32, config.rows * 32 + 100),
      "Aliensweeper", sf::Style::Close);
  SelectionScreen selection(config.columns * 32, config.rows * 32 + 100);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (mainState == Gamestate::Selection) {
        selection.handleEvent(event);
      }
    }

    if (mainState == Gamestate::Selection) {
      selection.render(window);
    }
  }

  return 0;
}
