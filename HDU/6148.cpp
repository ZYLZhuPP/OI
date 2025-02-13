#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () { return ~c; }
} io;

int T, f[105][11][2], n;
char s[105];

inline int dfs(int k, int x, bool up, bool lim) {
    if (k > n) return x != 10;
    if (!lim && ~f[k][x][up]) return f[k][x][up];
    int res = 0, L = up? x: x==10, R = lim? s[k]^48: 9;
    if (x == 10) res = dfs(k + 1, 10, 0, 0);
    For (i, L, R) add(res, dfs(k + 1, i, up || i>x, lim && i==R));
    return f[k][x][up] = res;
}

int main() {
    io >> T;
    while (T--) {
        memset(f, -1, sizeof f);
        scanf("%s", s + 1);
        n = strlen(s + 1);
        printf("%d\n", dfs(1, 10, 0, 1));
    }

    return 0;
}
