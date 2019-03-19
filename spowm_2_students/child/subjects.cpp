#include "subjects.h"

std::ofstream & operator<<(std::ofstream & out, Subjects & subject) {
	for (int i = 0; i < 5; i++) {
		out << subject.count[i] << std::endl;
	}
	return out;
}

std::ifstream & operator>>(std::ifstream & in, Subjects & subject) {
	for (int i = 0; i < 5; i++) {
		in >> subject.count[i];
	}
	return in;
}

int Subjects::get(int ind) {
	return this->count[ind];
}

bool Subjects::
CheckAvailableCount(int index) {
	return (this->count[index] > 0) ? true : false;
}
void Subjects::setSubject(int ind, int count) {
	this->count[ind] = count;
}
void Subjects::incSubjectCount(int ind, int count) {
	this->setSubject(ind, this->count[ind] + count);
}
bool Subjects::CheckAvailableSubject(int index, int labsNum) {
	return (this->count[index] >= labsNum && labsNum != 0) ? true : false;
}
