#include "Student.h"
#ifdef __linux__
#include <ncurses.h>
#endif

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		return 1;
	}
	#ifdef __linux__
		// initscr();
		// noecho();
	#endif
	Student student;
	student.startMenu(argv[1]);
	#ifdef _WIN32 | _WIN64
		// system("cls");
	#endif
	#ifdef __linux__
	endwin();
	initscr();
	noecho();
		// system("clear");
	endwin();
	#endif
	return 0;
}
