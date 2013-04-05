#include <cstdio>
#include <cstring>
#include <list>

using namespace std;

char org[1000001];

int main(void) {
	freopen("t.in", "r", stdin);
    list<char> word;
    scanf ("%s", org);
    int i;
    int len = strlen(org);
    list<char>::iterator it = word.begin();
    for (i = 0; i < len; ++i) {
        if (org[i] == 'L') {
            if (it != word.begin()) {
                --it;
            }
        } else if (org[i] == 'R') {
            if (it != word.end()) {
                ++it;
            }
        } else {
            word.insert(it, org[i]);
        }
    }
    for (it = word.begin(); it != word.end(); ++it) {
        printf ("%c", *it);
    }
    printf ("\n");
    return 0;
}
