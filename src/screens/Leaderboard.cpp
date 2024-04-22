
#include "../utils/LeaderboardHelper.h"
#include "../utils/TextHelper.h"
#include "Screen.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

Leaderboard::Leaderboard(int _width, int _height) {
  font.loadFromFile("./files/font.ttf");
  width = _width;
  height = _height;

  titleText.setFont(font);
  titleText.setString("LEADERBOARD");
  titleText.setCharacterSize(20);
  titleText.setFillColor(sf::Color::Green);
  titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  setText(titleText, width / 2, height / 2 - 120);

  leaderboardText.setFont(font);
  leaderboardText.setString(leaderString());
  leaderboardText.setCharacterSize(18);
  leaderboardText.setFillColor(sf::Color::Green);
  leaderboardText.setStyle(sf::Text::Bold);
  setText(leaderboardText, width / 2, height / 2 + 20);
}

void Leaderboard::render(sf::RenderWindow &window) {
  window.draw(titleText);
  window.draw(leaderboardText);
}
