#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Screen {
public:
  virtual void handleEvent(const sf::Event &event) = 0;
  virtual void update() = 0;
  virtual void render(sf::RenderWindow &window) = 0;
  virtual ~Screen(){};
};

class SelectionScreen : public Screen {
private:
  sf::Font font;
  sf::Text titleText;
  sf::Text subText;
  sf::Text singleText;
  sf::Text rankedText;

  // For window sizing
  int width;
  int height;

public:
  SelectionScreen(int _width, int _height);

  void handleEvent(const sf::Event &event) override;
  void update() override;
  void render(sf::RenderWindow &window) override;
};
