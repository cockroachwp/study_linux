/*************************************************************************
    > File Name: stat.c
    > Author: cockroach
    > Mail: cockroachwp@163.com 
    > Created Time: Tue Jul 30 23:29:55 2019
 ************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fcntl.h>

int main(int argc, char *argv[])
{
	struct stat groupstat;
	int fd, ret;

	if (argc < 2) {
		printf ( "\nPlease input file path \r\n");
		return 1;
	}

	ret = stat(argv[1], &groupstat);

	if (ret) {
		printf("please make sure file path\r\n");
		return 1;
	}

	printf("stat function test , %s of st_ino inode is %ld\n",argv[1],groupstat.st_ino);
    fd = open(argv[1], O_RDWR|O_NOCTTY|O_NDELAY);

	if (fd < 0) {
		printf("please make sure file path\r\n");
		return 1;
	}
	
	ret = fstat(fd, &groupstat);

	if (ret) {
		printf("please make sure file path\r\n");
		return 1;
	}

    printf("stat function test , %s of st_ino inode is %ld\n",argv[1],groupstat.st_ino);
 
	return 0;

}
