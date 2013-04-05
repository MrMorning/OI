#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
string str;
char stack[1111];
int main(){
	cin >> str;
	int top = 0;
	for(int i = 0; i < (int)str.size(); i ++)
		if(str[i] == '<'){
			if(str[i + 1] == '/'){
				char ch = str[i + 2];
				top --;
				for(int k = 0; k < top; k ++)
					printf("  ");
				printf("</%c>\n", ch);
				i += 3;
			}
			else{
				char ch = str[i + 1];
				for(int k = 0; k < top; k ++)
					printf("  ");
				printf("<%c>\n", ch);
				stack[top ++] = ch;
				i += 2;
			}
		}
}
