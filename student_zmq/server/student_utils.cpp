#include "student_utils.h"
#include "../common/student.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<Student> readStudentsFromFile(const std::string &filename) {
  std::vector<Student> students;
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filename);
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    // Удаляем лишние пробелы
    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);

    std::istringstream iss(line);
    Student student;
    std::vector<std::string> parts;
    std::string part;

    // Разбиваем строку на части
    while (iss >> part) {
      parts.push_back(part);
    }

    // Анализируем количество частей
    if (parts.size() < 4) {
      std::cerr << "Not enough data in line: " << line << std::endl;
      continue;
    }

    try {
      student.id = std::stoi(parts[0]);
      student.firstName = parts[1];

      // Определяем формат
      if (parts.size() == 4) {
        // Формат: ID Имя Фамилия Дата
        student.middleName = "";
        student.lastName = parts[2];
        student.birthDate = parts[3];
      }else {
        std::cerr << "Unexpected format in line: " << line << std::endl;
        continue;
      }

      students.push_back(student);
      std::cout << "Parsed: " << student.id << " " << student.firstName << " " << student.lastName << " "	<< student.birthDate << std::endl;

    } catch (const std::exception &e) {
      std::cerr << "Error parsing line '" << line << "': " << e.what() << std::endl;
		
    }
  }

  if (students.empty()) {
    std::cerr << "Warning: no valid students found in file: " << filename << std::endl;
  }

  return students;
}

std::vector<Student> mergeStudents(const std::vector<Student> &students1,
                                   const std::vector<Student> &students2) {
  std::vector<Student> merged = students1;

  for (const auto &student : students2) {
    if (std::find(merged.begin(), merged.end(), student) == merged.end()) {
      merged.push_back(student);
    }
  }

  return merged;
}