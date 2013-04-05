#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
string str0, str1;

int main(){
	freopen("digits.in", "r", stdin);
	freopen("digits.out", "w", stdout);
	cin >> str0 >> str1;
	int len = str0.size();
	for(int i = 0; i < len; i ++){
		str0[i] = str0[i] + ((str0[i] - '0') ^ 1);
		int x = 0;
		for(int j = 0; j < len; j ++)
			if(str0[j] == '1')
				x += 1 << (len - j - 1);
		static int d[50];
		int nd = 0;
		int tmp = x;
		while(tmp)
			d[nd ++] = tmp % 3, tmp /= 3;
		if(nd == (int)str1.size() - 1)
			d[nd ++] = 0;
		int diff = 0;
		for(int j = nd - 1; j >= 0; j --)
			if(d[j] != str1[nd - j - 1] - '0')
				diff ++;
		if(diff == 1){
			printf("%d\n", x);
			return 0;
		}
		str0[i] = str0[i] + ((str0[i] - '0') ^ 1);
	}
}
