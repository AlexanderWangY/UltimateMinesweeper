#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

void setText(sf::Text &text, float x, float y) {
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f,
                 textRect.top + textRect.height / 2.0f);
  text.setPosition(sf::Vector2f(x, y));
}

void setTextX(sf::Text &text, float x) {
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
  text.setPosition(sf::Vector2f(x, text.getPosition().y));
}
