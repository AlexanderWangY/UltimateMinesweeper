#include "../utils/LeaderboardHelper.h"
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

  // Setting number positions
  minuteTen.setPosition((columns * 32) - 97, 32 * (rows + 0.5) + 16);
  minute.setPosition((columns * 32) - 76, 32 * (rows + 0.5) + 16);
  secondTen.setPosition((columns * 32) - 54, 32 * (rows + 0.5) + 16);
  second.setPosition((columns * 32) - 33, 32 * (rows + 0.5) + 16);

  hundreth.setPosition(33, 32 * (rows + 0.5) + 16);
  tens.setPosition(54, 32 * (rows + 0.5) + 16);
  ones.setPosition(75, 32 * (rows + 0.5) + 16);

  // Setting starting values

  minuteTen.setTexture(buttonTextures[0]);
  minute.setTexture(buttonTextures[0]);
  secondTen.setTexture(buttonTextures[0]);
  second.setTexture(buttonTextures[0]);

  int flagHundred = flagsLeft / 100;
  int flagTen = (flagsLeft % 100) / 10;
  int flagOne = (flagsLeft % 10);

  hundreth.setTexture(buttonTextures[flagHundred]);
  tens.setTexture(buttonTextures[flagTen]);
  ones.setTexture(buttonTextures[flagOne]);

  timer.start();
}

GameScreen::~GameScreen() { delete board; }

void GameScreen::handleEvent(sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed) {
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;
    if (event.mouseButton.button == sf::Mouse::Left) {
      // Handle reset
      if (isClicked(happy, x, y)) {
        std::cout << "RESETTING GAME\n";
        this->reset();
      }

      // Handle debug
      if (isClicked(debug, x, y) && !gameOver && !paused) {
        std::cout << "Debug toggle\n";
        board->toggleDebug();
      }

      // Handle Pause
      if (isClicked(pause, x, y) && !gameOver) {
        paused = !paused;
        if (paused)
          timer.pause();
        else
          timer.start();
        board->togglePause();

        board->setDebug(false);
        std::cout << "Pause/Play toggle\n";
      }

      // Handle Leaderboard
      if (isClicked(leader, x, y)) {
        std::cout << "Opening leaderboard\n";

        int screenHeight = rows * 16 + 50;
        int screenWidth = columns * 16;

        sf::RenderWindow nWindow(sf::VideoMode(screenWidth, screenHeight),
                                 "Leaderboard", sf::Style::Close);

        Leaderboard leader(screenWidth, screenHeight);

        while (nWindow.isOpen()) {
          sf::Event event;
          while (nWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
              nWindow.close();
            }
          }

          nWindow.clear(sf::Color::Black);
          leader.render(nWindow);
          nWindow.display();
        }
      }

      if (!gameOver) {
        int result = board->handleClick(x, y);

        if (result == -1) {
          gameOver = true;
          paused = true;
          winner = false;
          board->setDebug(true);
          timer.pause();
        } else if (board->checkWinner()) {
          gameOver = true;
          paused = true;
          winner = true;
          flagsLeft = 0;
          board->setDebug(true);
          timer.pause();
          board->flagAll();
          int elapsedTime = timer.getElapsedTime();
          setScore(*username, elapsedTime);
        }
      }

    } else if (event.mouseButton.button == sf::Mouse::Right) {
      int result = board->handleFlag(x, y);

      if (result == 1) {
        flagsLeft++;
      } else {
        flagsLeft--;
      }
    }
  }
}

void GameScreen::update() {
  // Do something i guess

  if (flagsLeft >= 0) {
    int flagHundred = flagsLeft / 100;
    int flagTen = (flagsLeft % 100) / 10;
    int flagOne = (flagsLeft % 10);

    hundreth.setTexture(buttonTextures[flagHundred]);
    tens.setTexture(buttonTextures[flagTen]);
    ones.setTexture(buttonTextures[flagOne]);
  } else if (flagsLeft < 0) {
    hundreth.setTexture(buttonTextures[10]);
    int ABSflags = abs(flagsLeft);
    int flagTen = ABSflags / 10;
    int flagOne = (ABSflags % 10);
    tens.setTexture(buttonTextures[flagTen]);
    ones.setTexture(buttonTextures[flagOne]);
  }

  int elapsedTime = timer.getElapsedTime();
  timeElapsed = elapsedTime;
  int tenMinutes = elapsedTime / 600;
  elapsedTime = elapsedTime % 600;
  int minutes = elapsedTime / 60;
  elapsedTime = elapsedTime % 60;
  int tenSeconds = elapsedTime / 10;
  int seconds = elapsedTime % 10;

  minuteTen.setTexture(buttonTextures[tenMinutes]);
  minute.setTexture(buttonTextures[minutes]);
  secondTen.setTexture(buttonTextures[tenSeconds]);
  second.setTexture(buttonTextures[seconds]);
}

void GameScreen::reset() {
  flagsLeft = alienCount;
  winner = false;
  paused = false;
  gameOver = false;

  delete board;
  board = new Board(columns, rows, alienCount);

  timer.reset();
  timer.start();
}

void GameScreen::render(sf::RenderWindow &window) {
  window.clear(sf::Color::Black);
  board->render(window);

  window.draw(minuteTen);
  window.draw(minute);
  window.draw(secondTen);
  window.draw(second);

  window.draw(hundreth);
  window.draw(tens);
  window.draw(ones);

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
