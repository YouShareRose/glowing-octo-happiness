/*
 * strudef.c
 *
 *  Created on: 2014年10月24日
 *      Author: Candy
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//定义表示图像的结构体
typedef struct _image
{
	int	w;	//图像宽度
	int h;	//图像高度
	int* bits;	//指向图像数据的指针
} image;

//创建一张宽度为w，高为h的图像（结构体）
//返回的是指向这个图像的指针
image* create(int w, int h)
{
	//首先用malloc()函数为结构体动态盛情内存
	//其中保存的仅仅是图像的宽、高信息以及指向图像数据的指针
	image* img = malloc(sizeof(image));
	//设置图像的宽和高
	img->w = w;
	img->h = h;

	//为图像数据动态申请内存
	//根据图像数据的数据类型(int)和图像的宽和高
	//计算保存图像需要的内存体积大小
	img->bits = malloc(sizeof(int)*w*h);
	//初始化图像数据
	memset(img->bits,sizeof(int)*w*h,0);

	//返回指向创建成功的图像结构体的指针
	return img;
}


//在图像是绘制图形
image* draw(image* img)
{
	int w = img->w;
	int h = img->h;
	int centerx = w/2;
	int centery = h/2;
	int i,j;
	for( i = 0; i < w; ++i)
	{
		for(j = 0; j < h; ++j)
		{
			//如果当前作坐标点(i,j)在菱形范围内(到中心位置(centerx,centery)的
			//距离小于某个特定值)，或者是在边框上，则将这个像素点赋值为1
			if(((abs(centerx-i)+abs(centery-j))< w/2) ||//绘制菱形
				(0 == i*j) ||	//绘制边框
				(0 == (i+1-w)*(j+1-h)))
			{
				//通过指针的形式访问图像数据指针bits所指向的内存
				*(img->bits + w*i + j) = 1;
			}
		}
	}

	return img;
}

//显示图像
void print(image* img)
{
	int i,j;
	for(i = 0; i < img->w; ++i)
	{
		for(j=0; j<img->h; ++j)
		{
			//同样使用指针的形式访问图像数据，
			//将有图像的位置显示为“*”，其他地方留空
			if(1 == *(int*)(img->bits + img->w*i + j ))
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

//将图像结构体保存（写入）文件
void save(image* img, char* name)
{
	//以"wb"的二进制只写形式打开文件
	FILE* data;
	data = fopen(name, "wb");

	//首先，用fprintf()函数写入图像的宽和高信息
	fprintf(data,"%d %d",img->w,img->h);
	//将结构体中bits指针所指向的图像数据当作一个整体，
	//一次性地写入文件，这里，"sizeof(int)"表示每一个
	//图像数据（像素）是int类型的数据，而这些数据一共
	//有宽*高个，也就是"img->w*img->h"
	fwrite(img->bits,sizeof(int),img->w*img->h,data);
	//写入完成，关闭文件
	fclose(data);

}


//从文件读取图像数据结构体
image* read(char* name)
{
	//首先，以只读的二进制方式打开文件
	FILE* data;
	data = fopen(name, "rb");

	//动态申请结构体所占用的内存
	image* img = malloc(sizeof(image));
	//用fprintf()函数对应的fscanf()函数读取结构体的普通数据成员
	fscanf(data,"%d %d",&img->w,&img->h);
	//动态申请图像数据所占用的内存资源，其体积的大小，就是
	//单个数据的体积*数据的个数(sizeof(int)*img->w*img->h),
	//这些都是与写入的时候的体积数据相对应的。
	//最后讲结构体的bits指针指向这一内存区域。
	img->bits = malloc(sizeof(int)*img->w*img->h);

	//将使用fwrite()函数写入的图像数据，从文件读取到结构体的
	//bits指针所指向的内存区域，其单个数据的大小和数据的个数与
	//写入时的数据完全相同
	fread(img->bits,sizeof(int),img->w*img->h,data);

	//读取完成，关闭文件
	fclose(data);

	//返回从文件读取的结构体
	return img;
}

//释放结构体所占用的内存
image* freeimg(image* img)
{
	if(NULL != img)
	{
		//释放结构体指向的图像数据
		free(img->bits);
		//释放结构体本身
		free(img);

	}
	//返回NULL指针，表示释放成功
	return NULL;
}

//在主函数中展示结构体读写的过程
int main()
{
	//定义图形的宽和高
	const int w = 37;
	const int h = 37;
	//创建相应大小的结构体，得到指向这个结构体的指针
	image* img = create(w,h);
	//在图像是绘制菱形和边框
	draw(img);
	//显示图像
	print(img);

	//保存图像结构体
	save(img,"demo.img");
	//图像结构体已经被保存，可以释放程序中的图像结构体
	img = freeimg(img);


	//从文件读取图像结构体
	image* rimg = read("demo.img");
	//显示读取的图像结构体以验证读写的正确性
	print(rimg);
	//释放读取的图像结构体。
	rimg=freeimg(rimg);

	return 0;

}




















