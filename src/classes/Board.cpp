#include "Board.h"
#include <iostream>
#include <string>

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

  std::vector<int> tileChoices = {100, 101, 102, 103, 104, 105, 106, 107};
  std::vector<int> tileProbabilities = {20, 20, 20, 20, 7, 7, 5, 1};

  for (int y = 0; y < rows; ++y) {
    std::vector<Cell> entry;
    for (int x = 0; x < columns; ++x) {
      int tileChoice = rand() % 100;
      int tileIndex = 0;
      int cumulativeProbability = 0;

      for (int i = 0; i < tileProbabilities.size(); ++i) {
        cumulativeProbability += tileProbabilities[i];
        if (tileChoice < cumulativeProbability) {
          tileIndex = i;
          break;
        }
      }

      sf::Texture tileTextureRandom = textureMap[tileChoices[tileIndex]];

      Cell cell(board[y][x], x, y, textureMap[board[y][x]], textureMap[101],
                textureMap[0], textureMap[-2]);
      entry.push_back(cell);
    }
    cellBoard.push_back(entry);
  }
  textureMap = getCellTextures();

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

void Board::disableStatus(bool value) {
  if (value) {
    disabled = false;
  } else {
    disabled = true;
  }
}

void Board::printBoard() {
  for (std::vector<int> x : board) {
    for (int val : x) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}

void Board::render(sf::RenderWindow &window) {
  for (std::vector<Cell> row : cellBoard) {
    for (Cell cell : row) {
      cell.render(window);
    }
  }
}