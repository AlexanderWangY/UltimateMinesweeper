#include "../utils/TextHelper.h"
#include "Screen.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <cctype>
#include <iostream>
#include <string>

TitleScreen::TitleScreen(int _width, int _height) {
  font.loadFromFile("./files/font.ttf");
  width = _width;
  height = _height;

  // Setting up Title Text
  titleText.setFont(font);
  titleText.setString("Welcome to ALIENSWEEPER");
  titleText.setCharacterSize(24);
  titleText.setFillColor(sf::Color::Green);
  titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  setText(titleText, width / 2, height / 2 - 150);

  // Setting up Input Prompt Text
  inputPromptText.setFont(font);
  inputPromptText.setString("Enter your name:");
  inputPromptText.setCharacterSize(20);
  inputPromptText.setFillColor(sf::Color::White);
  setText(inputPromptText, width / 2, height / 2 - 75);

  userInputText.setFont(font);
  userInputText.setString("|");
  userInputText.setCharacterSize(18);
  userInputText.setFillColor(sf::Color::Yellow);
  userInputText.setStyle(sf::Text::Bold);
  setText(userInputText, width / 2, height / 2 - 45);

  cursor = "|";
  cursorClock.restart();
}

void TitleScreen::handleEvent(sf::Event event, Gamestate &state,
                              std::string &username) {

  // Check if event is user entering text!
  if (event.type == sf::Event::TextEntered) {
    if (event.text.unicode < 128) {
      if (event.text.unicode == '\r' && userInput.getSize() > 0) {
        username = userInput;
        state = Gamestate::Game;
      } else if (event.text.unicode == '\b' && userInput.getSize() != 0) {
        userInput.erase(userInput.getSize() - 1); // Remove last character
      } else if (userInput.getSize() < 10 && event.text.unicode != '\b' &&
                 event.text.unicode != '\r' &&
                 std::isalpha(static_cast<char>(event.text.unicode))) {
        // Convert entered character to uppercase and append it to userInput

        if (userInput.getSize() == 0) {
          userInput += static_cast<char>(
              std::toupper(static_cast<char>(event.text.unicode)));
        } else {
          userInput += static_cast<char>(
              std::tolower(static_cast<char>(event.text.unicode)));
        }
      }

      // Update userInputText with the modified userInput string
      userInputText.setString(userInput);
    }
  }
}

void TitleScreen::update() {
  if (cursorClock.getElapsedTime().asSeconds() >= blink_interval) {
    cursor = cursor == "|" ? "" : "|";
    userInputText.setString(userInput + cursor);
    cursorClock.restart();
  }
}

void TitleScreen::render(sf::RenderWindow &window) {
  window.clear(sf::Color::Black);
  window.draw(titleText);
  window.draw(inputPromptText);
  setTextX(userInputText, width / 2);

  window.draw(userInputText);
}
