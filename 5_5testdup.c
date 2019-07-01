#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char **argv)
{
    int fd;
    int newfd;
    
    if ((fd = open("tex.txt", O_RDWR,S_IRUSR | S_IWUSR)) == -1)
    {
        perror("Open file failed!\n");
        exit(EXIT_FAILURE);
    }
    if ((newfd = dup(fd)) == -1)
    {
        perror("dup failed!\n");
        exit(EXIT_FAILURE);
    }
    int flags, newflags;
    if ((flags = fcntl(fd, F_GETFL)) == -1)
    {
        perror("fcntl failed!\n");
        exit(EXIT_FAILURE);
    }
    if ((newflags = fcntl(newfd, F_GETFL)) == -1)
    {
        perror("fcntl failed!\n");
        exit(EXIT_FAILURE);
    }
    if (flags == newflags)
    {
        printf("Same Flags!\n");
    }
    if (lseek(fd, 0, SEEK_END) == -1)
    {
        perror("lseek failed!\n");
        exit(EXIT_FAILURE);
    }

    char buffer[20] = "test for fileNum!";
    if(write(newfd,buffer,strlen(buffer)) <= 0)
    {
        perror("write failed!\n");
        exit(EXIT_FAILURE);
    }
    if (close(newfd) == -1)
    {
        perror("close file failed!\n");
        exit(EXIT_FAILURE);
    }
    if (close(fd) == -1)
    {
        perror("close file failed!\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
