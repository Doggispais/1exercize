#include "../common/httplib.h"
#include "../common/student.h"
#include <iostream>

int main() {
  httplib::Server svr;

  // Загрузка данных из файлов
  auto students1 = readStudentsFromFile("student_file_1.txt");
  auto students2 = readStudentsFromFile("student_file_2.txt");
  auto merged = mergeStudents(students1, students2);

  // Обработчик GET запроса
  svr.Get("/students",
          [&merged](const httplib::Request &, httplib::Response &res) {
            res.set_content(serializeStudents(merged), "text/plain");
          });

  std::cout << "Server started on port 8080\n";
  svr.listen("0.0.0.0", 8080);
  return 0;
}