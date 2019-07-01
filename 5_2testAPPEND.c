#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char** argv)
{
    int fd;
    if(argc != 2)
    {
	   printf("Only filepath is needed!\n");
	   exit(EXIT_FAILURE);
    }
    char buffer[10] = "hello!";
    
    if((fd = open(argv[1],O_WRONLY|O_APPEND)) != -1)

    //if((fd = open(argv[1],O_WRONLY)) != -1)
    {
	   off_t cur;
	   cur = lseek(fd,0,SEEK_SET);
	   write(fd,buffer,strlen(buffer));
           close(fd);
    }
    else
           exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}
