#include "Screen.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <string>

GameScreen::GameScreen(int _width, int _height, int _columns, int _rows,
                       int _alienCount, std::string &_username) {
  // Preprocessing some of the information
  width = _width;
  height = _height;
  columns = _columns;
  rows = _rows;
  alienCount = _alienCount;
  username = &_username;

  board = new Board(columns, rows, alienCount);
}

GameScreen::~GameScreen() { delete board; }

void GameScreen::handleEvent(sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed) {
    std::cout << "MOUSE PRESSED :0\n";
    std::cout << "From user: " << *username << "\n";
  }
}

void GameScreen::update() {
  // Do something i guess
}

void GameScreen::render(sf::RenderWindow &window) {
  window.clear(sf::Color::Black);
  board->render(window);
}
