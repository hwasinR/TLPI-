#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char ** argv)
{
    if(argc != 3 && argc != 4)
    {
        printf("Wrong para nums!\n");
        exit(EXIT_FAILURE);
    }
    if(argc == 4 && strcmp("[x]",argv[3])!= 0)
    {
        printf("The 3rd para has to be [x]\n");
        exit(EXIT_FAILURE);
    }
    
    int fd;
    int flag = (argc == 4)?O_RDWR | O_CREAT:O_RDWR | O_CREAT | O_APPEND;
    int NumofBits = atoi(argv[2]);
    char buffer[10] = "aaaaa";int len = strlen(buffer);
    int times = NumofBits / len;

    fd = open(argv[1],flag,S_IRUSR | S_IWUSR);
    if(fd == -1)
    {
        perror("Open file failed!");
        exit(EXIT_FAILURE);
    }
    if (argc == 3)
    {
        for (int i = 0; i < times; i++)
            write(fd, buffer, len);
    }
    if (argc == 4)
    {
        for (int i = 0; i < times; i++)
        {
            lseek(fd, 0, SEEK_END);
            write(fd, buffer, len);
        }
    }
    if(close(fd) == -1)
    {
        perror("Close failed!");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}