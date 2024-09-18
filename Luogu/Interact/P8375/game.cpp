#include "game.h"
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef pair<int, int > P;
const int N = 3e5 + 5;

int n, k, l[N], r[N];
vector<P > es[N];

void init(int _n, int _k) {
    n = _n; k = _k;
    For (i, 0, k - 1) l[i] = r[i] = i;
    fill(l + k, l + n, -1);
    fill(r + k, r + n, n);
}

bool add(int, int);
bool add(int x) {
    for (auto &e : es[x]) if (add(e.first, e.second)) return 1;
    return 0;
}

bool add(int x, int y) {
    if (x < k && y < k) return y <= x;
    if (l[x] == l[y] && r[x] == r[y]) return 0;
    if (r[x] < l[y]) return 0;
    if (r[y] < l[x]) return 1;
    int mx = (l[x] + r[x]) >> 1, my = (l[y] + r[y]) >> 1;
    if (l[x] <= l[y] && r[y] <= mx) {
        r[x] = mx;
        return l[x] == r[x] || add(x);
    }
    if (r[y] >= r[x] && l[x] >= my + 1) {
        l[y] = my + 1;
        return l[y] == r[y] || add(y);
    }
    return 0;
}

int add_teleporter(int u, int v) {
    es[u].pb(P(u, v)); es[v].pb(P(u, v));
    return add(u, v);
}
