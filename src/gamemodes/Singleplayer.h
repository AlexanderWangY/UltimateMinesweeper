#pragma once
struct Config {
  int columns;
  int rows;
  int alienCount;
};

bool playSingleplayer(Config &config);
