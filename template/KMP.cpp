#include <cstring>
#include <string>

using namespace std;

const int N_MAX = 1000;

int pre[N_MAX];

void initKMP(const string &input){
	static char str[N_MAX];
	int n = input.size();
	for(int i = 1; i <= n; i ++)
		str[i] = input[i - 1];
	pre[0] = -1;
	int t = -1;
	for(int i = 1; i <= n; i ++){
		while(t >= 0 && str[t + 1] != str[i])
			t = pre[t];
		if(str[t + 1] == str[i])
			t ++;
		pre[i] = t;
	}
}

int main(){
}
