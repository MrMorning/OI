#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

class HP
{
	public:
		static const int MAXL = 1000;
		int len, s[MAXL];
		HP() { (*this) = 0; };
		HP(int inte) { (*this) = inte; };
		HP(const char* str) { (*this) = str; };
		HP(string str) { (*this) = str; };
		friend ostream& operator << (ostream &cout, const HP &x);
		HP operator = (int inte);
		HP operator = (const char* str); HP operator = (string str);
		HP operator + (const HP &b); HP operator += (const HP &b);
		HP operator - (const HP &b); HP operator -= (const HP &b);
		HP operator * (const HP &b); HP operator *= (const HP &b);
		HP operator / (const HP &b); HP operator /= (const HP &b);
		HP operator % (const HP &b); HP operator %= (const HP &b);
		int comp(const HP &b);
		bool operator > (const HP &b); bool operator < (const HP &b);
		bool operator >= (const HP &b); bool operator <= (const HP &b);
		bool operator == (const HP &b); bool operator != (const HP &b);
};
ostream& operator << (ostream &cout, const HP &x)
{
	for (int i = x.len - 1; i >= 0; --i) cout << x.s[i];
	return cout;
}
HP HP::operator = (int inte)
{
	if (inte == 0)
	{
		len = 1;
		s[0] = 0;
	}
	else
	{
		len = 0;
		while (inte)
		{
			s[len++] = inte % 10;
			inte /= 10;
		}
	}
	return (*this);
}
HP HP::operator = (const char* str)
{
	len = strlen(str);
	for (int i = 0; i != len; ++i) s[i] = int(str[len - 1 - i] - '0');
	return (*this);
}
HP HP::operator = (string str)
{
	len = str.size();
	for (int i = 0; i != len; ++i) s[i] = int(str[len - 1 - i] - '0');
	return (*this);
}
HP HP::operator + (const HP &b)
{
	HP c;
	c.s[0] = 0;
	for (int i = 0; i < len || i < b.len; ++i)
	{
		if (i < len) c.s[i] += s[i];
		if (i < b.len) c.s[i] += b.s[i];
		c.s[i + 1] = c.s[i] / 10;
		c.s[i] %= 10;
	}
	c.len = max(len, b.len) + 1;
	while (c.len > 1 && !c.s[c.len - 1]) --c.len;
	return c;
}
HP HP::operator - (const HP &b)
{
	HP c = (*this);
	for (int i = 0; i != b.len; ++i)
	{
		c.s[i] -= b.s[i];
		if (c.s[i] < 0)
		{
			c.s[i] += 10;
			--c.s[i + 1];
		}
	}
	while (c.len > 1 && !c.s[c.len - 1]) --c.len;
	return c;
}
HP HP::operator * (const HP &b)
{
	HP c;
	for (int i = 0; i != len + b.len; ++i) c.s[i] = 0;
	for (int i = 0; i != len; ++i)
		for (int j = 0; j != b.len; ++j)
		{
			c.s[i + j] += s[i] * b.s[j];
			c.s[i + j + 1] += c.s[i + j] / 10;
			c.s[i + j] %= 10;
		}
	c.len = len + b.len;
	while (c.len > 1 && !c.s[c.len - 1]) --c.len;
	return c;
}
HP HP::operator / (const HP &b)
{
	HP c, d;
	if (b.len == 1 && b.s[0] == 0) return c;
	for (int i = len - 1; i >= 0; --i)
	{
		if (d.len != 1 || d.s[0] != 0)
		{
			for (int j = d.len; j > 0; --j)
				d.s[j] = d.s[j - 1];
			++d.len;
		}
		d.s[0] = s[i];
		c.s[i] = 0;
		while (d >= b)
		{
			d -= b;
			++c.s[i];
		}
	}
	c.len = len;
	while (c.len > 1 && !c.s[c.len - 1]) --c.len;
	return c;
}
HP HP::operator % (const HP &b)
{
	HP d;
	if (b.len == 1 && b.s[0] == 0) return d;
	for (int i = len - 1; i >= 0; --i)
	{
		if (d.len != 1 || d.s[0] != 0)
		{
			for (int j = d.len; j > 0; --j)
				d.s[j] = d.s[j - 1];
			++d.len;
		}
		d.s[0] = s[i];
		while (d >= b) d -= b;
	}
	return d;
}
int HP::comp(const HP &b)
{
	if (len > b.len) return 1;
	if (len < b.len) return -1;
	int i = len - 1;
	while ((i > 0) && (s[i] == b.s[i])) --i;
	return s[i] - b.s[i];
}
HP HP::operator += (const HP &b)
{
	(*this) = (*this) + b;
	return (*this);
}
HP HP::operator -= (const HP &b)
{
	(*this) = (*this) - b;
	return (*this);
}
HP HP::operator *= (const HP &b)
{
	(*this) = (*this) * b;
	return (*this);
}
HP HP::operator /= (const HP &b)
{
	(*this) = (*this) / b;
	return (*this);
}
HP HP::operator %= (const HP &b)
{
	(*this) = (*this) % b;
	return (*this);
}
bool HP::operator > (const HP &b) { return this->comp(b) > 0; }
bool HP::operator < (const HP &b) { return this->comp(b) < 0; }
bool HP::operator >= (const HP &b) { return this->comp(b) >= 0; }
bool HP::operator <= (const HP &b) { return this->comp(b) <= 0; }
bool HP::operator == (const HP &b) { return this->comp(b) == 0; }
bool HP::operator != (const HP &b) { return this->comp(b) != 0; }

