#pragma once

#include "../json.hpp"
#include <SFML/Network.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <string>
#include <thread>

using json = nlohmann::json;

class SocketManager {
private:
  std::string serverIP;
  unsigned char port;
  sf::TcpSocket socket;
  std::thread receiverThread;
  std::mutex mtx;
  std::condition_variable cv;
  bool dataReceived;
  json receivedjson;

  void receiveData() {
    char buffer[1024];
    std::size_t received;

    while (socket.receive(buffer, sizeof(buffer), received) ==
           sf::Socket::Done) {
      std::string incoming(buffer, received);
      receivedjson = json::parse(incoming);

      std::unique_lock<std::mutex> lock(mtx);
      dataReceived = true;
      cv.notify_one();
    }
  }

public:
  SocketManager(const std::string &serverIP, const unsigned short &port);

  bool connect();

  void disconnect();

  void sendData(const json &data);

  json getData();
};

// Here is the basis for this class!

// #include "json.hpp"
// #include <SFML/Network.hpp>
// #include <condition_variable>
// #include <mutex>
// #include <string>
// #include <thread>

// using json = nlohmann::json;

// class SocketManager {
// public:
//     SocketManager(const std::string& serverIP, unsigned short serverPort)
//         : serverIP(serverIP), serverPort(serverPort) {}

//     bool connect() {
//         socket.connect(serverIP, serverPort);
//         if (socket.isConnected()) {
//             receiverThread = std::thread(&SocketManager::receiveMessages,
//             this); return true;
//         }
//         return false;
//     }

//     void disconnect() {
//         socket.disconnect();
//         if (receiverThread.joinable())
//             receiverThread.join();
//     }

//     void sendMessage(const json& message) {
//         std::string data = message.dump();
//         socket.send(data.c_str(), data.size());
//     }

//     json getCommand(const std::string& screenName) {
//         std::unique_lock<std::mutex> lock(mtx);
//         cv.wait(lock, [&] { return messageReceived && receivedjson["screen"]
//         == screenName; }); json command = receivedjson["command"];
//         messageReceived = false;
//         return command;
//     }

// private:
//     void receiveMessages() {
//         char buffer[1024];
//         std::size_t received;

//         while (socket.receive(buffer, sizeof(buffer), received) ==
//         sf::Socket::Done) {
//             std::string incoming(buffer, received);
//             receivedjson = json::parse(incoming);

//             std::unique_lock<std::mutex> lock(mtx);
//             messageReceived = true;
//             cv.notify_one();
//         }
//     }

//     std::string serverIP;
//     unsigned short serverPort;
//     sf::TcpSocket socket;
//     std::thread receiverThread;
//     std::mutex mtx;
//     std::condition_variable cv;
//     bool messageReceived = false;
//     json receivedjson;
// };
