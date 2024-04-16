#pragma once
#include "../utils/Gamestate.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <string>

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

public:
  TitleScreen(int _width, int _height);
  ~TitleScreen(){};

  std::string getUsername();
  void handleEvent(sf::Event event, Gamestate &state, std::string &username);
  void update();
  void render(sf::RenderWindow &window) override;
};
