#include <cstdio>
#define INPUT "t.in"
#define OUTPUT "t.out"
#define STDIO

namespace Solve
{
	int a, b;
	void solve(FILE *fin, FILE *fout);
}

void Solve::solve(FILE *fin, FILE *fout)
{
	fscanf(fin, "%d%d", &a, &b);
	fprintf(fout, "%d\n", a + b);
}

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
		 *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, fout);
#endif
}
