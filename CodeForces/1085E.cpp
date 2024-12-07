#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

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
    inline bool operator ~ () { return ~c; }
} io;

int T, n, K, to[30], vis[30];
char s[N], a[N], b[N];

bool dfs(int x, bool f1, bool f2) {
    if (x == n + 1 || (!f1 && !f2)) return 1;
    int l = f1? a[x]: 1, r = f2? b[x]: K, c = to[s[x]];
    if (c) {
        if (c < l || c > r) return 0;
        return dfs(x + 1, f1 && c==l, f2 && c==r);
    }
    For (i, l, r) if (!vis[i]) {
        to[s[x]] = i; vis[i] = 1;
        if (dfs(x + 1, f1 && i==l, f2 && i==r)) return 1;
        to[s[x]] = 0; vis[i] = 0;
    }
    return 0;
}

int main() {
    io >> T;
    while (T--) {
        io >> K;
        For (i, 1, K) to[i] = vis[i] = 0;
        scanf("%s %s %s", s + 1, a + 1, b + 1);
        n = strlen(s + 1);
        For (i, 1, n) s[i] -= 96, a[i] -= 96, b[i] -= 96;
        if (!dfs(1, 1, 1)) { puts("NO"); continue; }
        puts("YES");
        int x = 1;
        For (i, 1, K) if (!to[i]) { while (vis[x]) x++; to[i] = x; vis[x] = 1; }
        For (i, 1, K) putchar(to[i] + 96);
        puts("");
    }

    return 0;
}