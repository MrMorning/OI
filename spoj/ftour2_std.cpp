#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

//#define DEBUG
#define MAXN 200001
#define MAXM (MAXN << 1)
#define BUFF_SIZE 262144
#define INF 252645136

#define MAX(a,b) ((a) > (b) ? (a) : (b))


char buff[BUFF_SIZE],*pend = buff + BUFF_SIZE,*ptr = pend;
bool neg;

#define READ \
do \
{ \
	if (ptr == pend) \
	{ \
		fread(buff,1,BUFF_SIZE,stdin); \
		ptr = buff; \
	} \
} \
while (0)

#define IS_NUM(x) ('0' <= (x) && (x) <= '9')
#define SCAN(x) \
do \
{ \
	x = 0; \
	neg = 0; \
	READ; \
	while (!IS_NUM(*ptr)) {ptr++; READ;} \
	if (*(ptr - 1) == '-') neg = 1; \
	while (IS_NUM(*ptr)) {x = x * 10 + (*ptr++) - '0'; READ;} \
	if (neg) x = -x; \
} \
while (0)

int fir[MAXN],next[MAXM],end[MAXM],cost[MAXM],ECnt;
int N,K,M,Ans;
bool Black[MAXN];

void AddEdge(int st,int ed,int c) {

	next[++ECnt] = fir[st];
	fir[st] = ECnt;
	end[ECnt] = ed;
	cost[ECnt] = c;
}

void PreWork() {

	scanf("%d %d %d",&N,&K,&M);
	for (int i = 1,tmp; i <= M; i++)
	{
		SCAN(tmp);
		Black[tmp] = 1;
	}
	for (int i = 1,st,ed,c; i < N; i++)

	{
		SCAN(st); SCAN(ed); SCAN(c);
		AddEdge(st,ed,c);
		AddEdge(ed,st,c);
	}
}

bool Masked[MAXN];

int GetGravity(int &S,int *Mptr) {

	static int que[MAXN],BSize[MAXN],dist[MAXN];
	static int Size[MAXN],prev[MAXN],Max[MAXN];
	int l = 0,r = 1;
	int Best = INF,BestNode,Res = Black[S];
	que[0] = S;
	BSize[0] = Black[S];
	Max[0] = 0;
	Size[0] = 1;
	dist[0] = 0;
	Mptr[BSize[0]] = 0;

	for (;l != r; l++)
		for (int now = fir[que[l]],v; now; now = next[now])
			if ((v = end[now]) != que[prev[l]] && !Masked[v])
			{
				que[r] = v;
				Size[r] = 1;
				Max[r] = 0;
				dist[r] = dist[l] + cost[now];
				if ((BSize[r] = BSize[l] + Black[v]) > Res) 
				{
					//printf("	in GetGravity : BSize[%d] = %d Upating..\n",que[r],BSize[r]);
					Res = BSize[r];
				}
				prev[r++] = l;
			}
	memset(Mptr,240,(Res + 1) << 2);
	for (int i = r - 1,t; i >= 0; i--)
	{
		if (dist[i] > Mptr[BSize[i]]) Mptr[BSize[i]] = dist[i]; 
		if ((t = r - Size[i]) > Max[i]) Max[i] = t;
		if (Max[i] < Best) {Best = Max[i]; BestNode = que[i];}

		Size[prev[i]] += Size[i];
		Max[prev[i]] = MAX(Max[prev[i]],Size[i]);
		//update infomation
	}
	S = BestNode;
	return Res;
}

int Mem[MAXN << 2];

struct Son {

	int Id,*jmp,BSize,c;

	friend bool operator < (const Son &a,const Son &b) {

		return a.BSize < b.BSize;
	}

} son[MAXN << 1];

int Solve(int u,int *Mptr,Son *s) { // void Solve([now pos,ptr1,ptr2,ptr3])

	static int g[MAXN];
#ifdef DEBUG
	int oldu = u;
#endif
	int cnt = -1,Bound,prev;
	int BSize = GetGravity(u,Mptr); //Chroot
	int *ptr = Mptr + BSize + 1;
	int x = Black[u]; 
	Masked[u] = 1; //prevent access violation
#ifdef DEBUG
	printf("Changed the root %d -> %d where BSize is %d\n",oldu,u,BSize);
	printf("\t ::%d ",Mptr - Mem);
	for (int *t = Mptr,i = 0; t <= ptr - 1; t++,i++)
		printf("%d[%d] ",i,*t);
	printf("\n");
#endif 
	for (int now = fir[u],v; now; now = next[now])
		if (!Masked[v = end[now]]) 
		{
			cnt++;
			s[cnt].BSize = Solve(v,ptr,s + cnt);
			s[cnt].Id = v;
			s[cnt].jmp = ptr;
#ifdef DEBUG
			printf("\t s[%d] jmp = %d\n",cnt,ptr - Mem);
#endif
			s[cnt].c = cost[now];
			ptr += s[cnt].BSize + 1;
		}
	if (cnt >= 0)
	{
		std::sort(s,s + cnt + 1);
		Bound = s[cnt].BSize + x;
		g[0] = -INF;
		memset(g + x,0,(Bound - x + 1) << 2); // clean
	//	for (int k = x; k <= Bound; k++) g[k] = 0; //clean
		for (int i = 0; i <= cnt; i++)
		{
			int Upper = (s[i].BSize + x > K) ? K : (s[i].BSize + x);
			for (int k = 0; k <= Upper; k++)
			{
				if (k - x >= 0 && s[i].jmp[k - x] != -INF) g[k] = MAX(g[k],s[i].jmp[k - x] + s[i].c); 
				if (k) g[k] = MAX(g[k],g[k - 1]);
				if (g[k] > Ans) Ans = g[k];
				// g[i][k] = MAX(g[i - 1][k],g[i][k - 1],pg[si][k]
			}

			if (i != cnt)
			{
				int U2 = s[i + 1].BSize > K ? K : s[i + 1].BSize;
				for (int k = 0,t; k <= U2; k++)
					if ((prev = K - k) >= 0)
					{
						if (prev > Upper) prev = Upper;
						if (g[prev] == -INF || s[i + 1].jmp[k] == -INF) continue;
						if ((t = s[i + 1].jmp[k] + s[i + 1].c + g[prev]) > Ans)  Ans = t;
					}
			}

		}
	}
#ifdef DEBUG
	printf("Exiting..\n");
#endif
	return BSize;
}

int main() {
	freopen("t.in", "r", stdin);
	PreWork();
	Solve(1,Mem,son);
	printf("%d\n",Ans);
	return 0;
}


