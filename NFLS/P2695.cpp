#include"september.h"
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int n, m, f[N];
vector<int > es[N];

void dfs(int u) {
    for (auto &v : es[u]) dfs(v), f[u] = max(f[u], f[v]);
}

int solve(int N, int M, vector<int > F, vector<vector<int > > S) {
    n = N; m = M;
    For (i, 0, n - 1) es[i].resize(0), f[i] = 0;
    For (i, 1, n - 1) es[F[i]].pb(i);
    For (i, 0, M - 1) For (j, 0, n - 2) f[S[i][j]] = max(f[S[i][j]], j);
    dfs(0);
    int ans = 0, l = 0, r = 0;
    while (l <= n - 2) {
        ans++;
        while (l <= r) {
            For (i, 0, M - 1) r = max(r, f[S[i][l]]);
            l++;
        }
        r++;
    }
    return ans;
}
