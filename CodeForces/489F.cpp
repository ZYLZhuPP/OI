#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505;
int Mo;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, m, cnt[N], f[N][N];
char s[N];

int main() {
    io >> n >> m >> Mo;
    For (i, 1, m) {
        scanf("%s", s + 1);
        For (j, 1, n) if (s[j] == '1') cnt[j]++;
    }
    int x = 0;
    For (i, 1, n) x += !cnt[i];
    f[m][x] = 1;
    For (o, m, n - 1) {
        For (i, 0, n - o) if (f[o][i]) {
            int j = 2 * (n - o - i);
            if (j) add(f[o + 1][i], ml(f[o][i], 1ll * j * (j - 1) / 2 % Mo));
            if (i) add(f[o + 1][i - 1], ml(f[o][i], ml(i, j)));
            if (i > 1) add(f[o + 1][i - 2], ml(f[o][i], 1ll * i * (i - 1) / 2 % Mo));
        }
    }
    printf("%d", f[n][0]);

    return 0;
}
