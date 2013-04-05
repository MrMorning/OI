#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;

long long gcd(const long long &a, const long long &b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a%b);
}

void extgcd(long long &x, long long &y, const long long &a, const long long &b, const long long &c)
{
    if (b == 0)
    {
        x = c/a;  y = 0;
    }
    else
    {
        long long x_, y_;
        extgcd(x_, y_, b, a%b, c);
        x = y_;  y = x_ - (a/b)*y_;
    }
}

void fail()
{
    cout << "NO" << endl;
    exit(0);
}

long long a, b, m, n;
int main()
{
	freopen("t.in", "r", stdin);
    cin >> a >> b >> m >> n;
    long long t = gcd(a, b);
    a /= t;  b /= t;
    if (m % t != 0)
        fail();
    m /= t;
    long long x, y, bx, by;
    extgcd(x, y, a, b, m);
    
    bx = x+b;  by = y-a;
    while (abs(bx)+abs(by) < abs(x)+abs(y))
    {
        x = bx;  y = by;
        bx = x+b;  by = y-a;
    }
    
    bx = x-b;  by = y+a;
    while (abs(bx)+abs(by) < abs(x)+abs(y))
    {
        x = bx;  y = by;
        bx = x-b;  by = y+a;
    }

    bx = x;  by = y;
    for (int k=-10; k<=10; k++)
    {
        x = bx+k*b;
        y = by-k*a;
        if (abs(x)+abs(y)<=n && (abs(x)+abs(y))%2 == n%2)
        {
            long long a1=0, a2=0, a3=0, a4=0;
            t = n-abs(x)-abs(y);
            if (x > 0)
                a1 = x;
            else
                a2 = -x;
            if (y > 0)
                a3 = y;
            else
                a4 = -y;
            a1 += t/2;
            a2 += t/2;
            cout << "YES" << endl;
           // cout<<a1<<' '<<a2<<' '<<a3<<' '<<a4<<endl;
            exit(0);
        }
    }
    fail();
    return 0;
}
