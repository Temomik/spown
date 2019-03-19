#pragma once
#include "Menu.h"
#include <iostream>
#ifdef _WIN32 | _WIN64
#define CLEAR "cls"
#include <conio.h>
#endif
#ifdef __linux__
#include <termios.h>
#include <curses.h>	
#define CLEAR "clear"
#endif

Menu::Menu() {
	this->pick = 1;
}

Menu::~Menu() {
}

void Menu::push(std::string element) {
	this->elements.push_back(element);
}

int Menu::getPick() {
	return this->pick;
}

int Menu::elementCount() {
	return this->elements.size()-1;
}

std::string Menu::getElem(int ind) {
	return this->elements[ind];
}

void Menu::start() {
	#ifdef __linux__
	initscr();
	cbreak();
	noecho(); /* Set this for interactive programs. */
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	#endif
	this->pick = 1;
	char key = 'k';
	while (1) {
		system(CLEAR); 

		for (int i = 0; i < (int)this->elements.size(); i++) {
			#ifdef __linux__
			printf("\033[0E");
			printf("\033[0F");
			#endif
			printf("%s",this->getElem(i).c_str());
			if (i == this->pick) {
				printf(" <-----%d",this->pick);
			}
			printf("\n");
			// std::cout << std::endl;
			// #endif
		}
		// printf("\n\033[0E\033[0F%d",pick);		
		rewind(stdin);
		
		#ifdef _WIN32 | _WIN64
		key = _getch();
		#endif
		
		#ifdef __linux__
		key = getch();
		#endif

		switch (key) {
		case 13:
			return;
		#ifdef _WIN32 | _WIN64
		case 72:
		#endif
		#ifdef __linux__
		case 'w':
		#endif
			if (this->pick > 1) {
				this->pick--;
			}
			else {
				this->pick = this->elements.size() - 1;
			}
			break;
		#ifdef _WIN32 | _WIN64
		case 80:
		#endif
		#ifdef __linux__
		case 's':
		#endif
			if (this->pick + 1 < this->elements.size()) {
				this->pick++;
			}
			else {
				this->pick = 1;
			}
			break;
		default:
			break;
		}

	}
}
