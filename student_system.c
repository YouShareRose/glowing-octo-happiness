#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

struct student
{
		UINT32 number;
		UINT8 name[20];
		UINT16 age;
		struct student *next;
};

UINT8 NUM=0;
struct student *head=NULL;
	
struct student *add_student();
struct student *delete_student();
int print_list(struct student *head);

int main(void)
{
		UINT8 select=0;
		while(1)
		{
			printf("Select the operation:\n1---->Add a student\n
2---->Delete a student\n
0---->Exit\n");
			scanf("%d",&select);
			switch(select)
			{
				case 0:
					exit(0); break;  /*输入0，结束程序*/
				case 1:
					head = add_student(); break;   /*输入1，添加学生信息*/
				case 2:
					head = delete_student(); break;   /*输入2，删除学生信息*/
				default:
					break;
			}
			print_list(head);
		}
		return 0;
}

struct student *add_student()
{
		static struct student *p1, *p2;
		UINT8 flag=0;
		p2 = (struct student*) malloc(sizeof(struct student));/*p2指向新创建的结构体内存空间*/
		if(p2 == NULL)
		{
			printf("error, not enough memory to allocate buffer!\n");
			exit(1);         /* malloc出错退出*/
		}
		memset(p2,0,sizeof(struct student));   /*将新创建的结构体p2的成员值初始化为0/
		printf("Please input student's number:");
		scanf("%d",&p2->number);   /*输入学号*/
		printf("Please input student's name:");
		scanf("%s",p2->name);   /*输入姓名*/
		printf("Please input student's age:");
		scanf("%d",&p2->age);   /*输入年龄*/
		printf("Do you want to add this student info? Y:YES N:NO\n");  /*确认添加信息*/
		scanf("%s",&flag);
		if(flag == 'Y')    /*确认添加*/
		{
			NUM++;       /*学生数目加1*/
		}
		else
		{
			return head;  /*不添加，返回链表头结点*/
		}
		if(NUM==1)   /*头结点*/
		{
			p1 = p2;   /*将p1、p2、head均指向头结点*/
			head = p1;
		}
		else
		{
			p1->next = p2;
			p1 = p2;   /*p1、p2指向下一个节点*/
		}
		p1->next = NULL;   /*链表尾节点*/
		return head;
}

struct student *delete_student()
{
		struct student *p,*del;
		UINT16 num;
		printf("Please input the student's number you want to delete:");
		scanf("%d",&num);   /*输入将要删除的学生学号*/
		if(head == NULL)
		{
			printf("No student ifno!\n");
			return NULL;
		}
		p = head;
		del = head;
		if(del->number == num)   /*想要删除的节点是否是头结点*/
		{
			head = del->next;
			del->next = NULL;
			free(del);   /*删除节点后，释放该节点的内存空间*/
			return head;
		}
		else   /*根据num的值继续查找想要删除的节点*/
		{
			while(del!=NULL)
			{
				del = p->next;
				if(del->number == num)
				{
					printf("The student you want to delete is :%s\n",del->name);
					p->next = del->next;
					free(del);    /*删除节点后，释放该节点的内存空间*/
					return head;
				}
				else
				{
					p = del;
				}
			}
			printf("No this number student!\n");
		}
		return head;
}

int print_list(struct student *head)
{
		struct student *p;
		p = head;
		if(p == NULL)   /*链表为空，打印提示信息*/
		{
			printf("There is no student's information!\n");
			return -1;
		}
		else
		{
			do{
				printf("number: %d\n",p->number);
				printf("name: %s\n",p->name);
				printf("age: %d\n",p->age);
				p = p->next;
			}while(p != NULL);   /*循环打印各个节点的学生信息*/
		}
		return 0;
}
