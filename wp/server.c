/*************************************************************************
    > File Name: server.c
    > Author: cockroach
    > Mail: cockroachwp@163.com 
    > Created Time: Thu Jul 18 01:27:07 2019
 ************************************************************************/
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<strings.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int     sfp = 0;
	int     nfp = 0;
	int     num = 0;
	struct  sockaddr_in s_add,c_add;
	int     sin_size;
	unsigned short port = 8888;
	char    buffer[100] = {0};

	printf("Hello, welcome to cockroach's server !\r\n");

	sfp = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sfp) {
		printf("socket faill !\r\n");
		return -1;
	}

	printf("socket is ok\r\n");

	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family      = AF_INET;
	s_add.sin_addr.s_addr = htonl(INADDR_ANY);
	s_add.sin_port        = htons(port);

	if (-1 == bind(sfp, (struct sockaddr *) (&s_add), sizeof(struct sockaddr))) {
		printf("bind fail ! \r\n");
		return -1;
	}

	if (-1 == listen(sfp, 5))

	printf("listen is ok !\r\n");

    sin_size = sizeof(struct sockaddr_in);

	nfp = accept (sfp, (struct sockaddr *)  (&c_add), &sin_size);
	if (-1 == nfp) {
		printf("accept is faill\r\n");
		return -1;
	}

    printf("accept ok!\r\nServer start get connect from %#x : %#x\r\n", 
		ntohl(c_add.sin_addr.s_addr), ntohs(c_add.sin_port));
	while(1) {
		memset(buffer, 0, 100);
		sprintf(buffer, "hello,welcome to my server(%d) \r\n", num++);
		send(nfp, buffer, strlen(buffer), 0);
		usleep(500000);
    }   
}

