/*
 * Date: Tue Jan 18 07:52:42 CST 2011
 * Author: csimstu
 * Problem: Exponentiation
 * Source: poj 1001
 * Submission: A
 * Algorithm: high-precision
 */
#include <cstdio>
#include <cstring>
#define MAXLEN 10000

class BigInt{
	public:
		int num[MAXLEN], len;
		BigInt(){
			memset(num, 0, sizeof(num));
			len = 0;
		}

};;

BigInt operator*(const BigInt &a, const BigInt &b){
	BigInt c;
	c.len = a.len + b.len;
	for(int i = 1; i <= a.len; i ++)
		for(int j = 1; j <= b.len; j ++)
			c.num[i + j - 1] += a.num[i] * b.num[j];
	for(int i = 1; i <= c.len; i ++){
		c.num[i + 1] += c.num[i] / 10;
		c.num[i] %= 10;
	}
	while(c.num[c.len] == 0)
		c.len --;
	return c;
}

int main(){
	freopen("t.in", "r", stdin);
	char str[MAXLEN];
	int times, pointPos;
	while(! feof(stdin)){
		scanf("%s %d\n", str, &times);
		BigInt x;
		if(strchr(str, '.') ==NULL)
			x.len = strlen(str);
		else
			x.len = strlen(str) - 1;
		bool pointFound = false;
		pointPos = -1;
		for(int i = 0; i < strlen(str); i ++){
			if(str[i] == '.'){
				pointPos = x.len - i;
				pointFound = true;
				continue;
			}
			x.num[x.len - i + pointFound] = str[i] - '0';
		}
		pointPos *= times; 
		BigInt y;
		y.len = 1;
		y.num[1] = 1;
		while(times --)
			y = y * x;
		int zeroPoint = 0;
		while(y.num[zeroPoint + 1] == 0)
			zeroPoint ++;
		if(pointPos > 0){
			for(int i = y.len; i > pointPos; i --)
				printf("%d", y.num[i]);
			if(zeroPoint < pointPos)
				printf(".");
			for(int i = pointPos; i > zeroPoint ; i --)
				printf("%d", y.num[i]);
		}
		else
			for(int i = y.len; i >= 1; i --)
				printf("%d", y.num[i]);
		printf("\n");
	}
}
