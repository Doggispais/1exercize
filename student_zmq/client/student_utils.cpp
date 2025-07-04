#include "../common/student.h"
#include <vector>
#include <algorithm>
#include <iostream>

void sortStudents(std::vector<Student>& students) {
	std::sort(students.begin(), students.end());
}

void displayStudents(const std::vector<Student>& students) {
	for (const auto& student : students) {
		std::cout << student.id << " "
				  << student.firstName << " "
				  << student.lastName << " "
				  << student.birthDate << std::endl;
	}
}