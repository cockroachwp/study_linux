#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

//在真缓冲空间中输出一张图片
struct pixel_32{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char alpha;
};
struct pixel_24{
	unsigned char b;
	unsigned char g;
	unsigned char r;
    unsigned char d;
};
int main()
{
	int fbfd = open("/dev/fb0", O_RDWR);
	if(fbfd < 0)
	{
		perror("open fb0 failed");
		return -1;
	}
	struct fb_var_screeninfo  vinfo;
	int ret = ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);
	if(ret < 0)
	{
		perror("FBIOGET_VSCREENINFO failed");
		return -1;
	}
	printf("宽：%u\n", vinfo.xres);
	printf("高：%u\n", vinfo.yres);
	printf("虚拟宽：%u\n", vinfo.xres_virtual);
	printf("虚拟高：%u\n", vinfo.yres_virtual);
	printf("位深度：%d\n", vinfo.bits_per_pixel);

	struct fb_fix_screeninfo finfo;
	ret = ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo);
	if(ret < 0)
	{
		perror("FBIOGET_FSCREENINFO failed");
		return -1;
	}
	
	printf("一行所占空间：%u\n", finfo.line_length);

	unsigned fbsize0 = finfo.line_length * vinfo.yres_virtual;
	//unsigned fbsize1 = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;
	printf("fbsize0 = %u\n", fbsize0);
	
	unsigned char *fbp = (unsigned char *)mmap(NULL, fbsize0, PROT_WRITE|PROT_READ, MAP_SHARED, fbfd, 0);
	if(fbp == MAP_FAILED)
	{
		perror("mmap framebuffer failed");
		close(fbfd);
		return -1;
	}
	/*
	输出10行红色
	*/
	struct pixel_32 red={255, 255, 255, 0};
	struct pixel_32 * fbp_32 = (struct pixel_32 *)fbp;
	FILE *fp = fopen("12.bmp", "r+");
	if(fp == NULL)
	{
		perror("fopen file failed");
		return -1;
	}
	fseek(fp, 54, SEEK_SET);
	struct stat filestatus;
	stat("12.bmp", &filestatus);
	unsigned int filesize = filestatus.st_size;
	printf("filesize = %d\n", filesize);
	unsigned char imgbuf[1024 * 1024 *3 ] ={0};
	fread(imgbuf, filesize-54, 1, fp);

	struct pixel_24* imgbuf_24 = (struct pixel_24 *)imgbuf;
	unsigned int i, j;
	for(i = 0; i < 604; i++)//行跳转
	{
		for(j = 0; j < 1077; j++)//刷新对应行上的像素点
		{
			(fbp_32 + i * 2048 + j)->r = (imgbuf_24 + i * 1077 + j)->r;
			(fbp_32 + i * 2048 + j)->g =0;// (imgbuf_24 + i * 1077 + j)->g;
			(fbp_32 + i * 2048 + j)->b = 0;//(imgbuf_24 + i * 1077 + j)->b;
		}
	}
	
	ret = munmap(fbp, fbsize0);
	if(ret < 0)
	{
		perror("munmap framebuffer failed");
	}
	close(fbfd);
	return 0;  
}
