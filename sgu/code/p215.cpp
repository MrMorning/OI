#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
using namespace std;

const int kNMax = 100000;

int match[kNMax];

struct DS {
	int p[kNMax];
	int find(int x) { return p[x]==x?x:p[x]=find(p[x]); }
	void merge(int x, int y) {
		x = find(x), y = find(y);
		assert(x != y);
		p[x] = y;
	}
} ds;

map<string, int> id;
string name[kNMax];
int nVar;
bool defined[kNMax];

int sgn(int x) {
	if ( x == 0 ) return 0;
	return x > 0 ? 1 : -1;
}

int myPow(int a, int n) {
	if ( a == 0 && n == 0 ) return 0;
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = a * a;
		if ( n & 1 )
			res = res * a;
	}
	return res;
}

int calcMatch(const string &s, int i) {
	assert(s[i] == '(');
	int top = 1;
	for ( int j = i+1; ; j ++ )
		if ( s[j] == '(' ) top ++;
		else if ( s[j] == ')' ) {
			top --;
			if ( top == 0 ) return j;
		}
}

string eatSpace(string s) {
	string res;
	int n = s.size();
	for ( int i = 0; i < n; i ++ )
		if ( s[i] != ' ' )
			res += s[i];
	return res;
}

string wrapNumber(string s) {
	for ( int i = 0; i < (int)s.size(); i ++ )
		if ( isdigit(s[i]) ) {
			s.insert(i, "(");
			i++;
			while ( isdigit(s[i+1]) )
				i++;
			s.insert(i+1, ")");
		}
	return s;
}

string wrapUnary(string s) {
	for ( int i = 0; i < (int)s.size(); i ++ )
		if ( s[i] == '+' || s[i] == '-' ) 
			if ( i == 0 || s[i-1] != ')' ) {
				int flag = s[i]=='+'?1:-1;
				int st = i;
				while ( i+1 < (int)s.size() && 
						(s[i+1] == '+' || s[i+1] == '-') )
					i++, flag *= s[i]=='+'?1:-1;
				s.erase(st, i-st+1);
				i = st;
				s.insert(st, flag==1?"+":"-");
				s.insert(st, "((0)");
				s.insert(calcMatch(s, i+5), ")");
			}
	return s;
}

int recur(int l, int r, const string &s) {
	if ( s[l] == '(' && match[l] == r )
		return recur(l+1, r-1, s);
	if ( isdigit(s[l]) ) {
		int res = 0;
		for ( int i = l; i <= r; i ++ )
			res = res*10 + (s[i]-'0');
		return res;
	}

	int posPow = -1, posMul = -1, posDiv = -1,
		posMod = -1, posAdd = -1, posMin = -1;
	for ( int i = l; i <= r; i ++ ) {
		switch(s[i]) {
			case '(': i = match[i]; break;
			case '^': posPow==-1?posPow = i:0; break;
			case '*': posMul = i; break;
			case '/': posDiv = i; break;
			case '%': posMod = i; break;
			case '+': posAdd = i; break;
			case '-': posMin = i; break;
		}
	}
	int t1 = max(posMul, max(posDiv, posMod)),
		t2 = max(posAdd, posMin);
	if ( t2 != -1 ) {
		if ( posAdd == t2 ) 
			return recur(l, posAdd-1, s) + recur(posAdd+1, r, s);
		else 
			return recur(l, posMin-1, s) - recur(posMin+1, r, s);
	} else if ( t1 != -1 ) {
		if ( posMul == t1 )
			return recur(l, posMul-1, s) * recur(posMul+1, r, s);
		else if ( posDiv == t1 ) {
			int a = recur(l, posDiv-1, s),
				b = recur(posDiv+1, r, s);
			return sgn(a)*sgn(b) * (abs(a)/abs(b));
		} else {
			int a = recur(l, posMod-1, s),
				b = recur(posMod+1, r, s);
			return sgn(a)*sgn(b) * (abs(a)%abs(b));
		}
	} else {
		assert(posPow != -1);
		int a = recur(l, posPow-1, s),
			b = recur(posPow+1, r, s);
		return myPow(a,b);
	} 
}

int calcVal(string s) {
	s = eatSpace(s);
	s = wrapNumber(s);
	s = wrapUnary(s);
	//cerr << s << endl;
	int n = s.size();
	memset(match, -1, sizeof(int)*n);
	vector<int> stk;
	for ( int i = 0; i < n; i ++ )
		if ( s[i] == '(' ) 
			stk.push_back(i);
		else if ( s[i] == ')' ) {
			match[stk.back()] = i;
			stk.pop_back();
		}
	return recur(0, n-1, s);
}

void recruit(string s) {
	if ( !id.count(s) ) {
		name[nVar] = s;
		id[s] = nVar;
		ds.p[nVar] = nVar;
		nVar++;
	}
}

string lowerAlpha(string s) {
	int n = s.size();
	string res = s;
	for ( int i = 0; i < n; i ++ )
		if ( 'A' <= res[i] && res[i] <= 'Z' )
			res[i] = (char)(res[i] - 'A' + 'a');
	return res;
}

string replaceDefine(string s) {
	string res;
	int n = s.size();
	for ( int i = 0; i < n; i ++ )
		if ( isdigit(s[i]) || isalpha(s[i]) ) {
			string tmp; tmp += s[i];
			while ( i+1 < n && (isdigit(s[i+1]) || isalpha(s[i+1])) ) 
				tmp += s[++i];
			if ( id.count(tmp) ) {
				int q = ds.find(id[tmp]);
				if ( isdigit(name[q][0]) )
					res += name[q];
				else
					res += "0";
			} else {
				if ( isdigit(tmp[0]) )
					res += tmp;
				else
					res += "0";
			}
		} else 
			res += s[i];
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	string s;

	int tst = 0;
	while ( getline(cin, s) ) {
		tst++;
		s = lowerAlpha(s);
		if ( s[0] == 'p' ) {
			s = replaceDefine(s.substr(6, (int)s.size()-6));
			cout << calcVal(s) << '\n';
		} else {
			int pos = s.find(" ", 7);	
			string ls = s.substr(7, pos-7),
				   rs = s.substr(pos+1, (int)s.size()-pos-1);
			ls = eatSpace(ls); rs = eatSpace(rs);
			recruit(ls);
			recruit(rs);
			assert(id.count(ls));
			int t = id[ls];
			if ( defined[t] ) continue;
			if ( ds.find(id[rs]) == t ) continue;
			defined[t] = true;
			ds.merge(t, id[rs]);
		}
	}
}
