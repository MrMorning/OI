#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
typedef long long ll;

class TheBrickTowerEasyDivOne {
public:
	int find(int nR, int hR, int nB, int hB) {
		if ( hR == hB )
			return min(nR, nB) + max(min(nR-1,nB),min(nR,nB-1)) + 1;
		else
			return min(nR, nB) + min(nR-1, nB) + min(nR, nB-1) + 2;
	}
} cls;

int main() {
	freopen("brick.in", "r", stdin);
	freopen("brick.out", "w", stdout);
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	printf("%d\n", cls.find(a, b, c, d));
}
