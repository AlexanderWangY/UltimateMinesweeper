#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

inline bool isClicked(sf::Sprite &sprite, int x, int y) {
  sf::FloatRect bounds = sprite.getGlobalBounds();

  return bounds.contains(x, y);
}

inline std::unordered_map<int, sf::Texture> getCellTextures() {
  std::unordered_map<int, sf::Texture> textures;

  textures[-2].loadFromFile("./files/images/flag.png");
  textures[-1].loadFromFile("./files/images/alien.png");
  textures[0].loadFromFile("./files/images/space.png");
  textures[1].loadFromFile("./files/images/1.png");
  textures[2].loadFromFile("./files/images/2.png");
  textures[3].loadFromFile("./files/images/3.png");
  textures[4].loadFromFile("./files/images/4.png");
  textures[5].loadFromFile("./files/images/5.png");
  textures[6].loadFromFile("./files/images/6.png");
  textures[7].loadFromFile("./files/images/7.png");
  textures[8].loadFromFile("./files/images/8.png");

  textures[100].loadFromFile("./files/images/space1.png");
  textures[101].loadFromFile("./files/images/space2.png");
  textures[102].loadFromFile("./files/images/space3.png");
  textures[103].loadFromFile("./files/images/space5.png");
  textures[104].loadFromFile("./files/images/space4.png");
  textures[105].loadFromFile("./files/images/space7.png");
  textures[106].loadFromFile("./files/images/space6.png");
  textures[107].loadFromFile("./files/images/space8.png");

  return textures;
}

inline std::unordered_map<int, sf::Texture> getBoardTextures() {
  std::unordered_map<int, sf::Texture> textures;

  for (int x = 0; x < 11; ++x) {
    sf::IntRect textureRect(21 * x, 0, 21, 32);
    sf::Texture newTexture;
    newTexture.loadFromFile("./files/images/digits.png");
    newTexture.loadFromImage(newTexture.copyToImage(), textureRect);
    textures[x] = newTexture;
  }

  textures[12].loadFromFile("./files/images/happy.png");
  textures[13].loadFromFile("./files/images/win.png");
  textures[14].loadFromFile("./files/images/lose.png");
  textures[15].loadFromFile("./files/images/pause.png");
  textures[16].loadFromFile("./files/images/play.png");
  textures[17].loadFromFile("./files/images/debug.png");
  textures[18].loadFromFile("./files/images/leader.png");
  textures[19].loadFromFile("./files/images/mute.png");
  textures[20].loadFromFile("./files/images/unmute.png");

  return textures;
}
