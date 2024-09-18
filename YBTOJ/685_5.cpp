#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, Mo = 1e9 + 7, iv2 = 5e8 + 4;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }

int n, p[N << 1], ans;
int L[N << 1], R[N << 1], dl[N << 1], dr[N << 1];
char s[N];

void init() {
    ans = 0;
    memset(L, 0, sizeof L);
    memset(R, 0, sizeof R);
    memset(dl, 0, sizeof dl);
    memset(dr, 0, sizeof dr);
}

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
        init();
        manacher(s);
        n = strlen(s);
        For (i, 2, 2 * n) if (p[i] - 1) {
            int r = p[i], x = i - r + 1, y = i + r - 1;
            add(L[x], i); add(L[i + 1], -i);
            add(dl[x], -1); add(dl[i + 1], 1);
            add(R[i], i); add(R[y + 1], -i);
            add(dr[i], -1); add(dr[y + 1], 1);
        }
        For (i, 2, 2 * n)
            add(L[i], L[i - 1]), add(R[i], R[i - 1]),
            add(dl[i], dl[i - 1]), add(dr[i], dr[i - 1]);
        For (i, 1, n) {
            L[i] = mo(L[i * 2] + ml(dl[i * 2], i));
            R[i] = mo(R[i * 2] + ml(dr[i * 2], i));
        }
        For (i, 1, n - 1) add(ans, ml(R[i], L[i + 1]));
        printf("%d\n", ans);
    }

    return 0;
}
