#include "screens/Screen.h"
#include "utils/Configuration.h"
#include "utils/Gamestate.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <fstream>
#include <iostream>
#include <string>

int main() {

  Gamestate mainState = Gamestate::Title;

  Config config;

  // Loading config for sizing

  std::ifstream file("files/config.cfg");
  std::string line;
  sf::Image icon;
  icon.loadFromFile("./files/images/alien.png");

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

  int screenWidth = config.columns * 32;
  int screenHeight = config.rows * 32 + 100;
  std::string username = "";

  sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
                          "Aliensweeper", sf::Style::Close);
  TitleScreen title(screenWidth, screenHeight);
  GameScreen game(screenWidth, screenHeight, config.columns, config.rows,
                  config.alienCount, username);

  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      switch (mainState) {
      case Gamestate::Title:
        title.handleEvent(event, mainState, username);
        break;
      case Gamestate::Game:
        game.handleEvent(event);
        break;
      }
    }

    switch (mainState) {
    case Gamestate::Title:
      title.update();
      title.render(window);
      break;
    case Gamestate::Game:
      game.render(window);
      break;
    }

    // Displaying

    window.display();
  }

  return 0;
}
