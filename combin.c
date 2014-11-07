#include<stdlib.h>

float* combine(float * data,int num)//参数num表示有4类语音信号要合并
{	
	int i,j;
	int len=400;	//待合并的信号的长度是len=400;以后可能修改
	float* newData;	//返回指针
	newData=(float*)malloc(sizeof(float)*len*num);
	float* Data=newData;
	for (i=0;i<num;i++)
	{	
		for(j=0;j<len;j++)
		{
			*(Data)++=data[j];
		}
		
	}
	return newData;
}
