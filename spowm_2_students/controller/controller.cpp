#include<stdlib.h>
#ifdef _WIN32
#include<conio.h>
#include<windows.h>
#else
#include <sys/wait.h>
#include <ncurses.h>
#include<unistd.h>
#include <signal.h>
#include <termios.h>
#include <cstring>
#include <fcntl.h>
#endif
#include<vector>
#include<iostream>

#ifdef _WIN32
const int maxEventNameSize = 50;
const char path[50] = "parent.exe";
PROCESS_INFORMATION createProcess(char * commandline) {
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION infProc;
	ZeroMemory(&infProc, sizeof(infProc));
	char tmpBuff[100];
	sprintw(tmpBuff,"%s %s",path,commandline);
	if (!CreateProcess(NULL, tmpBuff, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &infProc))
		printw("Create Process failed (%d)\n", GetLastError());
	return infProc;
}

int main() {
    char choice;
	int currentEvent = 0;
    bool flag = true;
    char EventName[maxEventNameSize];
	std::vector<PROCESS_INFORMATION> threadsInfo;
	std::vector<HANDLE> closeEvents;
	std::vector<HANDLE> printEvents;


while(1) {
        if (_kbhit()) {
            choice = _getch();
            switch (choice) {
                case '1':
                    sprintw(EventName, "%dCE", closeEvents.size() + 1);
                    closeEvents.push_back(CreateEvent(NULL, FALSE, FALSE, EventName));
                    sprintw(EventName, "%dPE", printEvents.size() + 1);
                    printEvents.push_back(CreateEvent(NULL, TRUE, FALSE, EventName));
                    sprintw(EventName, "%d", printEvents.size());
                    threadsInfo.push_back(createProcess( EventName));
                    break;
                case '2':
                    if (closeEvents.size() > 0) {
                        SetEvent(closeEvents.back());

                        if (!CloseHandle(closeEvents.back()))
                            printw("Close Handle failed (%d)\n", GetLastError());
                        if (!CloseHandle(printEvents.back()))
                            printw("Close Handle failed (%d)\n", GetLastError());

                        closeEvents.pop_back();
                        printEvents.pop_back();
                        if (currentEvent >= closeEvents.size()) {
                            currentEvent = 0;
                            flag = true;
                        }
                    }
                    break;
                case '3':
                    if (closeEvents.size() > 0) {
                        while (closeEvents.size() > 0) {
                            SetEvent(closeEvents.back());
                            WaitForSingleObject(threadsInfo.back().hProcess, INFINITE);
                            if (!CloseHandle(closeEvents.back()) || !CloseHandle(printEvents.back()) || !CloseHandle(threadsInfo.back().hProcess) || !CloseHandle(threadsInfo.back().hThread))
                                printw("Close Handle failed (%d)\n", GetLastError());
                            closeEvents.pop_back();
                            printEvents.pop_back();
                        }
                       currentEvent = 0;
                    }
                    return 0;
                default:
                    break;
                }
            }
        
		if (printEvents.size() > 0 && WaitForSingleObject(printEvents[currentEvent], 0) == WAIT_TIMEOUT) {
			if (currentEvent >= printEvents.size() - 1)
                currentEvent = 0;
			else if (!flag) currentEvent++;
			flag = false;
			SetEvent(printEvents[currentEvent]);
		}
    }
    return 0;
}
#endif


int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


int printFlag = 0;
int endFlag = 1;

void enablePrint(int signo) {
	printFlag = 1;
}

void closeProcess(int signo) {
	endFlag = 1;
}

struct sigaction printSignal, closeSignal;
#ifdef __linux__
    int main () {
        initscr();
        
        int currentNum = 0;
        int processCount = 0;
        int flag = 0;
    	std::vector<pid_t> processesPids;
        pid_t tmpPid ;

        printSignal.sa_handler = enablePrint;
        sigaction(SIGUSR1, &printSignal, NULL);

        closeSignal.sa_handler = closeProcess;
        sigaction(SIGUSR2, &closeSignal, NULL);

        while(1) {
            // napms(10);
            rewind(stdin);
            fflush(stdin); 
            if(kbhit()) {
                switch (getchar()) {
                    case '1':
                        // tmpPid = fork();
                        processesPids.push_back(fork());
                        processCount++;
                        switch(processesPids.back()) {
                            case 0:
                                endFlag = 0;
                                char message[40];
                                sprintf(message, "%d %s\n", processCount, " student");
                                while (!endFlag) {
                                    usleep(30000); 
                                    // napms(100);
                                    if (printFlag) {
                                        // Person obj();
                                        for (int i = 0; i < strlen(message); i++) {
                                            if (endFlag)
                                                return 0;
                                            printw("%c", message[i]);
                                            refresh();
                                            usleep(50000);
                                        }
                                            refresh();
                                        printFlag = 0;
                                        kill(getppid(), SIGUSR2);
                                        }
                                    }
                                    return 0;
                                case -1:
                                    printw("Fork fail");
                                    refresh();
                                    return -1;
                                default:
                                    break;
                        }
                    break;

                    case '2':
                        if(processCount > 0) {
                            processCount--;
                            kill(processesPids[processCount],SIGUSR2);
                            waitpid(processesPids[processCount],NULL,NULL);

                            processesPids.pop_back();
                            if(currentNum >=  processCount) {
                                currentNum = 0;
                                endFlag = 1;	
                                flag = 1;			
                            }
                        }
                    break;

                    case '3':   
                        if (processesPids[processCount - 1] != 0)
                            for (; processCount >= 0; processCount--) {
                                kill(processesPids[processCount - 1], SIGUSR2);
                                waitpid(processesPids[processCount - 1], NULL, NULL);
                                processesPids.pop_back();
                            }
                            endwin();
                        return 0;
                }

            }
            if(endFlag && processCount > 0) {
                endFlag = 0;
                if(currentNum >= processCount - 1) {
                    currentNum = 0;
                } else if(!flag)
                    currentNum++;
                flag = 0;
                kill(processesPids[currentNum], SIGUSR1);
            }
         }

	endwin();
        return 0;
    }
#endif