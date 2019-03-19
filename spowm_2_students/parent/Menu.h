#pragma once
#include <string>
#include <vector>

class Menu {
	std::vector<std::string> elements;
	int pick;
public:
	Menu ();
	~Menu ();
	void push(std::string element);
	int getPick();
	int elementCount();
	std::string getElem(int ind);
	void start();
};
