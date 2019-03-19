
#include <sys/wait.h>
#include <sys/types.h>
#include <curses.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int fd;
    char * myfifo = argv[1];
    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_WRONLY);
    write(fd, argv[2], sizeof(argv[2]));
    close(fd);
	unlink(myfifo);
    return 0;
}