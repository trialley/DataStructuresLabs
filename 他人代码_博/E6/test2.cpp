//���ڶ�ջ���λ�ü���������Ĳ��Դ���
//����BSS��DATA��������������λ�õĲ��Դ���
#include<stdio.h>
#include<stdlib.h>

int g;
static int __g; //�˶�����BSS��
int _g = 123;
static int ___g = 123;  //�˶�����DATA��
//������BSS DATA���������������ģ��������λ�ñȽϿ����ڴ�0��
int main()
{
    int* a = (int*)malloc(sizeof(int)*10);
    int* b = (int*)malloc(sizeof(int)*10);
    printf("abָ����ڴ��ַ��\n");
    printf("%d\n",a);
    printf("%d\n",b);
	printf("ab����ĵ�ַ��\n");
    printf("%d\n",&a);
    printf("%d\n",&b);
	printf("g�ĵ�ַ��\n");
    printf("%d\n",&g);
    printf("%d\n",&__g);
    printf("%d\n",&_g);
    printf("%d\n",&___g);
	//������Ӧ�����ȷ���a�ٷ���b�����ab�Ⱥ�����Ϳ�����ʾ��������
	//���������Ǻ���֪����ϵ�
	//���Ƕ�ջ���λ�ò���
	//���Խ����ʾ�����ڴ�0�˵��ڴ涥�ˣ��ֱ��ǣ�DATA BSS ջ ��
	//����˵Ӧ���ǣ� DATA BSS �� ջ
	//������޷����ԣ����ֻ��Ĭ������DATA�Ľ�0��
}
