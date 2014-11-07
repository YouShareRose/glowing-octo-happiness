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
	//��"wb"�Ķ�����ֻд��ʽ���ļ�
	FILE* data;
	data = fopen(name, "wb");

	//���ȣ���fprintf()����д��ͼ��Ŀ�͸���Ϣ
	fprintf(data,"%d %d",img->w,img->h);
	//���ṹ����bitsָ����ָ���ͼ�����ݵ���һ�����壬
	//һ���Ե�д���ļ������"sizeof(int)"��ʾÿһ��
	//ͼ�����ݣ����أ���int���͵����ݣ�����Щ����һ��
	//�п�*�߸���Ҳ����"img->w*img->h"
	fwrite(img->bits,sizeof(int),img->w*img->h,data);
	//д����ɣ��ر��ļ�
	fclose(data);

}


//���ļ���ȡͼ�����ݽṹ��
image* read(char* name)
{
	//���ȣ���ֻ���Ķ����Ʒ�ʽ���ļ�
	FILE* data;
	data = fopen(name, "rb");

	//��̬����ṹ����ռ�õ��ڴ�
	image* img = malloc(sizeof(image));
	//��fprintf()������Ӧ��fscanf()������ȡ�ṹ�����ͨ���ݳ�Ա
	fscanf(data,"%d %d",&img->w,&img->h);
	//��̬����ͼ��������ռ�õ��ڴ���Դ��������Ĵ�С������
	//�������ݵ����*���ݵĸ���(sizeof(int)*img->w*img->h),
	//��Щ������д���ʱ�������������Ӧ�ġ�
	//��󽲽ṹ���bitsָ��ָ����һ�ڴ�����
	img->bits = malloc(sizeof(int)*img->w*img->h);

	//��ʹ��fwrite()����д���ͼ�����ݣ����ļ���ȡ���ṹ���
	//bitsָ����ָ����ڴ������䵥�����ݵĴ�С�����ݵĸ�����
	//д��ʱ��������ȫ��ͬ
	fread(img->bits,sizeof(int),img->w*img->h,data);

	//��ȡ��ɣ��ر��ļ�
	fclose(data);

	//���ش��ļ���ȡ�Ľṹ��
	return img;
}

//�ͷŽṹ����ռ�õ��ڴ�
image* freeimg(image* img)
{
	if(NULL != img)
	{
		//�ͷŽṹ��ָ���ͼ������
		free(img->bits);
		//�ͷŽṹ�屾��
		free(img);

	}
	//����NULLָ�룬��ʾ�ͷųɹ�
	return NULL;
}

//����������չʾ�ṹ���д�Ĺ���
int main()
{
	//����ͼ�εĿ�͸�
	const int w = 37;
	const int h = 37;
	//������Ӧ��С�Ľṹ�壬�õ�ָ������ṹ���ָ��
	image* img = create(w,h);
	//��ͼ���ǻ������κͱ߿�
	draw(img);
	//��ʾͼ��
	print(img);

	//����ͼ��ṹ��
	save(img,"demo.img");
	//ͼ��ṹ���Ѿ������棬�����ͷų����е�ͼ��ṹ��
	img = freeimg(img);


	//���ļ���ȡͼ��ṹ��
	image* rimg = read("demo.img");
	//��ʾ��ȡ��ͼ��ṹ������֤��д����ȷ��
	print(rimg);
	//�ͷŶ�ȡ��ͼ��ṹ�塣
	rimg=freeimg(rimg);

	return 0;

}




















