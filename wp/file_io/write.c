/*************************************************************************
    > File Name: write.c
    > Author: cockroach
    > Mail: cockroachwp@163.com 
    > Created Time: Thu 11 Jul 2019 03:55:57 AM PDT
 ************************************************************************/
#include<stdio.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>


main()
{
	int fd = 0;
	char *testwrite = "./testwrite";
	ssize_t lenhth_w = 0;
	char buffer_write[] = "hello write funtion\r\n";

	if ((fd = open(testwrite, O_RDWR|O_CREAT, 0777)) <0 ){
		printf("open %s failed \n", testwrite);
	}

	// write some  word into testwrite
	lenhth_w = write(fd, buffer_write, strlen(buffer_write));
	if (lenhth_w == -1) {
	    perror("write");
	} else {
		printf ("write funtion ok!\n");
	}
	close(fd);
}
