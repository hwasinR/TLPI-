#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#define BUFF_SIZE 20
ssize_t _writev(int fd, const struct iovec *iov, int iovcnt);
int main(int argc, char **argv)
{
    struct iovec iov[3];
    char str[BUFF_SIZE] = "DARK SOULS";
    char str2[BUFF_SIZE] = "BLOODBORNE";
    char str3[BUFF_SIZE] = "SEKIRO";

    iov[0].iov_base = &str;
    iov[0].iov_len = strlen(str);
    iov[1].iov_base = &str2;
    iov[1].iov_len = strlen(str2);
    iov[2].iov_base = &str3;
    iov[2].iov_len = strlen(str3);

    int fd;
    fd = open("Writevlog", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd <= 0)
    {
        perror("Open file failed!");
        exit(EXIT_FAILURE);
    }
    if (_writev(fd, iov, 3) == -1)
    {
        perror("_writev failed!");
        exit(EXIT_FAILURE);
    }
    if (close(fd) == -1)
    {
        perror("close file failed!");
        exit(EXIT_FAILURE);
    }
    fd = open("Writevlog2", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd <= 0)
    {
        perror("Open file failed!");
        exit(EXIT_FAILURE);
    }
    if (writev(fd, iov, 3) == -1)
    {
        perror("writev failed!");
        exit(EXIT_FAILURE);
    }
    if (close(fd) == -1)
    {
        perror("close file failed!");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
ssize_t _writev(int fd, const struct iovec *iov, int iovcnt)
{
    ssize_t len, sum = 0;
    for (size_t i = 0; i < iovcnt; i++)
    {
        len = write(fd, iov[i].iov_base, iov[i].iov_len);
        if (len == -1)
        {
            perror("Seq Write failed!");
            return -1;
        }
        sum += len;
    }
    return sum;
}