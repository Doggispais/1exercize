#ifndef ZMQ_UTILS_H
#define ZMQ_UTILS_H

#include "student.h"
#include <sstream>
#include <string>

std::string serializeStudent(const Student& student) {
	std::ostringstream oss;
	oss << student.id << " "
		<< student.firstName << " "
		<< student.middleName << " "
		<< student.lastName << " "
		<< student.birthDate;
	return oss.str();
}

Student deserializeStudent(const std::string& data) {
	std::istringstream iss(data);
	Student student;
	if (!(iss >> student.id >> student.firstName >> student.middleName >> student.lastName >> student.birthDate)) {
		throw std::runtime_error("Failed to deserialize student data");
	}
	return student;
}

#endif // ZMQ_UTILS_H