#include "../utils/TextHelper.h"
#include "Screen.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

SelectionScreen::SelectionScreen(int _width, int _height) {
  width = _width;
  height = _height;

  font.loadFromFile("files/font1.otf");

  // Setting up selection
  titleText.setFont(font);
  titleText.setString("Aliensweeper");
  titleText.setCharacterSize(24);
  titleText.setFillColor(sf::Color::Green);
  titleText.setStyle(sf::Text::Bold);
  setText(titleText, width / 2, height / 2 - 150);

  // Setting up subtext
  subText.setFont(font);
  subText.setString("Choose your mode");
  subText.setCharacterSize(18);
  subText.setFillColor(sf::Color::White);
  setText(titleText, width / 2, height / 2 - 150);
}

void SelectionScreen::handleEvent(const sf::Event &event) {
  if (event.key.code == sf::Keyboard::Up) {
    std::cout << "UP!\n";
  } else if (event.key.code == sf::Keyboard::Down) {
    std::cout << "DOWN!\n";
  }
}

void SelectionScreen::update() {}

void SelectionScreen::render(sf::RenderWindow &window) {
  window.draw(titleText);
  window.draw(subText);
}
