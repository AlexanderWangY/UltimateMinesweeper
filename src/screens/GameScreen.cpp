#include "Screen.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
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

  flagsLeft = alienCount;

  // Loading button textures
  buttonTextures = getBoardTextures();

  win.setTexture(buttonTextures[13]);
  lose.setTexture(buttonTextures[14]);
  happy.setTexture(buttonTextures[12]);
  debug.setTexture(buttonTextures[17]);
  pause.setTexture(buttonTextures[15]);
  play.setTexture(buttonTextures[16]);
  leader.setTexture(buttonTextures[18]);

  board = new Board(columns, rows, alienCount);

  happy.setPosition(columns / 2.0 * 32.f - 32, 32 * (rows + 0.5));
  win.setPosition(columns / 2.0 * 32.f - 32, 32 * (rows + 0.5));
  lose.setPosition(columns / 2.0 * 32.f - 32, 32 * (rows + 0.5));
  debug.setPosition(columns * 32.f - 304, 32 * (rows + 0.5));
  pause.setPosition(columns * 32.f - 240, 32 * (rows + 0.5));
  play.setPosition(columns * 32.f - 240, 32 * (rows + 0.5));
  leader.setPosition(columns * 32.f - 176, 32 * (rows + 0.5));

  timer.start();
}

GameScreen::~GameScreen() { delete board; }

void GameScreen::handleEvent(sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      int x = event.mouseButton.x;
      int y = event.mouseButton.y;

      int result = board->handleClick(x, y);

      if (result == -1) {
        std::cout << "YOU LOST LMAO\n";
      } else if (result == 1) {
        std::cout << "You can't reveal a flag.\n";
      } else if (result == 404) {
        std::cout << "Did not click within bounds\n";
      } else if (result == 500) {
        std::cout << "Board is disabled.\n";
      }

      if (isClicked(debug, x, y) && !gameOver) {
        std::cout << "Toggling debug\n";
        debugMode = !debugMode;
      } else if (isClicked(happy, x, y)) {
        std::cout << "resetting game\n";
      } else if (isClicked(leader, x, y)) {
        std::cout << "Opening leaderboard\n";
        timer.pause();
        paused = true;
      } else if (isClicked(pause, x, y) && !gameOver) {
        if (timer.running()) {
          timer.pause();
        } else {
          timer.start();
        }
        debugMode = false;
        paused = !paused;
        board->disableStatus(!board->getStatus());
      }
    } else if (event.mouseButton.button == sf::Mouse::Right) {
      int x = event.mouseButton.x;
      int y = event.mouseButton.y;

      int result = board->handleFlag(x, y);
    }
  }
}

void GameScreen::update() {
  // Do something i guess
}

void GameScreen::render(sf::RenderWindow &window) {
  window.clear(sf::Color::Black);
  board->render(window);

  if (paused) {
    window.draw(play);
  } else {
    window.draw(pause);
  }

  window.draw(leader);
  window.draw(debug);

  if (gameOver) {
    if (winner) {
      window.draw(win);
    } else {
      window.draw(lose);
    }
  } else {
    window.draw(happy);
  }
}
