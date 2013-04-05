#include <cstdio>
#include <cmath>

int main(){
	int n;
	scanf("%d", &n);
	int foot = n / 36,
		inch = (n - foot * 36) / 3,
		remainder = n - foot * 36 - inch * 3;
	if(remainder == 2)
		inch ++;
	if(inch == 12)
		inch = 0, foot ++;
	printf("%d %d\n", foot, inch);
}
