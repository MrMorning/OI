#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
const int kNMax = 1010;
map<string, int> name2Idx;

struct Key {
	int in;
} key[kNMax];

struct Man {
	string name;
	int in;
} man[kNMax];

struct Door {
	int u, v;
} door[kNMax];

int parent[kNMax];
int roomRes1[kNMax], roomRes2[kNMax];
int manRes1[kNMax], manRes2[kNMax];
int keyRes1[kNMax], keyRes2[kNMax];
bool used[kNMax];

int nRoom, nDoor, nMan, nKey;

void noSol() {
	puts("NO");
	exit(0);
}

int find(int x) {
	return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void merge(int x, int y) {
	x = find(x), y = find(y);
	if ( x < y ) swap(x, y);
	if ( x != y ) parent[x] = y;
}

void solve(int roomRes[], int manRes[], int keyRes[]) {
	memset(used, 0, sizeof(used));
	for ( int i = 0; i < nRoom; i ++ )
		parent[i] = i;
	while ( 1 ) {
		bool changed = false;
		for ( int i = 0; i < nDoor; i ++ ) 
			if ( !used[i] ) {
				int t = find(man[key[i].in].in);
				if ( t == find(door[i].u) || t == find(door[i].v) ) {
					used[i] = true;
					changed = true;
					merge(door[i].u, door[i].v);
				}
			}
		if ( !changed ) break;
	}
	for ( int i = 0; i < nRoom; i ++ )
		roomRes[i] = find(i);
	for ( int i = 0; i < nMan; i ++ )
		manRes[i] = find(man[i].in);
	for ( int i = 0; i < nKey; i ++ )
		keyRes[i] = find(man[key[i].in].in);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &nRoom, &nDoor, &nMan);
	nKey = nDoor;
	for ( int i = 0; i < nDoor; i ++ ) { 
		scanf("%d%d", &door[i].u, &door[i].v);
		door[i].u--, door[i].v--;
	}
	for ( int i = 0; i < nMan; i ++ ) {
		cin >> man[i].name;
		name2Idx[man[i].name] = i;
		scanf("%d", &man[i].in);
		man[i].in --;
		int k;
		scanf("%d", &k);
		while ( k -- ) {
			int x;
			scanf("%d", &x);
			x--;
			key[x].in = i;
		}
	}
	solve(roomRes1, manRes1, keyRes1);

	for ( int i = 0; i < nMan; i ++ ) {
		string str;
		cin >> str;
		int id = name2Idx[str];
		scanf("%d", &man[id].in);
		man[id].in --;
		int k;
		scanf("%d", &k);
		while ( k -- ) {
			int x;
			scanf("%d", &x);
			x--;
			key[x].in = id;
		}
	}
	solve(roomRes2, manRes2, keyRes2);

	for ( int i = 0; i < nRoom; i ++ )
		if ( roomRes1[i] != roomRes2[i] ) noSol();
	for ( int i = 0; i < nMan; i ++ )
		if ( manRes1[i] != manRes2[i] ) noSol();
	for ( int i = 0; i < nKey; i ++ )
		if ( keyRes1[i] != keyRes2[i] ) noSol();
	puts("YES");
}
