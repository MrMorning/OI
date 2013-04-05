#include <string>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <iostream>
using namespace std;
int info[4][55][55];

int main() {
	freopen("raw.in", "r", stdin);
	freopen("cipher10.in", "w", stdout);
	string str, totstr;
	while ( cin >> str )
		totstr += str;
	int len = totstr.size();
	int nRow = 0, nCol = 0;
	{
		int quotCnt = 0;
		for ( int i = 0; i < len; i ++ ) {
			if ( totstr[i] == '}' ) {
				break;
			}
			quotCnt += totstr[i] == '"';
		}
		nRow = quotCnt/2;
		for ( int i = 2; i < len; i ++ ) {
			if ( totstr[i] == '"' ) 
				break;
			nCol ++;
		}
	}
	printf("%d %d\n", nRow, nCol);

	string curstr;
	bool inside = false;
	int rowPtr = 0, colPtr = 0, matPtr = 0;
	for ( int i = 0; i < len; i ++ ) {
		if ( totstr[i] == '{' ) {
			matPtr++;
			rowPtr = 0;
		}
		else if ( totstr[i] == '}' || totstr[i] == ',' ) {
		} else if ( totstr[i] == '"' ) {
			if ( inside ) {
				colPtr = 0;
			} else {
				rowPtr ++;
			}
			inside ^= 1;
		} else {
			assert(isdigit(totstr[i]));
			colPtr++;
			info[matPtr][rowPtr][colPtr] = totstr[i] - '0';
		}
	}
	assert(matPtr == 3);
	for ( int i = 0; i < nRow; i ++, printf("\n"))
		for ( int j = 0; j < nCol; j ++ )
			printf("%d ", info[1][i+1][j+1]*100
					+ info[2][i+1][j+1]*10
					+ info[3][i+1][j+1]);
}
