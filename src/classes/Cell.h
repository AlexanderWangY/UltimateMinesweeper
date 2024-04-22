#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

struct Position {
  int x;
  int y;
};

struct State {
  bool revealed;
  bool flagged;
  bool disabled;
  bool debug;
};

class Cell {
private:
  std::vector<Cell *> nearbyCells;
  sf::Sprite tile;
  sf::Sprite under;
  sf::Sprite value;
  sf::Sprite flag;
  int type; // 0 - Nothing, 1, 2, 3, -1 - BOMB
  Position pos;
  State state;

public:
  Cell(int _type, int _x, int _y, sf::Texture &_value, sf::Texture &_tile,
       sf::Texture &_under, sf::Texture &_flag);
  bool withinBounds(int x, int y);
  void setNearbyCells(std::vector<std::vector<Cell>> &board);
  void render(sf::RenderWindow &window);

  int Reveal();
  bool isAlien();
  void toggleFlag();
  bool isRevealed();

  void setDebug(bool value);
  bool isDebug();
  void setPause(bool value);
  bool isPause(bool value);
  void setFlag(bool value);
  bool isFlagged();
};
