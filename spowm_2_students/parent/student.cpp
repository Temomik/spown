#include "Student.h"
#include <stdlib.h>
#ifdef _WIN32 | _WIN64
#define CLEAR "cls"

#endif
#ifdef __linux__
#define CLEAR "clear"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include <curses.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define SHARED_MEMORY_OBJECT_NAME "buffMem"
#define SHARED_MEMORY_OBJECT_SIZE 50
#endif

int Student::enterLabsProcess(int i) {
	char buff[256], paremeter[256];
	#ifdef __linux__
	char* arrayBuff[4];
	char labsCount[20], labsNum[20] ;
	sprintf(labsCount, "%d", this->labs[i]);
	sprintf(labsNum, "%d", i);
	#endif
	snprintf(buff, 256, "%s %d %d", this->path, this->labs[i], i); // error
	#ifdef _WIN32 | _WIN64
	DWORD result;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, 
		TEXT((LPSTR)buff),		
		NULL,					
		NULL,					
		FALSE,					
		NULL,		
		NULL,					
		NULL,					 
		&si,					
		&pi)					
		) {
		printf("CreateProcess failed (%d)\n",GetLastError() );
		return GetLastError();
	}
	



	// SYSTEMTIME lt;
	// while (WaitForSingleObject(pi.hProcess, 50)) {

	// GetExitCodeProcess(pi.hProcess, &result);
	#endif

#ifdef __linux__
	int result;
	pid_t pid = fork();
    if (pid < 0) {
        exit(-1);
    }
    else if (pid  == 0) {
		// arrayBuff[0] = (char*)this->path;
		// arrayBuff[2] = labsCount;
		// arrayBuff[1] = labsNum;
		// arrayBuff[3] = NULL;

		// execl("/usr/bin/xterm","/usr/bin/xterm","-e",this->path, labsCount, labsNum, NULL);
		return 0;
    } else if(pid > 0) {
    //     int st;
		
	// while (waitpid(pid, &st, 0) <= 0) {
	// 	system(CLEAR);
	// }

	// int shm, mode = 0;
    // char *addr;

	// if ((shm = shm_open(SHARED_MEMORY_OBJECT_NAME, mode | O_RDWR, 0777)) == -1) {
	// 	perror("shm_open");
	// 	return 1;
	// }
	// addr = (char*)mmap(0, SHARED_MEMORY_OBJECT_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
	// result = atoi(addr);
	// munmap(addr, SHARED_MEMORY_OBJECT_SIZE);
    // close(shm);
    // shm_unlink(SHARED_MEMORY_OBJECT_NAME);
	}	

#endif
 	// system(CLEAR);
	// switch (result) {
	// case -6:
	// 	std::cout << "You dont have labs!" << std::endl;
	// 	break;
	// case 0:
	// 	std::cout << "Not enought subjects!" << std::endl;
	// 	break;
	// case -5:
	// 	std::cout << "Not enough time!" << std::endl;
	// 	break;
	// case -10:
	// 	std::cout << 10 << std::endl;
	// 	std::cin.get();
	// 	break;
	// #ifdef _WIN32 | _WIN64
	// case WAIT_FAILED:
	// 	std::cout << "FAIL!" << std::endl;
	// 	break;
	// #endif
	// default:
	// 	if(result > 0) {
	// 		std::cout << "You pass " + this->labMenu.getElem(i+1) << "!" << std::endl;
	// 		this->labs[i] -= result;
	// 	}
	// 	break;
	// }

	// #ifdef _WIN32 | _WIN64
	// CloseHandle(pi.hProcess);
	// #endif
	// std::cin.get();
	return 0;
}

Student::Student() {
	menu.push("You want to pass labs:");
	menu.push("Pass labs");
	menu.push("add labs to list");
	menu.push("check labs count");
	menu.push("end");

	labMenu.push("subject:");
	labMenu.push("ep");
	labMenu.push("physics");
	labMenu.push("kpi9p");
	labMenu.push("spowm");
	labMenu.push("tec");
	for (int i = 0; i < 5; i++) {
		this->labs[i] = 0;
	}
}

Student::~Student() {
}

void Student::outLabsCount() {
	for (int i = 0; i < 5; i++) {
		std::cout << this->labMenu.getElem(i+1) << " - " << this->labs[i] << std::endl;
		#ifdef __linux__
		printf("\033[0F");
		printf("\033[0E");
		#endif
	}
}

void Student::startMenu(char* eventNamePart) {
	#ifdef _WIN32
		char eventName[30];
		sprintf(eventName, "%sCE", eventNamePart);
		HANDLE closeEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, eventName);
		std::string nameOfProcess(eventNamePart);
		sprintf(eventName, "%sPE", eventNamePart);
		HANDLE canPrintEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, eventName);

		nameOfProcess += " student in queue";
		while (1) {
			 Sleep(1);
			if (WaitForSingleObject(canPrintEvent, 1) == WAIT_OBJECT_0) {
				printf("\n");
				enterLabsProcess(5);
				for (int i = 0; i < nameOfProcess.length(); i++) {
					if (WaitForSingleObject(closeEvent, 0) == WAIT_OBJECT_0) {
						CloseHandle(closeEvent);
						CloseHandle(canPrintEvent);
						return;
					}
					printf("%c", nameOfProcess[i]);
					Sleep(20);
				}
				ResetEvent(canPrintEvent);
			}

			if (WaitForSingleObject(closeEvent, 0) == WAIT_OBJECT_0) {
				CloseHandle(closeEvent);
				CloseHandle(canPrintEvent);
				return;
			}
		}
	#endif
	enterLabsProcess(5);

}
