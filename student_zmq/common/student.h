#ifndef STUDENT_H
#define STUDENT_H

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

struct Student {
  int id;
  std::string firstName;
  std::string middleName;
  std::string lastName;
  std::string birthDate;

  void print() const {
    std::cout << id << " " << firstName << " " << middleName << " " << lastName << " " << birthDate << std::endl;
  }

  // Для сравнения студентов
  bool operator==(const Student &other) const {
    return firstName == other.firstName && middleName == other.middleName &&
           lastName == other.lastName && birthDate == other.birthDate;
  }

  // Для сортировки
  bool operator<(const Student &other) const {
    if (lastName != other.lastName)
      return lastName < other.lastName;
    if (firstName != other.firstName)
      return firstName < other.firstName;
    return middleName < other.middleName;
  }
};

#endif // STUDENT_H