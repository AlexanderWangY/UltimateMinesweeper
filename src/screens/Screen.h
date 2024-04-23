#pragma once
#include "../classes/Board.h"
#include "../utils/Gamestate.h"
#include "../utils/TimerUtility.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <unordered_map>

class Screen {
public:
  virtual void render(sf::RenderWindow &window) = 0;
  virtual ~Screen(){};
};
class GameScreen : public Screen {
private:
  Board *board;
  std::unordered_map<int, sf::Texture> buttonTextures;
  sf::Sprite win;
  sf::Sprite lose;
  sf::Sprite happy;
  sf::Sprite debug;
  sf::Sprite pause;
  sf::Sprite play;
  sf::Sprite leader;
  sf::Sprite mute;
  sf::Sprite unmute;

  // For timer
  int timeElapsed;
  sf::Sprite hundreth;
  sf::Sprite tens;
  sf::Sprite ones;

  sf::Sprite minuteTen;
  sf::Sprite minute;
  sf::Sprite secondTen;
  sf::Sprite second;

  // Actual Chrono Timer class
  Timer timer;
  int timeTaken;

  bool gameOver = false;
  bool winner = false;
  bool paused = false;

  int flagsLeft;

  // For window sizing
  int width;
  int height;
  int columns;
  int rows;
  int alienCount;

  // Other MISC.
  std::string *username;

  // Audio
  sf::SoundBuffer buffer;
  sf::Sound loseSound;

  sf::SoundBuffer buffer1;
  sf::Sound winSound;

  sf::Music music;
  sf::Music winMusic;

  bool muted = false;

public:
  GameScreen(int _width, int _height, int _columns, int _rows, int _alienCount,
             std::string &_username);
  ~GameScreen();

  void startGame();

  void handleEvent(sf::Event event);
  void update();
  void reset();
  void render(sf::RenderWindow &_window) override;

  // For game handling
  void setPause(bool value);
  void setDebug(bool value);
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
  const float blink_interval = .5;

  // For window sizing

  int width;
  int height;

  int opacity = 255;

  bool entered = false;

  // Audio
  sf::SoundBuffer buffer;
  sf::Sound typeSound;

  sf::SoundBuffer buffer1;
  sf::Sound characterLimitSound;

  sf::Music music;
  sf::Music intro;

public:
  TitleScreen(int _width, int _height);
  ~TitleScreen(){};

  std::string getUsername();
  void handleEvent(sf::Event event, Gamestate &state, std::string &username,
                   GameScreen &game);
  void update(Gamestate &state, GameScreen &game);
  void render(sf::RenderWindow &window) override;
};

class Leaderboard : public Screen {
private:
  sf::Font font;
  sf::Text titleText;
  sf::Text leaderboardText;
  sf::RenderWindow *window;

  // For window sizing

  int width;
  int height;

public:
  Leaderboard(int _width, int _height);
  ~Leaderboard(){};

  void render(sf::RenderWindow &_window) override;
};
