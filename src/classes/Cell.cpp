#include "Cell.h"
#include <iostream>
#include <ostream>

Cell::Cell(int _type, int _x, int _y, sf::Texture &_value, sf::Texture &_tile,
           sf::Texture &_under, sf::Texture &_flag) {
  tile.setTexture(_tile);
  under.setTexture(_under);
  flag.setTexture(_flag);
  value.setTexture(_value);
  pos.x = _x;
  pos.y = _y;
  state.disabled = false;
  state.flagged = false;
  state.revealed = false;
  state.debug = false;
  type = _type;
  tile.setPosition(32.f * pos.x, 32.f * pos.y);
  under.setPosition(pos.x * 32.f, pos.y * 32.f);
  value.setPosition(pos.x * 32.f, pos.y * 32.f);
  flag.setPosition(pos.x * 32.f, pos.y * 32.f);
}

bool Cell::withinBounds(int x, int y) {
  return tile.getGlobalBounds().contains(x, y);
}

void Cell::setNearbyCells(std::vector<std::vector<Cell>> &board) {
  for (int dy = -1; dy <= 1; ++dy) {
    for (int dx = -1; dx <= 1; ++dx) {
      // Skip the current cell itself
      if (dx == 0 && dy == 0)
        continue;

      // Calculate coordinates of the neighboring cell
      int nx = pos.x + dx;
      int ny = pos.y + dy;

      // Check if the neighboring cell is within the bounds of the board
      if (nx >= 0 && nx < board[0].size() && ny >= 0 && ny < board.size()) {
        nearbyCells.push_back(&board[ny][nx]);
      }
    }
  }
}

void Cell::render(sf::RenderWindow &window) {
  window.draw(under);

  if (state.debug && type == -1) {
    window.draw(value);
  } else if (state.debug && type != -1) {
    window.draw(tile);
  }

  if (state.revealed && !state.disabled) {
    window.draw(value);
  }

  if (!state.revealed && !state.debug) {
    window.draw(tile);
  }

  if (!state.revealed && state.flagged) {
    window.draw(flag);
  }
}

int Cell::Reveal() { // 0 - nothing, 1 - success, -1 -  ALIEN!
  if (state.flagged) {
    return 1;
  }

  if (type == -1) {
    state.revealed = true;
    return -1;
  }

  if (type == 0 && !state.revealed) {
    state.revealed = true;

    for (Cell *c : nearbyCells) {
      c->Reveal();
    }
  } else {
    state.revealed = true;
  }

  return 0;
}

bool Cell::isAlien() {
  if (type == -1) {
    return true;
  }
  return false;
}

void Cell::toggleFlag() { state.flagged = !state.flagged; }
bool Cell::isFlagged() { return state.flagged; }

void Cell::setDebug(bool value) { state.debug = true; }
