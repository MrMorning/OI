#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct Segment
{
	int l, r, h, type;
} seg[10000];
int segNum;

vector<int> vec;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &segNum);
	for(int i = 0, x1, y1, x2, y2; i < segNum; i ++)
	{
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if(x1 == x2)
			seg[i].h = x1, seg[i].l = min(y1, y2), seg[i].r = max(y1, y2), seg[i].type = 1;
		else
			seg[i].h = y1, seg[i].l = min(x1, x2), seg[i].r = max(x1, x2), seg[i].type = 0;
	}
	int xt, yt;
	scanf("%d%d", &xt, &yt);
	for(int i = 0; i < segNum; i ++)
		if(seg[i].type == 0)
		{
			if(seg[i].l <= xt && xt < seg[i].r)
				vec.push_back(seg[i].h);
		}
		else
			if(seg[i].h == xt)
				if(seg[i].l <= yt && yt <= seg[i].r)
				{
					printf("BORDER\n");
					return 0;
				}
	sort(vec.begin(), vec.end());
	for(int i = 1; i < (int)vec.size(); i ++)
		if(vec[i - 1] == yt || yt == vec[i])
		{
			printf("BORDER\n");
			return 0;
		}
		else if(vec[i - 1] < yt && yt < vec[i])
		{
			if(i & 1)
				printf("INSIDE\n");
			else
				printf("OUTSIDE\n");
			return 0;
		}
	printf("OUTSIDE\n");
}
