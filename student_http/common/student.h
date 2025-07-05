#ifndef STUDENT_H
#define STUDENT_H

#include <ctime>
#include <string>
#include <vector>

struct Student {
  int id;
  std::string firstName;
  std::string lastName;
  std::tm birthDate;

  std::string toString() const;
  static Student fromString(const std::string &str);
  static bool validateDate(const std::string &dateStr);
};

std::vector<Student> readStudentsFromFile(const std::string &filename);
std::vector<Student> mergeStudents(const std::vector<Student> &list1,
                                   const std::vector<Student> &list2);
std::string serializeStudents(const std::vector<Student> &students);
std::vector<Student> deserializeStudents(const std::string &data);

#endif // STUDENT_H