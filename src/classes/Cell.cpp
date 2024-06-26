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
  // Always draw the under texture
  window.draw(under);

  // If in debug mode, draw value or tile based on type
  if (state.debug && !state.revealed) {
    if (type == -1) {
      window.draw(value);
    } else {
      window.draw(tile);
    }
  }
  // If revealed and not disabled, draw value
  else if (state.revealed && !state.disabled) {
    window.draw(value);
  }
  // If not revealed and not in debug mode, draw tile
  else if (!state.revealed && !state.disabled) {
    window.draw(tile);
  }

  // If flagged, draw flag on top
  if (state.flagged && !state.disabled) {
    window.draw(flag);
  }
}

int Cell::Reveal() { // 0 - nothing, 1 - success, -1 - ALIEN!
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

bool Cell::isRevealed() { return state.revealed; }

void Cell::toggleFlag() { state.flagged = !state.flagged; }
void Cell::setFlag(bool value) { state.flagged = value; }
bool Cell::isFlagged() { return state.flagged; }

void Cell::setDebug(bool value) { state.debug = value; }
bool Cell::isDebug() { return state.debug; }

void Cell::setPause(bool value) { state.disabled = value; }
