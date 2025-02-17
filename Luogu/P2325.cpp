#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int n, S, B, be[N], cap[N];
int stk[N], top;
vector<int > T[N];

void dfs(int u, int pre) {
    int t = top;
    for (auto &v : T[u]) if (v ^ pre) {
        dfs(v, u);
        if (top - t >= S) {
            cap[++B] = u;
            while (top > t) be[stk[top--]] = B;
        }
    }
    stk[++top] = u;
}

int main() {
    io >> n >> S;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, T[u].pb(v), T[v].pb(u);
    dfs(1, 0);
    if (!B) cap[++B] = 1;
    while (top) be[stk[top--]] = B;

    printf("%d\n", B);
    For (i, 1, n) printf("%d%c", be[i], " \n"[i == n]);
    For (i, 1, B) printf("%d ", cap[i]);

    return 0;
}
