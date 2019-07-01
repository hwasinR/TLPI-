#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
extern int optind, opterr, optopt;
extern char *optarg;
#define printable(ch) (isprint((unsigned char)ch) ? ch : '#')
#define BUFF_SIZE 10
int main(int argc, char **argv)
{
    int opt;
    bool A_flag = false;
    char **filename;
    int *fd;
    // use if ?
    while ((opt = getopt(argc, argv, ":a")) != -1)
    {
        //printf("opt = %3d (%c); optind = %d\n", opt, printable(opt), optind);
        if (opt == 'a')
            A_flag = true;
        else
        {
            printf("Wrong para!\n");
            exit(EXIT_FAILURE);
        }

        if (optarg != NULL)
        {
            printf("%s", optarg);
            //printf("\n");
        }
    }
    //printf("current optind = %d\n", optind);
    if (argc > optind)
    {
        filename = malloc(sizeof(char) * (argc - optind));
        fd = malloc(sizeof(int) * (argc - optind));
        int fileflag = A_flag ? O_RDWR | O_CREAT | O_APPEND : O_RDWR | O_CREAT;
        for (size_t i = 0; i < argc - optind; i++)
        {
            filename[i] = argv[optind + i];
            //printf("%s ", filename[i]);
            fd[i] = open(filename[i], fileflag, S_IRUSR | S_IWUSR);
            if (fd[i] == -1)
                perror("Open file failed\n");
            //printf("%d", fd[i]);
        }
    }
    char buffer[BUFF_SIZE + 1];
    ssize_t len;
    //if ((len = read(STDIN_FILENO, buffer, BUFF_SIZE)) == -1)
    //perror("Read file failed\n");
    while ((len = read(STDIN_FILENO, buffer, BUFF_SIZE)) != 0 && len != EOF)
    {
        buffer[len] = '\0';
        //printf("%s",buffer);
        if (write(STDOUT_FILENO, buffer, len) == -1)
            perror("Write file failed\n");
        if (fd != NULL)
        {
            for (size_t i = 0; i < argc - optind; i++)
            {
                if (write(fd[i], buffer, len) == -1)
                    perror("Write file failed\n");
                //                if (close(fd[i]) == -1)
                //                   perror("Close file failed");
            }
        }
    }
    for (size_t i = 0; i < argc - optind; i++)
    {
        //if (write(fd[i], buffer, len) == -1)
        // perror("Write file failed\n");
        if (close(fd[i]) == -1)
            perror("Close file failed");
    }
    exit(EXIT_SUCCESS);
}