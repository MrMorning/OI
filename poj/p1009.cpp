/*
 * Date: Tue Jan 18 22:54:49 CST 2011
 * Author: csimstu
 * Prob: Edge Detection
 * Source: poj 1009
 * Algorithm: 离散化+事件点+模拟
 */
#include <cstdio>
#include <set>
#define MAXN 2011

using std::set;

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int abs(int x){
	return x > 0 ? x : -x ;
}

struct Interval{
	int value, l, r;
	Interval(){};
	Interval(int _value, int _l, int _r):value(_value), l(_l), r(_r){};
} interval[MAXN];

struct Answer{
	int result, len;
	Answer(){};
	Answer(int _result, int _len):result(_result), len(_len){};
}ans[MAXN << 2];

int width, height, total, intervalNum, ansNum;
set<int> eventPoint;

inline int up(int k){
	if(k == -1) return -1;
	return (k > width) ? k - width : -1;
}

inline int down(int k){
	if(k == -1) return -1;
	return (k <= (height - 1) * width) ? k + width : -1;
}

inline int left(int k){
	if(k == -1) return -1;
	return (k % width != 1) ? k - 1 : -1;
}
inline int right(int k){
	if(k == -1) return -1;
	return (k % width != 0) ? k + 1 : -1;
}

int getValue(int k){
	int l = 1, r = intervalNum, mid = (l + r) / 2;
	while(l < r){
		if(k <= interval[mid].r && interval[mid].l <= k)
			return interval[mid].value;
		else{
			if(k < interval[mid].l)
				r = mid - 1;
			else
				l = mid + 1;
		}
		mid = (l + r) / 2;
	}
	return interval[mid].value;
}

int getResult(int k){
	int tmp = getValue(k), kResult = 0;
	if(up(k) != -1)
		kResult = max(kResult, abs(tmp - getValue(up(k))));
	if(down(k) != -1)
		kResult = max(kResult, abs(tmp - getValue(down(k))));
	if(left(k) != -1)
		kResult = max(kResult, abs(tmp - getValue(left(k))));
	if(right(k) != -1)
		kResult = max(kResult, abs(tmp - getValue(right(k))));
	if(up(left(k)) != -1)
		kResult = max(kResult, abs(tmp - getValue(up(left(k)))));
	if(down(left(k)) != -1)
		kResult = max(kResult, abs(tmp - getValue(down(left(k)))));
	if(up(right((k))) != -1)
		kResult = max(kResult, abs(tmp - getValue(up(right((k))))));
	if(down(right(k)) != -1)
		kResult = max(kResult, abs(tmp - getValue(down(right(k)))));
	return kResult;
}

int main(){
	freopen("t.in", "r", stdin);
	while(! feof(stdin)){
		scanf("%d\n", &width);
		if(width == 0)
			break;
		int lenCnt = 0;
		eventPoint.clear();
		intervalNum = ansNum = total = 0;
		while(1){
			int value, len;
			scanf("%d %d", &value, &len);
			total += len;
			if(len == 0)
				break;
			interval[++ intervalNum] = Interval(value, lenCnt + 1, lenCnt + len);
			lenCnt += len;
		}
		height = total / width;
		for(int i = 1; i <= intervalNum; i ++){
			eventPoint.insert(interval[i].l);
			if(up(interval[i].l) != -1)
				eventPoint.insert(up(interval[i].l));
			if(down(interval[i].l) != -1)
				eventPoint.insert(down(interval[i].l));
			eventPoint.insert(interval[i].r);
			if(up(interval[i].r) != -1)
				eventPoint.insert(up(interval[i].r));
			if(down(interval[i].r) != -1)
				eventPoint.insert(down(interval[i].r));
			if(eventPoint.find(36) != eventPoint.end())
				printf("lal");
		}
		int pre = 0;
		for(set<int>::iterator it = eventPoint.begin(); it != eventPoint.end(); it ++){
			int cur = *it;
			if(cur - pre - 1 > 0)
				ans[++ ansNum] = Answer(getResult(cur - 1), cur - pre - 1);
			ans[++ ansNum] = Answer(getResult(cur), 1);
			pre = cur;
		}
		int cnt = 0;
		printf("%d\n", width);
		for(int i = 1; i <= ansNum; i ++){
			if(i != ansNum && ans[i].result == ans[i+1].result)
				cnt += ans[i].len;
			else{
				cnt += ans[i].len;
				printf("%d %d\n", ans[i].result, cnt);
				cnt = 0;
			}
		}
		printf("0 0\n");
	}
	printf("0\n");
}
