#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define MAX 110
typedef struct
{
	char* p;
	int length;

}string;

string* creat()
{
	string* s;
	s = (string*)malloc(sizeof(string));
	s->length = 0;
	return s;
}
void assi(string* s1, char* s2)
{
	int i = 0;
	while (i != '\0')
	{
		s1->p[i] = s2[i];
		i++;
	}
	s1->length = i;
}//将字符串常量s2赋值给字符串变量s1
void FAIL(string* t, int f[])
{
	int j, k;
	f[0] = -1;
	j = 0;
	k = -1;
	while (j < t->length)
		if (k==-1|| t->p[j] == t->p[k])
		{
			k++;
			j++;
			f[j] = k;
			printf("%d ", j);
		}
		else
			k = f[k];
}//定义的失败函数

int search(string* s, string* t)
{
	int f[MAX], i = 0, j = 0;
	FAIL(t, f);
	while (i < s->length && j < t->length)
		if (j == -1 || s->p[i] == t->p[j])
		{
			i++;
			j++;
		}
		else
			j = f[j];
	if (j >= t->length)
		return i - t->length + 1;
	else return 0;
}

int main(void)
{
	char s[MAX], p[MAX];
	int  i=0 , j;//i作为主串数组下标，j作为目标串数组下标
	scanf("%s", s);
	scanf("%s", p);
	string* a;
	string*b;
	a=creat();
	b=creat();
	assi(a, s);
	assi(b, p);
	j=search(a, b);
	printf("\0");
	printf("%d", j);

	

}