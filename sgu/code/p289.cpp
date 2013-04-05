#include <cstdio>
#include <cassert>

#define NUL 0
#define X_POS 1
#define Y_POS 2

#define UNKNOWN -1
#define X_WIN 0
#define Y_WIN 1
#define DRAW 3
#define ILLE 4

int GET(int s, int i) {
	return (s >> 2 * i) & 3;
}

int SET(int s, int i, int x) {
	s = s & ~(3 << 2 * i);
	s |= x << 2 * i;
	return s;
}

bool done[1 << 18];
int memo[1 << 18];
int Q[1 << 18];
bool exist[1 << 18];

int isCertain(int s) {
	int cntNul = 0;
	int cntX = 0, cntY = 0;
	int winX = 0, winY = 0;
	for ( int x = 0; x < 3; x ++ )
		for ( int y = 0; y < 3; y ++ )
			if ( GET(s, 3 * x + y) == X_POS )
				cntX ++;
			else if ( GET(s, 3 * x + y) == Y_POS )
				cntY ++;
			else if ( GET(s, 3 * x + y) == NUL )
			   cntNul ++;	
	if ( !(cntY == cntX || cntX == cntY + 1) )
		assert(0);

	for ( int x = 0; x < 3; x ++ ) {
		cntX = cntY = 0;
		for ( int y = 0; y < 3; y ++ )
			if ( GET(s, 3 * x + y) == X_POS )
				cntX ++;
			else if ( GET(s, 3 * x + y) == Y_POS )
				cntY ++;
		if ( cntX == 3 )
			winX ++;
		if ( cntY == 3 )
			winY ++;
	}
	for ( int y = 0; y < 3; y ++ ) {
		cntX = cntY = 0;
		for ( int x = 0; x < 3; x ++ )
			if ( GET(s, 3 * x + y) == X_POS )
				cntX ++;
			else if ( GET(s, 3 * x + y) == Y_POS )
				cntY ++;
		if ( cntX == 3 )
			winX ++;
		if ( cntY == 3 )
			winY ++;
	}
	cntX = cntY = 0;
	for ( int x = 0; x < 3; x ++ ) {
		if ( GET(s, 3 * x + x) == X_POS )
			cntX ++;
		else if ( GET(s, 3 * x + x) == Y_POS ) 
			cntY ++;
	}
	if ( cntX == 3 )
		winX ++;
	if ( cntY == 3 )
		winY ++;
	cntX = cntY = 0;
	for ( int x = 0; x < 3; x ++ ) {
		if ( GET(s, 3 * x + 2 - x) == X_POS )
			cntX ++;
		else if ( GET(s, 3 * x + 2 - x) == Y_POS ) 
			cntY ++;
	}
	if ( cntX == 3 )
		winX ++;
	if ( cntY == 3 )
		winY ++;

	if ( winX || winY )
		return winX ? X_WIN : Y_WIN;
	else if ( cntNul == 0 )
		return DRAW;
	return UNKNOWN;
}

void expand() {
	int qh = 0, qt = 0;
	Q[qt ++] = 0;
	exist[0] = true;
	while ( qh < qt ) {
		int s = Q[qh ++];
		if ( isCertain(s) != UNKNOWN )
			continue;
		int cntY = 0, cntX = 0;
		for ( int x = 0; x < 3; x ++ )
			for ( int y = 0; y < 3; y ++ )
				if ( GET(s, 3 * x + y) == X_POS )
					cntX ++;
				else if ( GET(s, 3 * x + y) == Y_POS )
					cntY ++;
		int who = cntX == cntY ? X_POS : Y_POS;
		for ( int x = 0; x < 3; x ++ )
			for ( int y = 0; y < 3; y ++ )
				if ( GET(s, 3 * x + y) == NUL ) {
					int ns = SET(s, 3 * x + y, who);
					if ( !exist[ns] ) {
						exist[ns] = true;
						Q[qt ++] = ns;
					}
				}
	}
}

int dp(int s) {
	if ( done[s] )
		return memo[s];
	done[s] = true;
	int &ret = memo[s] = 0;
	ret = isCertain(s);
	if ( ret != UNKNOWN )
		return ret;
	int cntY = 0, cntX = 0;
	for ( int x = 0; x < 3; x ++ )
		for ( int y = 0; y < 3; y ++ )
			if ( GET(s, 3 * x + y) == X_POS )
				cntX ++;
			else if ( GET(s, 3 * x + y) == Y_POS )
				cntY ++;
	int who = cntX == cntY ? X_POS : Y_POS;
	bool hasDraw = false;
	for ( int x = 0; x < 3; x ++ )
		for ( int y = 0; y < 3; y ++ )
			if ( GET(s, 3 * x + y) == NUL ) {
				int ns = SET(s, 3 * x + y, who);
				if ( dp(ns) == who - 1) 
					return ret = who - 1;
				else if ( dp(ns) == DRAW )
					hasDraw = true;
			}
	if ( hasDraw )
		ret = DRAW;
	else
		ret = 2 - who;
	return ret;
}

int main() {
	expand();
	while ( 1 ) {
		static char str[10];
		int curS = 0;
		for ( int i = 0; i < 3; i ++ ) {
			scanf("%s", str);
			if ( str[0] == 'Q' )
				break;
			for ( int j = 0; j < 3; j ++ ) {
				int val;
				if ( str[j] == 'X' )
					val = X_POS;
				else if ( str[j] == '0' )
					val = Y_POS;
				else
					val = NUL;	
				curS = SET(curS, i * 3 + j, val);
			}
		}
		if ( str[0] == 'Q' )
			break;
		if ( !exist[curS] ) {
			puts("Illegal position.");
			continue;
		}

		int res = dp(curS);
		if ( res == X_WIN )
			puts("X wins.");
		else if (res == Y_WIN )
			puts("0 wins.");	
		else 
			puts("Game is a draw.");
	}
}
