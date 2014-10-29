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
	//以
	FILE* data;
	data = fopen(name, "wb");

	//
	fprintf(data,"%d %d",img->w,img->h);
	//
	//
	//
	//
	fwrite(img->bits,sizeof(int),img->w*img->h,data);
	//
	fclose(data);

}


//
image* read(char* name)
{
	//
	FILE* data;
	data = fopen(name, "rb");

	//
	image* img = malloc(sizeof(image));
	//
	fscanf(data,"%d %d",&img->w,&img->h);
	//
	//
	//
	//
	img->bits = malloc(sizeof(int)*img->w*img->h);

	//
	//
	//
	fread(img->bits,sizeof(int),img->w*img->h,data);

	//
	fclose(data);

	//
	return img;
}

//
image* freeimg(image* img)
{
	if(NULL != img)
	{
		//
		free(img->bits);
		//
		free(img);

	}
	//
	return NULL;
}

//
int main()
{
	//
	const int w = 37;
	const int h = 37;
	//
	image* img = create(w,h);
	//
	draw(img);
	//
	print(img);

	//
	save(img,"demo.img");
	img = freeimg(img);


	//
	image* rimg = read("dome.img");
	//
	print(rimg);
	//
	rimg=freeimg(rimg);

	return 0;

}




















