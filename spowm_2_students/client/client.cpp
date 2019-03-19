#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

#define MAX_BUF 1024

int main(int argc, char* argv[]){
    int fd;
    char * myfifo = argv[1];
    char buf[MAX_BUF];

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    close(fd);

    return atoi(buf);
}