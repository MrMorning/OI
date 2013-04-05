#include <cstdio>
int main()
{
	int n;
	scanf("%d", &n);
	if(n < 9)
		printf("0\n");
	else if(n == 9)
		printf("8");
	else
	{
		printf("72");
		for(int i = 0; i < n - 10; i ++)
			printf("0");
		printf("\n");
	}
}
