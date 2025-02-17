#include<bits/stdc++.h>
using namespace std;

#define mem(a, x) memset(a, x, sizeof(a))

typedef long long ll;

const int N = 5e4 + 5, A = 5005;
const ll Mo = 998244353;

struct IO {
    char c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

ll n, u, v, a[N], f[A], g[A], ans;
bool vis[N];
vector<int > es[N];
vector<int > pt[A]; 

void dfs(int u, int pre, ll ma) {
    g[ma]++;
    for (auto &v : es[u]) if (v ^ pre && !vis[v]) {
        dfs(v, u, max(ma, a[v]));
    }
}

int main() {
    io >> n;
    for (int i = 1; i <= n; i++) io >> a[i], pt[a[i]].push_back(i);
    for (int i = 1; i < n; i++) {
        io >> u >> v;
        es[u].push_back(v);
        es[v].push_back(u);
    }
    
    for (auto &p : pt) {
        for (auto &u : p) {
            ans = (ans + a[u] * a[u]) % Mo;
            mem(f, 0);
            for (auto &v : es[u]) if (!vis[v]) {
                mem(g, 0);
                dfs(v, u, a[v]);
                for (int i = a[u]; i < A; i++) ans = (ans + g[i] * i * a[u]) % Mo;
                ll sf = 0, sg = 0;
                for (int i = a[u]; i < A; i++) {
                    sf += f[i - 1]; sg += g[i - 1];
                    ans = (ans + (sf * g[i] + sg * f[i] + f[i] * g[i]) * a[u] * i) % Mo;
                }
                for (int i = a[u]; i < A; i++) f[i] += g[i];
            } 
            vis[u] = 1;
        }
    } 
    
    printf("%lld", ans);
    
    return 0;
} 
