#pragma once
#include "../utils/RandomHelper.h"
#include "../utils/SpriteHelper.h"
#include "Cell.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <string>
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

  // Game logiv

  bool disabled;

public:
  Board(int _columns, int _rows, int _alienCount) {
    columns = _columns;
    rows = _rows;
    alienCount = _alienCount;

    for (int y = 0; y < rows; ++y) {
      std::vector<int> entry;
      for (int x = 0; x < columns; ++x) {
        entry.push_back(0);
      }

      board.push_back(entry);
    }

    this->Generate();
    this->GenerateValues();

    textureMap = getCellTextures();
    for (int y = 0; y < rows; ++y) {
      std::vector<Cell> entry;
      for (int x = 0; x < columns; ++x) {

        int tileChoice = rand() % 100;
        sf::Texture tileTextureRandom;

        if (tileChoice <= 20) {
          tileTextureRandom = textureMap[100];
        } else if (tileChoice <= 40) {
          tileTextureRandom = textureMap[101];
        } else if (tileChoice <= 60) {
          tileTextureRandom = textureMap[102];
        } else if (tileChoice <= 80) {
          tileTextureRandom = textureMap[103];
        } else if (tileChoice <= 87) {
          tileTextureRandom = textureMap[104];
        } else if (tileChoice <= 94) {
          tileTextureRandom = textureMap[105];
        } else if (tileChoice <= 99) {
          tileTextureRandom = textureMap[106];
        } else if (tileChoice == 100) {
          tileTextureRandom = textureMap[107];
        }

        Cell cell(board[y][x], x, y, textureMap[board[y][x]], tileTextureRandom,
                  textureMap[0], textureMap[-2]);

        entry.push_back(cell);
      }

      cellBoard.push_back(entry);
    }

    for (int y = 0; y < rows; ++y) {
      for (int x = 0; x < columns; ++x) {
        cellBoard[y][x].setNearbyCells(cellBoard);
      }
    }
  }

  void Generate() {
    int generated = 0;

    while (generated != alienCount) {
      int y = getRandomNumber(0, columns - 1);
      int x = getRandomNumber(0, rows - 1);

      if (board[x][y] != -1) {
        board[x][y] = -1;
        ++generated;
      }
    }
  }

  void GenerateValues() {
    int xTransform[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int yTransform[] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for (int y = 0; y < rows; ++y) {
      for (int x = 0; x < columns; ++x) {
        if (board[y][x] == -1) {
          continue;
        }

        int count = 0;

        for (int t = 0; t < 8; ++t) {
          int newX = x + xTransform[t];
          int newY = y + yTransform[t];

          if (newX < 0 || newY < 0 || newX > columns - 1 || newY > rows - 1) {
            continue;
          } else {
            if (board[newY][newX] == -1) {
              ++count;
            }
          }
        }

        board[y][x] = count;
      }
    }
  }

  void disableStatus(bool value) {
    if (value) {
      disabled = false;
    } else {
      disabled = true;
    }
  }

  void printBoard() {
    for (std::vector<int> x : board) {
      for (int val : x) {
        std::cout << val << " ";
      }
      std::cout << std::endl;
    }
  }

  void render(sf::RenderWindow &window) {
    for (std::vector<Cell> row : cellBoard) {
      for (Cell cell : row) {
        cell.render(window);
      }
    }
  }
};
