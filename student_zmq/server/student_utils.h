#ifndef STUDENT_UTILS_H
#define STUDENT_UTILS_H

#include "../common/student.h"

#include <vector>

std::vector<Student> readStudentsFromFile(const std::string& filename);
std::vector<Student> mergeStudents(const std::vector<Student>& students1, 
								 const std::vector<Student>& students2);

#endif