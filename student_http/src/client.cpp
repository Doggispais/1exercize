#include "../common/httplib.h"
#include "../common/student.h"
#include <algorithm>
#include <iostream>

int main() {
  httplib::Client cli("localhost", 8080);

  // Получение данных от сервера
  auto res = cli.Get("/students");
  if (res && res->status == 200) {
    auto students = deserializeStudents(res->body);

    // Сортировка по ФИО
    std::sort(students.begin(), students.end(),
              [](const Student &a, const Student &b) {
                return (a.lastName + a.firstName) < (b.lastName + b.firstName);
              });

    // Вывод
    std::cout << "Final sorted list:\n";
    for (const auto &s : students) {
      std::cout << s.toString() << "\n";
    }
  } else {
    std::cerr << "Failed to get students data\n";
  }

  return 0;
}