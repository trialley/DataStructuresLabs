//关于堆栈相对位置及生长方向的测试代码
//关于BSS和DATA区生长方向和相对位置的测试代码
#include<stdio.h>
#include<stdlib.h>

int g;
static int __g; //此二者在BSS区
int _g = 123;
static int ___g = 123;  //此二者在DATA区
//经测试BSS DATA区都是向上生长的，而且相对位置比较靠近内存0端
int main()
{
    int* a = (int*)malloc(sizeof(int)*10);
    int* b = (int*)malloc(sizeof(int)*10);
    printf("ab指向的内存地址：\n");
    printf("%d\n",a);
    printf("%d\n",b);
	printf("ab本身的地址：\n");
    printf("%d\n",&a);
    printf("%d\n",&b);
	printf("g的地址：\n");
    printf("%d\n",&g);
    printf("%d\n",&__g);
    printf("%d\n",&_g);
    printf("%d\n",&___g);
	//汇编代码应该是先分配a再分配b，因此ab先后输出就可以显示生长方向。
	//生长方向是和认知相符合的
	//但是堆栈相对位置不对
	//测试结果显示，从内存0端到内存顶端，分别是：DATA BSS 栈 堆
	//按理说应该是： DATA BSS 堆 栈
	//代码段无法测试，因此只好默认它在DATA的近0端
}
