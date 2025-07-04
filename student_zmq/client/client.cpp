#include "../common/student.h"
#include "../common/zmq_utils.h"
#include "../libs/zmq.hpp"
#include "student_utils.cpp"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void runClient() {
  zmq::context_t context(1);
  zmq::socket_t subscriber(context, ZMQ_SUB);

  try {
    subscriber.connect("tcp://127.0.0.1:5556");
    subscriber.set(zmq::sockopt::subscribe, "");
    subscriber.set(zmq::sockopt::rcvtimeo, 5000); // Таймаут чтобы подключиться

    std::cout << "Connected to server. Waiting for data..." << std::endl;

    std::vector<Student> students;
    bool receiving = true;

    while (receiving) {
      zmq::message_t message;
      if (subscriber.recv(message)) {
        std::string msg_str(static_cast<char *>(message.data()),
                            message.size());

        if (msg_str == "END") {
          receiving = false;
          break;
        }

        // Парсинг сообщения
        size_t pos1 = msg_str.find('|');
        size_t pos2 = msg_str.find('|', pos1 + 1);
        size_t pos3 = msg_str.find('|', pos2 + 1);

        if (pos1 != std::string::npos && pos2 != std::string::npos &&
            pos3 != std::string::npos) {

          Student s;
          s.id = std::stoi(msg_str.substr(0, pos1));
          s.firstName = msg_str.substr(pos1 + 1, pos2 - pos1 - 1);
          s.lastName = msg_str.substr(pos2 + 1, pos3 - pos2 - 1);
          s.birthDate = msg_str.substr(pos3 + 1);

          students.push_back(s);
          std::cout << "Received: " << s.id << " " << s.firstName << " " << s.lastName << " " << s.birthDate << std::endl;
        }
      } else {
        std::cerr << "Timeout: no data received" << std::endl;
        break;
      }
    }

    // Сортировка и вывод
    std::sort(students.begin(), students.end(),
              [](const Student &a, const Student &b) { return a.id < b.id; });

    std::cout << "\nFinal sorted list (" << students.size() << " students):\n";
    for (const auto &s : students) {
      std::cout << s.id << " " << s.firstName << " " << s.lastName << " " << s.birthDate << std::endl;
    }

  } catch (const zmq::error_t &e) {
    std::cerr << "ZMQ error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

int main() {
  std::cout << "Client starting..." << std::endl;
  runClient();
  return 0;
}