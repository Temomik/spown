// #include <iostream>
// #include <fstream>
// #include "subjects.h"
// #include <stdio.h>
// #include <stdlib.h>

// #ifdef _WIN32 | _WIN64
// #include <Windows.h>
// #include <conio.h>
// #define CLEAR "cls"
// #define FILE_NAME "lab1.txt"
// #endif
// #ifdef __linux__
// #define CLEAR "clear"
// #define FILE_NAME "lab1.txt"
// #include <sys/wait.h>
// #include <sys/types.h>
// #include <curses.h>
// #include <unistd.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <cstring>
// #include <sys/mman.h>
// #endif

// #define SHARED_MEMORY_OBJECT_NAME "buffMem"
// #define SHARED_MEMORY_OBJECT_SIZE 50


// #include <string>


// #define MAX_BUF 1024
// #ifdef __linux__
// void createMemory(const char* str) {
// 		int shm, mode = 0;
// 			char *addr;
// 		mode = O_CREAT;

// 		if ((shm = shm_open(SHARED_MEMORY_OBJECT_NAME, mode | O_RDWR, 0777)) == -1) {
// 			return;
// 		}

// 		if ( ftruncate(shm, SHARED_MEMORY_OBJECT_SIZE+1) == -1 ) {
// 			return;
// 		}
// 		addr = (char*)mmap(0, SHARED_MEMORY_OBJECT_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
// 		memcpy(addr, str, SHARED_MEMORY_OBJECT_SIZE);
// 		munmap(addr, SHARED_MEMORY_OBJECT_SIZE);
// 		close(shm);
// }
// #endif

int main(int argc, char* argv[]) {
	// system(CLEAR);
	// std::cout << "_______________Child_______________" << std::endl;

	// Subjects subjects;
	// std::ifstream inputFile(FILE_NAME);
	// if (!inputFile.is_open()) {
	// 	#ifdef __linux__
	// 	createMemory("0");
	// 	#endif
	// 	return 0;
	// }
	// inputFile >> subjects;
	// inputFile.close();

	// int labsNum = atoi(argv[1]);
	// int labIndex = atoi(argv[2]);

	// if (!subjects.CheckAvailableCount(labIndex)) {
	// 	#ifdef __linux__
	// 	createMemory("0");
	// 	#endif
	// 	return 0;
	// }

	// if (labsNum == 0){
	// 	#ifdef __linux__
	// 	createMemory("-6");
	// 	#endif
	// 	return -6;
	// }
	// std::cout << subjects.get(labIndex)<< "  " << labsNum << std::endl;

	// if (subjects.get(labIndex) < labsNum) {
	// 	std::cout << "Do you want pass somelabs?(y/n)" << std::endl;
	// 	if ( std::getchar() == 'n') {
	// 		#ifdef __linux__
	// 		createMemory("-5");
	// 		#endif
	// 		return -5;
	// 	} else {
	// 		int tmp;
	// 		std::cout << "enter numb of labs"<< "1-"<< subjects.get(labIndex) << std::endl;
	// 		do {
	// 			std::cin >> tmp;
	// 		} while (tmp <= 0 || tmp > subjects.get(labIndex));
	// 		subjects.incSubjectCount(labIndex,-tmp);
	// 		labsNum = tmp;
	// 	}
	// } else {
	// 	subjects.incSubjectCount(labIndex,-labsNum);
	// }

	// printf("Press any key to close \r");
	// #ifdef _WIN32 | _WIN64
	// SYSTEMTIME lt;
	// while (_kbhit()) {
	// 	GetLocalTime(&lt);
	// 	Sleep(50);
	// }
	// #endif

	// #ifdef __linux__
	// 	std::cin.get();
	// #endif

	// std::ofstream outputFile(FILE_NAME);
	// outputFile << subjects;
	// outputFile.close();
	
	// #ifdef __linux__
	// char tmpStr[SHARED_MEMORY_OBJECT_SIZE];
	// sprintf(tmpStr,"%d",labsNum);
	// createMemory(tmpStr);
	// #endif
	// return labsNum;
}
