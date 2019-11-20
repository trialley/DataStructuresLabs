#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"zjslib.h"
#include<math.h>
void treatment_of_infix(char* infix){
	//此函数将中缀表达式中的负数x全部变成0-x的形式
	//0只有两种情况：(- 或者是表达式一开始就是一个-
	//思路是将-前插入一个0
	//实践检验在测试集input4中没有犯错.
	int len = strlen(infix);
	if(infix[0]=='-'){
		for(int i=len;i>=0;i--){
			infix[i+1] = infix[i];
		}//这样就全部后移了一位，空出infix[0]
		infix[0] = '0';
		len++;
	}
	for(int i=1;i<len;i++){
		if(infix[i]=='-'&&infix[i-1]=='('){
			for(int j=len;j>=i;j--){
				infix[j+1] = infix[j];
			}//这样就全部后移了一位，空出infix[i]
			infix[i] = '0';
			len++;
		}
	}
	return; //函数结束，自己写返回标识，不要过分依赖编译器自动补.
}
char* convertion_of_infix(char* infix){
	//此函数将中缀表达式转换成后缀表达式并返回指向后缀表达式的指针
	//由于后缀表达式是我显式声明的，因此被存放在heap里，直到我显式释放，这块空间都是安全的，由此可以返回指针.
	int len = strlen(infix);
	char* postfix = (char*)malloc(sizeof(char)*2*len);
	for(int i=0;i<2*len;i++) postfix[i] = '\0';
	//因为中缀表达式转后缀时括号被去掉了，所以这么长肯定够用，最后不要忘记补上一个'\0'以便使用者手动确定长度.
	if(postfix==NULL) return postfix;//空间分配异常处理.
	//下面开始转换.
    int j=0;
    arrstack<char> convertion_stack;
    for(int i=0; i<len; i++){
        if(infix[i]>='0' && infix[i]<='9'){
			//本来是遇到操作数直接入栈的，现在要检查这个操作数是否结束，并在结束后插入空格.
			for(;( infix[i]>='0' && infix[i]<='9' );i++) postfix[j++]=infix[i];
			postfix[j++]=' ';
			i--;
        }   //这使得每一个数字后面都有了一个空格，以便区分多位数字.
        else{
            if(infix[i]==')'){
                while(convertion_stack.top()!='('){
                    postfix[j++] = convertion_stack.top();
                    convertion_stack.pop();
                }
                convertion_stack.pop();
            }
            else if(infix[i]=='*'||infix[i]=='/'){
                if(!convertion_stack.empty())
                    if(convertion_stack.top()=='*'||convertion_stack.top()=='/'){
                        postfix[j++] = convertion_stack.top();
                        convertion_stack.pop();
                    }
                convertion_stack.push(infix[i]);
            }
            else if(infix[i]=='+'||infix[i]=='-'){
                if(!convertion_stack.empty())
                    if(convertion_stack.top()=='*'||convertion_stack.top()=='/'||convertion_stack.top()=='+'||convertion_stack.top()=='-'){
                        postfix[j++] = convertion_stack.top();
                        convertion_stack.pop();
                    }
                convertion_stack.push(infix[i]);
            }
            else
                convertion_stack.push(infix[i]);
        }
    }
    while(!convertion_stack.empty()){
        postfix[j++] = convertion_stack.top();
        convertion_stack.pop();
    }
	return postfix;
}
double calculation_of_postfix(char* postfix){
	//此函数计算后缀表达式的值并返回该值
	double result = 0.0;
	int len = strlen(postfix);
	arrstack<double> caculation_stack;
	//此处默认后缀表达式转换正确，故不设置检验.
	for(int i=0;i<len;i++){
		if(postfix[i]>='0'&&postfix[i]<='9'){
			double t = 0.0;
			if(postfix[i+1]==' '){
				t = (double)postfix[i] - 48.0;
				caculation_stack.push(t);
				i++;    //如果下一位是空格就跳过下一位.
			}
			else{
				int num_digit = 0;  //通过空格确定这是几位数，该变量表示数字位数.
				for(int j=0;postfix[i+j]!=' ';j++) num_digit++;
				int k = 0;
				for(int j=i+num_digit-1;j>=i;j--){
					t = t + ((double)postfix[j] - 48.0)*pow((double)10,k);
					k++;
				}
				caculation_stack.push(t);
				i = i + num_digit;  //跳过这个数字和空格.
			}
		}
		else{
			double right = caculation_stack.top();
			caculation_stack.pop();
			double left = caculation_stack.top();
			caculation_stack.pop();
			if(postfix[i]=='+') caculation_stack.push(left+right);
			if(postfix[i]=='-') caculation_stack.push(left-right);
			if(postfix[i]=='*') caculation_stack.push(left*right);
			if(postfix[i]=='/') caculation_stack.push(left/right);
		}
	}
	result = caculation_stack.top();
	caculation_stack.pop();
	return result;
}
int main(){
	while(1){
		char* infix = (char*)malloc(sizeof(char)*2600);
		//经统计，本次的测试数据中最长的表达式有2539个字符，所以使用2600，treatment_of_infix()将使字符串长度增加，最大可以增加到两倍.
		//这是为了省事，实际上应该使用智能化的空间分配方法.
		if(infix==NULL){
			printf("\n infix malloc fatal error! \n");
			return -1;
		}
		scanf("%s",&*infix);
		treatment_of_infix(infix);
			//printf("%s\n",infix);
		char* postfix = convertion_of_infix(infix);
		if(postfix==NULL){
			printf("\n postfix malloc fatal error! \n");
			return -2;
		}
			//printf("%s\n",postfix);
		double result = calculation_of_postfix(postfix);
			printf("%lf\n",result);
		free(infix);
		free(postfix);
	}
	return 0;
}

