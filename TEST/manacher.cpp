#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int n, p[N << 1];
char s[N];

void manacher(char *st) {
    int n = strlen(st);
    string s = "@";
    For (i, 0, n - 1) s += '#', s += st[i];
    s += "#$";

    int r = 0, m = 0;
    For (i, 2, 2 * n) {
        p[i] = max(1, min(p[2 * m - i], r - i));
        while (s[i + p[i]] == s[i - p[i]]) p[i]++;
        if (i + p[i] > r) r = i + p[i], m = i;
    }
}

int main() {
    while (~scanf("%s", s)) {
        manacher(s);
        n = strlen(s);
    }

    return 0;
}
