#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
const double eps = 1e-10;
struct point
{
    double x, y;
    friend point operator -(point a, point b)
    {
        return (point){a.x - b.x, a.y - b.y};
    }
    friend point operator +(point a, point b)
    {
        return (point){a.x + b.x, a.y + b.y};
    }

    friend double operator *(point a, point b)

    {

        return a.x * b.x + a.y * b.y;

    }

};

 

struct circle

{

    point cen, spd;

    double rad, mas;

    void read()

    {

        cin >> cen.x >> cen.y >> spd.x >> spd.y >> rad >> mas;

    }

    void print()

    {

        cout << cen.x << " " << cen.y << " " << spd.x << " " << spd.y << endl;

    }

}c1, c2;

 

inline bool same(double a, double b)

{

    return fabs(a - b) < eps;

}

 

template <typename T> inline T sqr(T x)

{

    return x * x;

}

 

inline double dist(point a, point b)

{

    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));

}

 

double target;

 

void init()

{

    c1.read();

    c2.read();

    cin >> target;

}

 

double get_crash_time(circle c0, circle c1)

{

    //(X0 + delta * Vx0 - X1 - delta * Vx1) ^ 2

    //((Vx0 - Vx1) * delta + (X0 - X1)) ^ 2

    //Dim (Vx0 - Vx1) as A1, (X0 - X1) as B1

    double a1 = c0.spd.x - c1.spd.x, b1 = c0.cen.x - c1.cen.x;

    double a2 = c0.spd.y - c1.spd.y, b2 = c0.cen.y - c1.cen.y;

    double a = sqr(a1) + sqr(a2), b = 2 * (a1 * b1 + a2 * b2), c = sqr(b1) + sqr(b2) - sqr(c0.rad + c1.rad);

    if(same(a, 0.0))

        return -c / b;

    double delta = sqr(b) - 4 * a * c;

    if(delta < eps)

        return -1.0;

 

    return (-b - sqrt(delta)) / (2.0 * a);

}

 

void move(circle &c, double t)

{

    c.cen.x += c.spd.x * t;

    c.cen.y += c.spd.y * t;

}

 

void change(point &a, double t)

{

    double l = sqrt(sqr(a.x) + sqr(a.y));

    if(same(l, 0.0))

        return;

    double len = t / l;

    a.x *= len;

    a.y *= len;

}

 

void crash(circle &c0, circle &c1)

{

    //Crash Equation

    //Va = (m1 - m2) / (m1 + m2) * v1 + (2 * m2) / (m1 + m2) * v2

    //Vb = (m2 - m1) / (m1 + m2) * v2 + (2 * m1) / (m1 + m2) * v1

    point vec0[2], vec1[2];

    double len = dist(c0.cen, c1.cen), shadow;

    double v1, v2, va, vb;

 

    vec0[0] = c1.cen - c0.cen;

    vec0[1] = (point){-vec0[0].y, vec0[0].x};

 

    shadow = c0.spd * vec0[0] / len;

    v1 = shadow;

    change(vec0[0], shadow);

 

    shadow = c0.spd * vec0[1] / len;

    change(vec0[1], shadow);

 

    vec1[0] = c1.cen - c0.cen;

    vec1[1] = (point){-vec1[0].y, vec1[0].x};

 

    shadow = c1.spd * vec1[0] / len;

    v2 = shadow;

    change(vec1[0], shadow);

 

    shadow = c1.spd * vec1[1] / len;

    change(vec1[1], shadow);

 

    va = (c0.mas - c1.mas) / (c0.mas + c1.mas) * v1 + (2 * c1.mas) / (c0.mas + c1.mas) * v2;

    vb = (c1.mas - c0.mas) / (c0.mas + c1.mas) * v2 + (2 * c0.mas) / (c0.mas + c1.mas) * v1;

 

    vec0[0] = c1.cen - c0.cen;

    vec1[0] = c1.cen - c0.cen;

    change(vec0[0], va);

    change(vec1[0], vb);

    c0.spd = vec0[0] + vec0[1];

    c1.spd = vec1[0] + vec1[1];

}

 

void solve()

{

    double crash_time = get_crash_time(c1, c2);

    if(crash_time > eps && crash_time < target - eps)

    {

        target -= crash_time;

        move(c1, crash_time);

        move(c2, crash_time);

        crash(c1, c2);

    }

    move(c1, target);

    move(c2, target);

    cout << setiosflags(ios :: fixed) << setprecision(3);

    c1.print();

    c2.print();

}

 

int main()

{

    init();

    solve();

    return 0;

}
