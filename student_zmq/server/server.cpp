#include "../common/student.h"
#include "../common/zmq_utils.h"
#include "../libs/zmq.hpp"
#include "student_utils.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void runServer() {

  try {
    //Загрузка данных из файлов
    auto students1 = readStudentsFromFile("student_file_1.txt");
    auto students2 = readStudentsFromFile("student_file_2.txt");

    //Объединение списков студентов
    auto mergedStudents = mergeStudents(students1, students2);

    //Инициализация ZeroMQ
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://127.0.0.1:5556");

    std::cout << "Waiting for subscribers..." << std::endl; // Чтобы клиент успел подключиться
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Отправка всех студентов
    for (const auto &student : mergedStudents) {
      std::string serialized = std::to_string(student.id) + "|" + student.firstName + "|" + student.middleName + "|" + student.lastName + "|" + student.birthDate;

      zmq::message_t message(serialized.begin(), serialized.end());
      publisher.send(message, zmq::send_flags::none);
      std::cout << "Sent: " << serialized << std::endl;
    }

    // Задержка перед завершением
    std::cout << "Server waiting for 30 seconds before exit..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(30));

    // Отправка сообщения о завершении передачи
    std::cout << "Server comlete..." << std::endl;

    zmq::message_t endMsg("END", 3);
    publisher.send(endMsg, zmq::send_flags::none);

  } catch (const std::exception &e) {
    std::cerr << "Server error: " << e.what() << std::endl;
  }
}

int main() {
  runServer();
  return 0;
}