char comp[33][222];
int compSz[33];
bool isComp[33];
HP ans[33];
char pat[111];
int patLen;
int pi[111];
char acc[101000];
void KMP() {
	pi[0] = -1;
	for ( int i = 1; i < patLen; i ++ ) {
		int t = pi[i - 1];
		while ( t >= 0 && pat[t + 1] != pat[i] )
			t = pi[t];
		if ( pat[t + 1]  == pat[i] )
			pi[i] = t + 1;
		else
			pi[i] = -1;
	}
}
int countMatch(const char *s, int n) {
	int res = 0;
	int t = -1;
	for ( int i = 0; i < n; i ++ ) {
		if ( t == patLen - 1 )
			t = pi[t];
		while ( t >= 0 && pat[t + 1] != s[i] )
			t = pi[t];
		if ( pat[t + 1] == s[i] )
			t ++;
		else
			t = -1;
		res += t == patLen - 1;
	}
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	int N;
	scanf("%d", &N);
	scanf("%s", pat);
	patLen = strlen(pat);
	KMP();
	for ( int i = 1; i <= N; i ++ ) {
		int m;
		int accSz = 0;
		scanf("%d", &m);
		for ( int j = 0; j < m; j ++ ) {
			static char ts[5];
			scanf("%s", ts);
			if ( ts[0] == 'a' || ts[0] == 'b' ) 
				acc[accSz++] = ts[0];
			else {
				int t;
				sscanf(ts, "%d", &t);
				memcpy(acc + accSz, comp[t], sizeof(char) * compSz[t]);
				accSz += compSz[t];
				if ( isComp[t] )
					ans[i] += ans[t];
			}
		}

		ans[i] += countMatch(acc, accSz);
		if ( accSz <= 2*(patLen-1) ) {
			compSz[i] = accSz;
			memcpy(comp[i], acc, sizeof(char) * accSz);
		} else {
			memcpy(comp[i], acc, sizeof(char) * (patLen - 1));
			comp[i][patLen - 1] = '$';
			memcpy(comp[i] + patLen, acc + accSz - patLen + 1, sizeof(char) * (patLen - 1));
			compSz[i] = 2 * (patLen - 1) + 1;
			isComp[i] = true;
		}
	}
	cout << ans[N];
}
