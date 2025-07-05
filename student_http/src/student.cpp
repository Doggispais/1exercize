#include "../common/student.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>

std::string Student::toString() const {
  std::ostringstream oss;
  oss << id << " " << lastName << " " << firstName << " " << std::setfill('0')
      << std::setw(2) << birthDate.tm_mday << "." << std::setfill('0')
      << std::setw(2) << (birthDate.tm_mon + 1) << "."
      << (birthDate.tm_year + 1900);
  return oss.str();
}

Student Student::fromString(const std::string &str) {
  std::istringstream iss(str);
  Student s;
  std::string dateStr;

  iss >> s.id >> s.lastName >> s.firstName >> dateStr;

  std::memset(&s.birthDate, 0, sizeof(s.birthDate));
  char dot;
  std::istringstream dateIss(dateStr);
  dateIss >> s.birthDate.tm_mday >> dot >> s.birthDate.tm_mon >> dot >>
      s.birthDate.tm_year;

  s.birthDate.tm_mon -= 1;
  s.birthDate.tm_year -= 1900;

  return s;
}

bool Student::validateDate(const std::string &dateStr) {
  std::tm tm = {};
  std::istringstream iss(dateStr);
  iss >> std::get_time(&tm, "%d.%m.%Y");
  return !iss.fail();
}

std::vector<Student> readStudentsFromFile(const std::string &filename) {
  std::vector<Student> students;
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    if (!line.empty()) {
      try {
        students.push_back(Student::fromString(line));
      } catch (...) {
      }
    }
  }

  return students;
}

std::vector<Student> mergeStudents(const std::vector<Student> &list1,
                                   const std::vector<Student> &list2) {
  std::vector<Student> merged = list1;

  // Добавляем студентов из второго списка, если их нет в первом
  for (const auto &student2 : list2) {
    bool exists = false;
    for (const auto &student1 : list1) {
      if (student1.lastName == student2.lastName &&
          student1.firstName == student2.firstName &&
          std::mktime(const_cast<std::tm *>(&student1.birthDate)) ==
              std::mktime(const_cast<std::tm *>(&student2.birthDate))) {
        exists = true;
        break;
      }
    }
    if (!exists) {
      merged.push_back(student2);
    }
  }

  return merged;
}

std::string serializeStudents(const std::vector<Student> &students) {
  std::ostringstream oss;
  for (const auto &s : students) {
    oss << s.toString() << "\n";
  }
  return oss.str();
}

std::vector<Student> deserializeStudents(const std::string &data) {
  std::vector<Student> students;
  std::istringstream iss(data);
  std::string line;

  while (std::getline(iss, line)) {
    if (!line.empty()) {
      students.push_back(Student::fromString(line));
    }
  }

  return students;
}