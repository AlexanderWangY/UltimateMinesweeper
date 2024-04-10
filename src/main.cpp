#include "json.hpp"
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

using json = nlohmann::json;

std::mutex mtx;
std::condition_variable cv;
bool messageReceived = false;
std::string receivedMessage;
json receivedjson;

void receiveMessages(sf::TcpSocket &socket) {
  char buffer[1024];
  std::size_t received;

  while (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
    std::string incoming(buffer, received);
    receivedjson = json::parse(incoming);

    std::unique_lock<std::mutex> lock(mtx);
    messageReceived = true;
    cv.notify_one();
  }
}

int main() {
  std::string username;
  std::cout << "What is your username?" << std::endl;
  std::cin >> username;

  sf::TcpSocket socket;
  socket.connect("127.0.0.1", 8080);

  std::thread receiverThread(receiveMessages, std::ref(socket));

  std::thread messageProcessingThread([&]() {
    while (true) {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, [&] { return messageReceived; });
      std::cout << receivedjson["username"] << ": " << receivedjson["data"]
                << std::endl;
      messageReceived = false;
    }
  });

  while (true) {
    std::string message;
    std::getline(std::cin, message);

    if (message == "exit") {
      break;
    }

    if (message == "") {
      continue;
    }

    json j = {{"type", "message"}, {"username", username}, {"data", message}};
    std::string data = j.dump();
    socket.send(data.c_str(), data.size());
  }

  messageProcessingThread.join();
  receiverThread.join();
  return 0;
}
