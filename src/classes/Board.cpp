#include "Board.h"
#include "Cell.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <string>
#include <vector>

Board::Board(int _columns, int _rows, int _alienCount) {
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
      int num = getRandomNumber(0, 100);
      sf::Texture *test = nullptr;

      if (num <= 35) {
        test = &textureMap[100];
      } else if (num <= 65) {
        test = &textureMap[101];
      } else if (num <= 85) {
        test = &textureMap[102];
      } else if (num <= 92) {
        test = &textureMap[103];
      } else if (num <= 95) {
        test = &textureMap[104];
      } else if (num <= 97) {
        test = &textureMap[105];
      } else if (num <= 99) {
        test = &textureMap[106];
      } else if (num == 100) {
        test = &textureMap[107];
      }

      Cell newCell(board[y][x], x, y, textureMap[board[y][x]], *test,
                   textureMap[0], textureMap[-2]);
      entry.push_back(newCell);
    }

    cellBoard.push_back(entry);
  }

  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < columns; ++x) {
      cellBoard[y][x].setNearbyCells(cellBoard);
    }
  }
}

void Board::Generate() {
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

void Board::GenerateValues() {
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

int Board::handleClick(int x, int y) {
  if (paused) {
    return 500;
  }

  bool cellFound = false;
  for (std::vector<Cell> &row : cellBoard) {
    for (Cell &c : row) {
      if (c.withinBounds(x, y)) {
        int result = c.Reveal();

        return result;
      }
    }
  }

  return 404;
}

int Board::handleFlag(int x, int y) {
  if (paused) {
    return 500;
  }

  bool cellFound = false;
  for (std::vector<Cell> &row : cellBoard) {
    for (Cell &c : row) {
      if (c.withinBounds(x, y)) {
        c.toggleFlag();

        if (c.isFlagged()) {
          return 0;
        } else {
          return 1;
        }
      }
    }
  }

  return 404;
}

void Board::toggleDebug() {
  debug = !debug;
  for (std::vector<Cell> &row : cellBoard) {
    for (Cell &c : row) {
      c.setDebug(debug);
    }
  }
}

void Board::setDebug(bool value) {
  debug = value;
  for (std::vector<Cell> &row : cellBoard) {
    for (Cell &c : row) {
      c.setDebug(debug);
    }
  }
}

void Board::togglePause() {
  paused = !paused;
  for (std::vector<Cell> &row : cellBoard) {
    for (Cell &c : row) {
      c.setPause(paused);
    }
  }
}

void Board::setPause(bool value) {
  paused = value;
  for (std::vector<Cell> &row : cellBoard) {
    for (Cell &c : row) {
      c.setPause(paused);
    }
  }
}

void Board::render(sf::RenderWindow &window) {
  for (std::vector<Cell> row : cellBoard) {
    for (Cell cell : row) {
      cell.render(window);
    }
  }
}

bool Board::checkWinner() {
  int numOfRevealed = columns * rows - alienCount;
  for (auto &row : cellBoard) {
    for (Cell &c : row) {
      if (c.isRevealed()) {
        numOfRevealed--;
      }
    }
  }

  if (numOfRevealed == 0) {
    return true;
  }

  return false;
}

void Board::flagAll() {
  for (auto &row : cellBoard) {
    for (Cell &c : row) {
      if (c.isAlien()) {
        c.setFlag(true);
      }
    }
  }
}
