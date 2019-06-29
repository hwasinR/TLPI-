#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFF_SIZE 10
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Wrong para!");
        exit(EXIT_SUCCESS);
    }

    int Source_fd;
    Source_fd = open(argv[1], O_RDONLY);
    if (Source_fd == -1)
    {
        perror("Open Source file failed!");
        exit(EXIT_FAILURE);
    }

    int Dest_fd;
    Dest_fd = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (Dest_fd == -1)
    {
        perror("Open Dest file failed!");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFF_SIZE];
    ssize_t len;
    while ((len = read(Source_fd, buffer, BUFF_SIZE)) != EOF && len != 0)
    {
        write(Dest_fd, buffer, len);
    }
    if (close(Source_fd) == -1)
    {
        perror("Close Source file failed!");
        exit(EXIT_FAILURE);
    }
    if (close(Dest_fd) == -1)
    {
        perror("Close Dest file failed!");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}