#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "main.h"

#define PORT 2222
#define IPADDR "192.168.5.129"


pthread_mutex_t mutex;
CAMERA *camera = NULL;
SERIAL *serial = NULL;


void *camera_thread(void *arg)
{
	
	
	
	/*摄像头*/
}

void *serial_thread(void *arg)
{
	/*串口，控制传输M0信息*/
}


void *gsm_thread(void *arg)
{
	/*GSM*/
}

void *lcd_thread(void *arg)
{
	/*显示*/
}


void *client_thread(void *arg)
{
	int conn_fd = (int)arg;
	char buf[10];  /*buf用于保存比对信息(pic,env)*/
	char head[20];  /*head用于保存图片、串口等数据的大小*/
	while(1)
	{
		memset(buf,0,sizeof(buf));
		memset(head,0,sizeof(head));
		if(-1 = read(conn_fd,buf,sizof(buf)))
		{
			perror("read failed");
			exit(EXIT_FAILURE);
		}
		if(0 == strncmp(buf,"pic",3))
		{
			int count = 0;
			pthread_mutex_lock(&mutex);
			int data_length = sprintf(head,"%d",camera->len);
			if(-1 = data_length){
				perror("sprintf failed");
				exit(EXIT_FAILURE);
			}
			write(conn_fd,head,sizeof(head));  /*写图片大小*/
			while(count < camera->len)  /*写图片内容*/
			{
				ret = write(conn_fd,camera->data,camera->len-count);
				count += ret;
			}
			pthread_mutex_unlock(&mutex);
		}
		else if(0 == strncmp(buf,"env",3))
		{
			int count = 0;
			pthread_mutex_lock(&mutex);
			int data_length = sprintf(head,"%d",serial->len);
			if(-1 = data_length){
				perror("sprintf failed");
				exit(EXIT_FAILURE);
			}
			write(conn_fd,head,sizeof(head));  /*写串口数据大小*/
			while(count < serial->len)  /*写串口数据内容*/
			{
				ret = write(conn_fd,serial->data,serial->len-count);
				count += ret;
			}
			pthread_mutex_unlock(&mutex);
		}
		
		
	}
	
	
}


/*服务器socket绑定*/
static void server_init(int sock_fd)
{
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	printf("socket success!\n");

	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(PORT);  
	myaddr.sin_addr.s_addr = inet_addr(IPADDR);
	
	if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	printf("bind success!\n");
	
	if (0 > listen(sockfd, 1024)) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("listen......\n");
	sock_fd = sockfd;
}


int main(void)
{
	int ret;
	pthread_t camera_tid,serial_tid,gsm_tid,lcd_tid;
	

	/*camera thread*/
	ret = pthread_create(&camera_tid,NULL,camera_thread,NULL);
	if(ret != 0){
		errno = ret;
		perror("create camera_thread");
		exit(EXIT_FAILURE);
	}else{
		printf("create camera_thread success!\n");
	}
	ret = pthread_detach(camera_tid);
	if(ret != 0){
		errno = ret;
		perror("detach camera_thread");
		exit(EXIT_FAILURE);
	}else{
		printf("detach camera_thread success!\n");
	}
	
	
	/*serial thread*/
	ret = pthread_create(&serial_tid,NULL,serial_thread,NULL);
	if(ret != 0){
		errno = ret;
		perror("create serial_thread");
		exit(EXIT_FAILURE);
	}else{
		printf("create serial_thread success!\n");
	}
	ret = pthread_detach(serial_tid);
	if(ret != 0){
		errno = ret;
		perror("detach serial_thread");
		exit(EXIT_FAILURE);
	}else{
		printf("create serial_thread success!\n");
	}
	
	
	/*GSM thread*/
	ret = pthread_create(&gsm_tid,NULL,gsm_thread,NULL);
	if(ret){
		errno = ret;
		perror("create gsm_thread");
		exit(EXIT_FAILURE);
	}else{
		printf("create gsm_thread success!\n");
	}
	ret = pthread_detach(gsm_tid);
	if(ret != 0){
		errno = ret;
		perror("detach gsm_thread");
		exit(EXIT_FAILURE);
	}else{
		printf("detach gsm_thread success!\n");
	}
	
	
	/*lcd thread*/
	ret = pthread_create(&lcd_tid,NULL,lcd_thread,NULL);
	if(ret != 0)
	{
		errno = ret;
		perror("create lcd_thread");
		exit(EXIT_FAILURE);
	}else{
		printf("create lcd_thread success!\n");
	}
	ret = pthread_detach(lcd_tid);
	if(ret != 0){
		errno = ret;
		perror("detach lcd_thread");
		exit(EXIT_FAILURE);
	}else{
		printf("detach lcd_thread success!\n");
	}

	int sock_fd;
	server_init(sock_fd);  /*初始化服务器，socket,bind,listen*/
	struct sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	
	while(1)
	{
		
		int addrlen = sizeof(client_addr);
		int connfd = accept(sock_fd, (struct sockaddr*)&client_addr, &addrlen);
		if (connfd < 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}
		printf("accept: %s\n", inet_ntoa(client_addr.sin_addr));	
		
		
		pthread_t client_tid;
		if(0 != pthread_create(&client_tid,NULL,client_thread,NULL)) {
			perror("create client_thread failed");
			exit(EXIT_FAILURE);
		}
		printf("create client_thread success!\n");
		if(0 != pthread_detach(client_tid)) {
			perror("detach client_thread failed");
			exit(EXIT_FAILURE);
		}
		printf("detach client_thread success!\n");
		sleep(1);
		
	}
	


	return 0;
}

