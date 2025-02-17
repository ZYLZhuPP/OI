#include<bits/stdc++.h>
using namespace std;

#define double long double
typedef long long ll;

const int N = 2e5 + 5;
const ll Mo = 998244353;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

vector<int > es[N];
int n, u, v;
ll mo[N][2], val[N];
double f[N][2], lgv[N];

void dfs(int u, int pre) {
    f[u][0] = 0; f[u][1] = lgv[u];
    mo[u][0] = 1; mo[u][1] = val[u];
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
        f[u][1] += f[v][0]; mo[u][1] = (mo[u][1] * mo[v][0]) % Mo;
        f[u][0] += max(f[v][0], f[v][1]); mo[u][0] = (mo[u][0] * mo[v][f[v][0] < f[v][1]]) % Mo;
    }
}

int main() {
    io >> n;
    for (int i = 1; i <= n; ++i) {
        io >> val[i];
        lgv[i] = log(val[i]);
    }
    for (int i = 1; i < n; ++i) {
        io >> u >> v;
        es[u].push_back(v);
        es[v].push_back(u);
    }
    
    dfs(1, 0);
    
    printf("%lld", mo[1][f[1][0] < f[1][1]]);
    
    return 0;
}

