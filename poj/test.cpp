#include <cstdio>
//#include <pair>
#include <set>
using namespace std;
set<pair<int, int> > S;

int main()
{
	S.insert(make_pair(1, 1));
	S.insert(make_pair(1, 1));
	printf("%d\n", S.count(make_pair(2, 1)));
}
