#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

class HP
{
	public:
		static const int MAXL = 500;
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

HP gcd(HP a, HP b) {
	return b == 0 ? a : gcd(b, a % b);
}

HP f[101], fact[101];
int n, k;
int main() {
	freopen("t.in", "r", stdin);
	f[0] = 1, f[1] = 0, f[2] = 1;
	for ( int i = 3; i <= 100; i ++ )
		f[i] = (f[i-1]+f[i-2])*(i-1);
	fact[0] = 1;
	for ( int i = 1; i <= 100; i ++ )
		fact[i] = fact[i-1]*i;
	scanf("%d%d", &k, &n);
	HP a = f[n-k], b = fact[k]*fact[n-k], g = gcd(a, b);
	if ( a == 0 ) {
		puts("0");
		return 0;
	}
	a /= g, b /= g;
	cout << a << '/' << b;
}
