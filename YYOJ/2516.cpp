#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int T, la, lb, _10[N], g[N], cnt[10], a[N], b[N];
char A[N], B[N];

inline void init() {
    _10[0] = 1; For (i, 1, N - 1) _10[i] = ml(_10[i - 1], 10);
    For (i, 2, N - 1) g[i] = ml(1ll * i * (i - 1) / 2 * 45 % Mo, _10[i - 2]);
}

inline int dfs(int a[], int k, int s, int x) {
    if (!k) return x;
    int res = 0, c = a[k];
    For (i, c + 1, 9) x += cnt[i];
    cnt[c]++; add(res, dfs(a, k - 1, s + c, mo(x))); cnt[c]--;
    rFor (i, c - 1, 0) {
        x += cnt[i + 1], add(res, ml(x, _10[k - 1]));
        if (k > 1) add(res, ml(ml(s + i, k - 1), _10[k - 2]));
        add(res, g[k - 1]);
    }
    return res;
}

int main() {
    init();
    io >> T;
    while (T--) {
        scanf("%s", A + 1); scanf("%s", B + 1);
        int la = strlen(A + 1), lb = strlen(B + 1);
        For (i, 1, la) a[i] = A[la - i + 1] ^ 48;
        For (i, 1, lb) b[i] = B[lb - i + 1] ^ 48;
        For (i, 1, la) if (a[i]) { a[i]--; break; } else a[i] = 9;
        if (!a[la]) la--;
        printf("%d\n", mo(dfs(b, lb, 0, 0) - dfs(a, la, 0, 0)));
    }

    return 0;
}
