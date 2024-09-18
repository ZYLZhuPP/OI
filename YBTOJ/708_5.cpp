#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, M = 1e3 + 5;

int n, m, x, y, A, a[M], b[M], B, c[M], d[M], ans;
int sx1, sy1, sx2, sy2, len, dis[N];

vector<int > es[N], pt[N];
stack<int > st;
int dfn[N], low[N], tim, co[N], con;
void Tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st.push(u);
    for (auto &v : es[u])
        if (!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
        else if (!co[v]) low[u] = min(low[u], dfn[v]);
    if (low[u] == dfn[u]) {
        pt[co[u] = ++con].push_back(u);
        int v;
        while ((v = st.top()) ^ u) pt[co[v] = con].push_back(v), st.pop();
        st.pop();
    }
}

void init(int n) {
    For (i, 0, n) es[i].resize(0);
    For (i, 1, con) pt[i].resize(0);
    tim = con = 0;
    memset(dfn, 0, sizeof dfn);
    memset(co, 0, sizeof co);
}

bool ok(int x) {
    init(n << 1 | 1);
    For (i, 1, A) {
        es[a[i] << 1].pb(b[i] << 1 | 1); es[b[i] << 1 | 1].pb(a[i] << 1);
        es[b[i] << 1].pb(a[i] << 1 | 1); es[a[i] << 1 | 1].pb(b[i] << 1);
    }
    For (i, 1, B) {
        es[c[i] << 1].pb(d[i] << 1); es[d[i] << 1].pb(c[i] << 1);
        es[c[i] << 1 | 1].pb(d[i] << 1 | 1); es[d[i] << 1 | 1].pb(c[i] << 1 | 1);
    }
    For (i, 1, n) For (j, i + 1, n) {
        if (dis[i << 1] + dis[j << 1] > x)
            es[i << 1].pb(j << 1 | 1), es[j << 1].pb(i << 1 | 1);
        if (dis[i << 1 | 1] + dis[j << 1 | 1] > x)
            es[i << 1 | 1].pb(j << 1), es[j << 1 | 1].pb(i << 1);
        if (dis[i << 1] + dis[j << 1 | 1] + len > x)
            es[i << 1].pb(j << 1), es[j << 1 | 1].pb(i << 1 | 1);
        if (dis[i << 1 | 1] + dis[j << 1] + len > x)
            es[i << 1 | 1].pb(j << 1 | 1), es[j << 1].pb(i << 1);
    }
    For (i, 2, n << 1 | 1) if (!dfn[i]) Tarjan(i);
    For (i, 1, n) if (co[i << 1] == co[i << 1 | 1]) return 0;
    return 1;
}

int dist(int x, int y, int xx, int yy) { return abs(x - xx) + abs(y - yy); }

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n >> A >> B) {
        ans = -1;
        cin >> sx1 >> sy1 >> sx2 >> sy2;
        len = dist(sx1, sy1, sx2, sy2);
        For (i, 1, n) {
            cin >> x >> y;
            dis[i << 1] = dist(x, y, sx1, sy1);
            dis[i << 1 | 1] = dist(x, y, sx2, sy2);
        }
        For (i, 1, A) cin >> a[i] >> b[i];
        For (i, 1, B) cin >> c[i] >> d[i];
        int l = 0, r = 8e6;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (ok(m)) ans = m, r = m - 1;
            else l = m + 1;
        }
        cout << ans << endl;
    }

    return 0;
}
