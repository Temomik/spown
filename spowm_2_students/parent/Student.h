#pragma once
#include "Menu.h"
#include <iostream>
#include <stdio.h>

#ifdef _WIN32 | _WIN64
#include <windows.h>
#include <conio.h>
#endif
class Student {
	#ifdef _WIN32 | _WIN64
	const char* path = "child.exe";
	#endif
	#ifdef __linux__
	const char* path = "./child.out";
	#endif
	int labs[5];
	Menu menu, labMenu;
	int enterLabsProcess(int i);
public:
	Student ();
	~Student ();
	void outLabsCount();
	void startMenu(char* eventNamePart);
};