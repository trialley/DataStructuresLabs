#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"zjslib.h"
#include<math.h>
void treatment_of_infix(char* infix){
	//�˺�������׺���ʽ�еĸ���xȫ�����0-x����ʽ
	//0ֻ�����������(- �����Ǳ��ʽһ��ʼ����һ��-
	//˼·�ǽ�-ǰ����һ��0
	//ʵ�������ڲ��Լ�input4��û�з���.
	int len = strlen(infix);
	if(infix[0]=='-'){
		for(int i=len;i>=0;i--){
			infix[i+1] = infix[i];
		}//������ȫ��������һλ���ճ�infix[0]
		infix[0] = '0';
		len++;
	}
	for(int i=1;i<len;i++){
		if(infix[i]=='-'&&infix[i-1]=='('){
			for(int j=len;j>=i;j--){
				infix[j+1] = infix[j];
			}//������ȫ��������һλ���ճ�infix[i]
			infix[i] = '0';
			len++;
		}
	}
	return; //�����������Լ�д���ر�ʶ����Ҫ���������������Զ���.
}
char* convertion_of_infix(char* infix){
	//�˺�������׺���ʽת���ɺ�׺���ʽ������ָ���׺���ʽ��ָ��
	//���ں�׺���ʽ������ʽ�����ģ���˱������heap�ֱ������ʽ�ͷţ����ռ䶼�ǰ�ȫ�ģ��ɴ˿��Է���ָ��.
	int len = strlen(infix);
	char* postfix = (char*)malloc(sizeof(char)*2*len);
	for(int i=0;i<2*len;i++) postfix[i] = '\0';
	//��Ϊ��׺���ʽת��׺ʱ���ű�ȥ���ˣ�������ô���϶����ã����Ҫ���ǲ���һ��'\0'�Ա�ʹ�����ֶ�ȷ������.
	if(postfix==NULL) return postfix;//�ռ�����쳣����.
	//���濪ʼת��.
    int j=0;
    arrstack<char> convertion_stack;
    for(int i=0; i<len; i++){
        if(infix[i]>='0' && infix[i]<='9'){
			//����������������ֱ����ջ�ģ�����Ҫ�������������Ƿ���������ڽ��������ո�.
			for(;( infix[i]>='0' && infix[i]<='9' );i++) postfix[j++]=infix[i];
			postfix[j++]=' ';
			i--;
        }   //��ʹ��ÿһ�����ֺ��涼����һ���ո��Ա����ֶ�λ����.
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
	//�˺��������׺���ʽ��ֵ�����ظ�ֵ
	double result = 0.0;
	int len = strlen(postfix);
	arrstack<double> caculation_stack;
	//�˴�Ĭ�Ϻ�׺���ʽת����ȷ���ʲ����ü���.
	for(int i=0;i<len;i++){
		if(postfix[i]>='0'&&postfix[i]<='9'){
			double t = 0.0;
			if(postfix[i+1]==' '){
				t = (double)postfix[i] - 48.0;
				caculation_stack.push(t);
				i++;    //�����һλ�ǿո��������һλ.
			}
			else{
				int num_digit = 0;  //ͨ���ո�ȷ�����Ǽ�λ�����ñ�����ʾ����λ��.
				for(int j=0;postfix[i+j]!=' ';j++) num_digit++;
				int k = 0;
				for(int j=i+num_digit-1;j>=i;j--){
					t = t + ((double)postfix[j] - 48.0)*pow((double)10,k);
					k++;
				}
				caculation_stack.push(t);
				i = i + num_digit;  //����������ֺͿո�.
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
		//��ͳ�ƣ����εĲ�����������ı��ʽ��2539���ַ�������ʹ��2600��treatment_of_infix()��ʹ�ַ����������ӣ����������ӵ�����.
		//����Ϊ��ʡ�£�ʵ����Ӧ��ʹ�����ܻ��Ŀռ���䷽��.
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

