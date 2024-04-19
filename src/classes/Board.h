#pragma once
#include "../utils/RandomHelper.h"
#include "../utils/SpriteHelper.h"
#include "Cell.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <vector>

class Board {
private:
  std::vector<std::vector<int>> board;
  std::vector<std::vector<Cell>> cellBoard;
  std::unordered_map<int, sf::Texture> textureMap;
  int columns;
  int rows;
  int alienCount;
  bool disabled;

public:
  Board(int _columns, int _rows, int _alienCount);
  void Generate();
  void GenerateValues();
  void disableStatus(bool value);
  void printBoard();
  void render(sf::RenderWindow &window);
};
