#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int BASE = 29;
const int N_MAX = 1000010;

char sa[N_MAX], sb[N_MAX], si[N_MAX];
int xsa[N_MAX], xsb[N_MAX], xsi[N_MAX];
int pow[N_MAX];

void initPreSum(char *str, int n, int *res){
	for(int i = 0; i < n; i ++)
		res[i] = (i ? res[i - 1] : 0) * BASE + (str[i]);
}
int getHash(int *s, int l, int r){
	if(l > r)
		return 0;
	return s[r] - (l ? s[l - 1] : 0) * pow[r - l + 1];
}
int main(){
	freopen("t.in", "r", stdin);
	gets(sa);
	gets(sb);
	int na = strlen(sa),
		nb = strlen(sb);
	if(na != nb){
		printf("-1 -1\n");
		return 0;
	}
	int n = na;
	pow[0] = 1;
	for(int i = 1; i <= n; i ++)
		pow[i] = pow[i - 1] * BASE;
	for(int i = 0; i < na; i ++)
		si[i] = sa[na - i - 1];
	initPreSum(sa, n, xsa);
	initPreSum(sb, n, xsb);
	initPreSum(si, n, xsi);
	int ansI = -1, ansJ = -1;
	for(int i = 0; i < n - 1; i ++){
		if(getHash(xsi, n - i - 1, n - 1) == getHash(xsb, n - i - 1, n - 1)){
			int lb = i + 1, rb = n - 1;
			for(int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2){
			}
			while(j > i && (getHash(xsa, i + 1, j - 1) != getHash(xsb, 0, j - i - 2) 
						|| getHash(xsi, 0, n - j - 1) != getHash(xsb, j - i - 1, n - i - 2)))
				j --;
			if(j == i)
				continue;
			while(j - 1 > i && getHash(xsa, i + 1, j - 2) != getHash(xsb, 0, j - i - 3) 
						&& getHash(xsi, 0, n - j) != getHash(xsb, j - i - 2, n - i - 2))
				j --;
			if(i > ansI)
				ansI = i, ansJ = j;
			else if(i == ansI && j < ansJ)
				ansJ = j;
		}
	}
	printf("%d %d\n", ansI, ansJ);
}
