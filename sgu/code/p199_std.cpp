#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
typedef pair<int, int> PII;
typedef pair<PII, int> PPI;

vector<PPI> people;
vector<int> x;
vector<int> record;

bool operator > (PII a, PII b)
{
	//if(a.first == b.first) return true;
	return a.second > b.second;
}

bool operator <= (PII a, PII b)
{
	if(a.first == b.first) return true;
	return a.second <= b.second;
}

bool cmp(PPI a, PPI b)
{
	if(a.first.first == b.first.first) return a.first.second > b.first.second;
	return a.first.first < b.first.first;
}

int binary_search(PII a)
{
	int l = 0, r = x.size() - 1;
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if(a > people[x[mid]].first) l = mid + 1;
		else r = mid - 1;
	}
	return r + 1;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		PII a;
		cin >> a.first >> a.second;
		people.push_back(PPI(a, i));
	}
	sort(people.begin(), people.end(), cmp);
	for(int i = 0; i < n; i++)
	{
		int pos = binary_search(people[i].first);
		if(pos == x.size())
			x.push_back(i);
		else
			x[pos] = i;
		record.push_back(pos);
	}
	cout << x.size() << endl;
	return 0;
	int a = x.size() - 1;
	PII b(INT_MAX, INT_MAX);
	for(int i = people.size() - 1; i >= 0; i--)
	{
		if(b <= people[i].first) continue;
		if(record[i] == a)
		{
			cout << people[i].second + 1 << " ";
			b = people[i].first;
			a--;
		}
	}
	cout << endl;
	// while(1);
	return 0;
}
