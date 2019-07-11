#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
main()
{
    int    fd ;
    char  *leds  = "/dev/leds";
    char  *test1 = "./test1";
    char  *test2 = "./test2";
    char  *test3 = "./test3";

    if ((fd = open(leds, O_RDWR|O_NOCTTY|O_NDELAY)) < 0) {
        printf("open %s failed\n", leds);
    } 
        printf("\r\n%s open %d \n", leds, fd);
    
	if ((fd = open(test1, O_RDWR|0777)) <0 ) 
	{
	    printf("open %s failed!\n", test1);
	}
	    printf(" %s fd is %d\r\n\n", test1, fd);

	if ((fd = open(test2, O_RDWR|O_CREAT, 0777)) <0 ) 
	{
	    printf("open %s failed!\n", test2);
	}
	    
	    printf(" %s fd is %d\r\n", test2, fd);

	fd = creat(test3,0777);
	if(fd == -1) {
	    
	    printf(" %s fd is %d\r\n!", test3, fd);
	} else {
	    printf("creat %s is succeed!\r\n", test3);
	}

}
