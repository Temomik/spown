#pragma once
#include <fstream>

class Subjects {
	int count[5];
public:
	Subjects() {};
	friend std::ofstream& operator<< (std::ofstream& out, Subjects& subject);
	int get(int ind);
	bool CheckAvailableCount(int index);
	void setSubject(int ind, int count);
	void incSubjectCount(int ind, int count);
	bool CheckAvailableSubject(int index, int labsNum);
	friend std::ifstream& operator>> (std::ifstream& in, Subjects& subject);
};

