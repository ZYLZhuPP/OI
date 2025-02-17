#include<bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;

struct IO {
    static const int BufS = 1 << 20;
    char ibuf[BufS], *S, *T, c; int f;
#define gc() ((S==T && (T=(S=ibuf)+fread(ibuf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, to[N][2], ans, d1[N], d2[N];
bool vis[N];

void dfs(int u, int x) {
    if (vis[u]) {
        if (x <= n) {
            puts("-1");
            exit(0);
        }
        return;
    }
    vis[u] = 1;
    d1[(u + n - x) % n]++;
    d2[(2 * n - x + 1 - u) % n]++;
    dfs(to[u][vis[to[u][0]]], x + 1);
}

int main() {
    io >> n;
    for (int i = 1; i <= n; ++i) {
        io >> to[i][0] >> to[i][1];
    }

    dfs(1, 1);

    ans = n;
    for (int i = 0; i < n; ++i) ans = min(ans, n - max(d1[i], d2[i]));

    printf("%d", ans);

    return 0;
}
