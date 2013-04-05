/*
 * Date: Mon Jan 17 22:14:48 CST 2011
 * Author: csimstu
 * Problem: 487-3279
 * Source: poj 1002
 * Submission: WA
 * Algorithm: easy hash
 */
#include <cstdio>
#include <cstdlib>
const int MAP[26] = {
	2, 2, 2,
	3, 3, 3,
	4, 4, 4,
	5, 5, 5,
	6, 6, 6,
	7, -1, 7, 7,
	8, 8, 8,
	9, 9, 9, -1
};
int n, hash[10000003];
int ans[100005], ansNum;

int compare(const void *a, const void *b){
	return *(int*)a - *(int*)b;
}

int convert(char ch){
	if('0' <= ch && ch <= '9')
		return ch - '0';
	else
		return MAP[ch - 'A'];
}

int main(){
	scanf("%d\n", &n);
	bool isDuplicate = false;
	while(n --){
		char str[100];
		scanf("%s\n", str);
		int cnt = 0, i = -1, x = 0;
		while(cnt < 7)
			if(str[++ i] != '-'){
				cnt ++;
				x = x * 10 + convert(str[i]);
			}
		if(hash[x]){
			isDuplicate = true;
			hash[x] ++;
		}
		else{
			ans[++ ansNum] = x;
			hash[x] = 1;
		}
	}
	if(! isDuplicate)
		printf("No duplicates.\n");
	else{
		qsort(ans + 1, ansNum, sizeof(int), compare);
		for(int i = 1; i <= ansNum; i ++){
			if(hash[ans[i]] <= 1) continue;
			int x = ans[i];
			int suf = x % 10000;
			int pre = x / 10000;
			if(pre < 10)
				printf("00%d", pre);
			else if(pre < 100)
				printf("0%d", pre);
			else
				printf("%d", pre);
			printf("-");
			if(suf < 10)
				printf("000%d", suf);
			else if(suf < 100)
				printf("00%d", suf);
			else if(suf < 1000)
				printf("0%d", suf);
			else
				printf("%d", suf);
			printf(" %d\n", hash[x]);
		}
	}
}
