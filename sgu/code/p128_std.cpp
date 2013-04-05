#include <cstdio>
#include <iostream> 
#include <cstdlib> 
#include <cstring> 

using namespace std; 

const int MAX = 30 * 20000; 
const int MAX_LEFT = -10010, MAX_RIGHT = 10010; 
int seg[MAX]; 
int n, point[10010][3]; 
int pre[MAX_RIGHT]; 

inline int left(int i) { return i << 1; } 
inline int right(int i) { return (i << 1) + 1; } 

int search(int a, int b, int l, int r, int n) 
{ 
	if(!seg[n]) return 0; 
	if(l == r) return seg[n]; 

	if(b <= (l + r) / 2) 
		return search(a, b, l , (l + r) / 2, left(n)); 
	if(a > (l + r) / 2) 
		return search(a, b, (l + r) / 2 + 1, r, right(n)); 

	return search(a, (l + r) / 2, l, (l + r) / 2, left(n)) || search((l + r) / 2 + 1, b, (l + r) / 2 + 1, r, right(n)); 
} 

void change(int n, int choice) 
{ 
	int _left = 0, _right = MAX_RIGHT * 2, pos = 1; 

	n += MAX_RIGHT; 
	while(_left != _right) 
	{ 
		seg[pos] += choice; 
		if(n <= (_left + _right) / 2) pos = left(pos), _right = (_left + _right) / 2; 
		else pos = right(pos), _left = (_left + _right) / 2 + 1; 
	} 
	seg[pos] += choice; 
} 

int cmp(const void *a, const void *b) 
{ 
	if(*(int *)a == *(int *)b) return *((int *)a + 1) - *((int *)b + 1); 
	return *(int *)a - *(int *)b; 
} 

void init() 
{ 
	cin >> n; 
	for(int i = 0; i < n; i++) 
	{ 
		pre[i] = i; 
		point[i][2] = i; 
		cin >> point[i][0] >> point[i][1]; 
	} 
} 

inline void swap(int *a, int *b) 
{ 
	int tmp = *a; 
	*a = *b; 
	*b = tmp; 
} 

int root(int a) 
{ 
	if(pre[a] != a) 
		pre[a] = root(pre[a]); 
	return pre[a]; 
} 

void un(int a, int b) 
{ 
	a = root(a), b = root(b);
	if(a != b) 
		pre[b] = a; 
} 

int solve() 
{ 
	int sum = 0, point_in[10010][2], point_out[10010][2], line[10010][3]; 

	if(n & 1) return 0; 
	qsort(point, n, sizeof(point[0]), cmp); 
	for(int i = 0; i < n; i += 2) 
	{ 
		if(point[i][0] != point[i + 1][0]) return 0; 
		sum += point[i + 1][1] - point[i][1]; 
		point_in[i / 2][0] = point[i][1], point_in[i / 2][1] = point[i][0]; 
		point_out[i / 2][0] = point[i + 1][1], point_out[i / 2][1] = point[i][0]; 
		un(point[i][2], point[i + 1][2]); 
	} 

	for(int i = 0; i < n; i++) swap(&point[i][0], &point[i][1]); 
	qsort(point, n, sizeof(point[0]), cmp); 
	for(int i = 0; i < n; i += 2) 
	{ 
		if(point[i][0] != point[i + 1][0]) return 0; 
		sum += point[i + 1][1] - point[i][1]; 
		line[i / 2][0] = point[i][0], line[i / 2][1] = point[i][1], line[i / 2][2] = point[i + 1][1]; 
		un(point[i][2], point[i + 1][2]); 
	} 

	for(int i = 1; i < n; i++) 
	{ 
		if(root(i) != root(i - 1)) 
			return 0; 
	} 

	qsort(point_in, n / 2, sizeof(point_in[0]), cmp); 
	qsort(point_out, n / 2, sizeof(point_out[0]), cmp); 
	qsort(line, n / 2, sizeof(line[0]), cmp); 

	int p_line = -1, p_in = 0, p_out = 0; 
	while(++p_line != n / 2) 
	{ 
		while(point_out[p_out][0] < line[p_line][0] && p_out < n / 2) 
		{ 
			change(point_out[p_out][1], -1); 
			p_out++; 
		} 
		while(point_in[p_in][0] <= line[p_line][0] && p_in < n / 2) 
		{ 
			change(point_in[p_in][1], 1); 
			p_in++; 
		} 
		if(line[p_line][1] + 1 > line[p_line][2] - 1) 
			continue; 
		if(search(line[p_line][1] + 1 + MAX_RIGHT, line[p_line][2] - 1 + MAX_RIGHT, 0, 2 * MAX_RIGHT, 1)) 
			return 0; 
	} 
	return sum; 
} 
int main() 
{ 
	freopen("t.in", "r", stdin);
	init(); 
	cout << solve() << endl; 
} 
