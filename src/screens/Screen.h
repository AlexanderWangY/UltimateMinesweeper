#pragma once
#include "../classes/Board.h"
#include "../utils/Gamestate.h"
#include "../utils/TimerUtility.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <unordered_map>

class Screen {
public:
  virtual void render(sf::RenderWindow &window) = 0;
  virtual ~Screen(){};
};

class TitleScreen : public Screen {
private:
  sf::Font font;
  sf::Text titleText;
  sf::Text inputPromptText;
  sf::Text userInputText;
  sf::String userInput;
  sf::RenderWindow *window;

  // For blinking cursor
  std::string cursor;
  sf::Clock cursorClock;
  const float blink_interval = 0.5;

  // For window sizing

  int width;
  int height;

  // Audio
  sf::SoundBuffer buffer;
  sf::Sound typeSound;

  sf::SoundBuffer buffer1;
  sf::Sound characterLimitSound;

  sf::Music music;

public:
  TitleScreen(int _width, int _height);
  ~TitleScreen(){};

  std::string getUsername();
  void handleEvent(sf::Event event, Gamestate &state, std::string &username);
  void update();
  void render(sf::RenderWindow &window) override;
};

class GameScreen : public Screen {
private:
  Board *board;
  // std::unordered_map<std::string, sf::Texture> buttonTextures;
  // sf::Sprite win;
  // sf::Sprite lose;
  // sf::Sprite happy;
  // sf::Sprite debug;
  // sf::Sprite pause;
  // sf::Sprite play;
  // sf::Sprite leader;

  // // For timer
  // std::unordered_map<int, sf::Texture> numberTextures;
  // int timeElapsed;
  // sf::Sprite hundreth;
  // sf::Sprite tens;
  // sf::Sprite ones;

  // sf::Sprite minuteTen;
  // sf::Sprite minute;
  // sf::Sprite secondTen;
  // sf::Sprite second;

  // // Actual Chrono Timer class
  // Timer timer;
  // int timeTaken;

  // For game logic
  // bool gameOver = false;
  // bool winner = false;
  // bool paused = false;
  // bool debugMode = false;
  // bool enabled = true;

  // int flagsLeft;

  // For window sizing
  int width;
  int height;
  int columns;
  int rows;
  int alienCount;

  // Other MISC.
  std::string *username;

public:
  GameScreen(int _width, int _height, int _columns, int _rows, int _alienCount,
             std::string &_username);
  ~GameScreen();

  void handleEvent(sf::Event event);
  void update();
  void render(sf::RenderWindow &_window) override;
};
