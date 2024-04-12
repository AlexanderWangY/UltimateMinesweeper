#include "json.hpp"
#include "network/SocketManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <bits/c++config.h>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

int main() {
  std::string username;
  std::cout << "What is your username?" << std::endl;
  std::cin >> username;

  SocketManager sock("127.0.0.1", 8080);

  if (sock.connect()) {
    std::cout << "Connected to server!\n";
  } else {
    std::cout << "Error connecting\n";
  }

  while (true) {
  }
  return 0;
}
