#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;

const int kPartyMax = 12 * 100010;
const int kEventMax = 40 * 100010;
const int kIdtMax = 12 * 100010;
const int kStkMax = kPartyMax;

vector<int> son[kPartyMax];
int pos[kPartyMax][2], father[kPartyMax];
int seqPtr = 0;

struct StackElement {
	int id, now;
	StackElement(){}
	StackElement(int _id, int _now):
		id(_id), now(_now){}
} stk[kStkMax];

void getDfsSeq(int root) {
	int top = 0;
	pos[root][0] = seqPtr++;
	stk[top++] = StackElement(root, 0);

	while ( top ) {
		StackElement &u = stk[top - 1];
		if ( u.now == (int)son[u.id].size() ) {
			pos[u.id][1] = seqPtr - 1;
			top --;
			continue;
		}
		int v = son[u.id][u.now ++];
		pos[v][0] = seqPtr++;
		stk[top++] = StackElement(v, 0);
	}
}

struct Query {
	int a, b, res;
} query[kPartyMax];
int nQuery;

void addQuery(int a, int b) {
	Query &T = query[nQuery++];
	T.a = a, T.b = b;
}

struct Quest {
	int id, a, b, flag;
} quest[kPartyMax];
int nQuest;

struct Pair {
	int a, b;
} pir[kPartyMax];

int nParty, nPair;

void addQuest(int id, int a, int b, int flag) {
	Quest &T = quest[nQuest++];
	T.id = id, T.a = a, T.b = b, T.flag = flag;
}
#define PAIR 0
#define QUEST 1
struct Event {
	int type, key, id;
	Event(){}
	Event(int _tt, int _kk, int _ii):
		type(_tt), key(_kk), id(_ii){}
	bool operator< (const Event &e) const {
		return key < e.key || (key == e.key && type < e.type);
	}
} event[kEventMax];
int nEvent;

struct IndexTree {
	int ele[kIdtMax];
	void add(int i) {
		i += 5;
		for ( ; i < kIdtMax; i += i & -i )
			ele[i]++;
	}
	int sum(int i) {
		i += 5;
		int res = 0;
		for ( ; i; i -= i & -i )
			res += ele[i];
		return res;
	}
} idt;

void answerQuest() {
	for ( int i = 0; i < nPair; i ++ )
		event[nEvent++] = Event(PAIR, pos[pir[i].a][0], i);
	for ( int i = 0; i < nQuest; i ++ )
		event[nEvent++] = Event(QUEST, quest[i].a, i);
	sort(event, event + nEvent);
	for ( int i = 0; i < nEvent; i ++ ) {
		Event &e = event[i];
		if ( e.type == PAIR ) 
			idt.add(pos[pir[e.id].b][0]);
		else 
			query[quest[e.id].id].res += quest[e.id].flag * idt.sum(quest[e.id].b);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	memset(father, -1, sizeof(father));

	scanf("%d%d", &nParty, &nPair);
	for ( int i = 0; i < nPair; i ++ ) {
		scanf("%d%d", &pir[i].a, &pir[i].b);
		pir[i].a --, pir[i].b --;
	}
	int nOprt;
	scanf("%d", &nOprt);
	for ( int i = 0; i < nOprt; i ++ ) {
		int type, a, b;
		scanf("%d", &type);
		scanf("%d%d", &a, &b);
		a --, b --;
		if ( type == 1 ) 
			addQuery(a, b);
		else {
			son[nParty].push_back(a);
			son[nParty].push_back(b);
			father[a] = father[b] = nParty;
			nParty++; 
		}
	}
	int root = nParty++;
	for ( int i = 0; i < nParty - 1; i ++ )
		if ( father[i] == -1 )
			son[root].push_back(i), father[i] = root;
	getDfsSeq(root);

	for ( int i = 0; i < nQuery; i ++ ) {
		int a = query[i].a, b = query[i].b;
		addQuest(i, pos[a][1], pos[b][1], 1);
		addQuest(i, pos[a][0] - 1, pos[b][1], -1);
		addQuest(i, pos[a][1], pos[b][0] - 1, -1);
		addQuest(i, pos[a][0] - 1, pos[b][0] - 1, 1);
	}

	answerQuest();
	for ( int i = 0; i < nQuery; i ++ )
		printf("%s\n", query[i].res > 0 ? "YES" : "NO");
}
