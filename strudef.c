/*
 * strudef.c
 *
 *  Created on: 2014��10��24��
 *      Author: Candy
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//�����ʾͼ��Ľṹ��
typedef struct _image
{
	int	w;	//ͼ����
	int h;	//ͼ��߶�
	int* bits;	//ָ��ͼ�����ݵ�ָ��
} image;

//����һ�ſ��Ϊw����Ϊh��ͼ�񣨽ṹ�壩
//���ص���ָ�����ͼ���ָ��
image* create(int w, int h)
{
	//������malloc()����Ϊ�ṹ�嶯̬ʢ���ڴ�
	//���б���Ľ�����ͼ��Ŀ�����Ϣ�Լ�ָ��ͼ�����ݵ�ָ��
	image* img = malloc(sizeof(image));
	//����ͼ��Ŀ�͸�
	img->w = w;
	img->h = h;

	//Ϊͼ�����ݶ�̬�����ڴ�
	//����ͼ�����ݵ���������(int)��ͼ��Ŀ�͸�
	//���㱣��ͼ����Ҫ���ڴ������С
	img->bits = malloc(sizeof(int)*w*h);
	//��ʼ��ͼ������
	memset(img->bits,sizeof(int)*w*h,0);

	//����ָ�򴴽��ɹ���ͼ��ṹ���ָ��
	return img;
}


//��ͼ���ǻ���ͼ��
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
			//�����ǰ�������(i,j)�����η�Χ��(������λ��(centerx,centery)��
			//����С��ĳ���ض�ֵ)���������ڱ߿��ϣ���������ص㸳ֵΪ1
			if(((abs(centerx-i)+abs(centery-j))< w/2) ||//��������
				(0 == i*j) ||	//���Ʊ߿�
				(0 == (i+1-w)*(j+1-h)))
			{
				//ͨ��ָ�����ʽ����ͼ������ָ��bits��ָ����ڴ�
				*(img->bits + w*i + j) = 1;
			}
		}
	}

	return img;
}

//��ʾͼ��
void print(image* img)
{
	int i,j;
	for(i = 0; i < img->w; ++i)
	{
		for(j=0; j<img->h; ++j)
		{
			//ͬ��ʹ��ָ�����ʽ����ͼ�����ݣ�
			//����ͼ���λ����ʾΪ��*���������ط�����
			if(1 == *(int*)(img->bits + img->w*i + j ))
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

//��ͼ��ṹ�屣�棨д�룩�ļ�
void save(image* img, char* name)
{
	//��
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




















