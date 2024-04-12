#include "SocketManager.h"
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

SocketManager::SocketManager(const std::string &serverIP,
                             const unsigned short &port)
    : serverIP(serverIP), port(port) {}

bool SocketManager::connect() {
  if (socket.connect(serverIP, port)) {
    receiverThread = std::thread(&SocketManager::receiveData, this);
    return true;
  }
  return false;
}

void SocketManager::disconnect() {
  socket.disconnect();
  if (receiverThread.joinable()) {
    receiverThread.join();
  }
}

void SocketManager::sendData(const json &data) {
  std::string send = data.dump();
  socket.send(send.c_str(), send.size());
}

json SocketManager::getData() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [&] { return dataReceived; });
  dataReceived = false;
  return receivedjson;
}
