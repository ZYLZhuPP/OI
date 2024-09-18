#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 505;

int n, m, u, v, Case;
ll ans, f;

vector<int > es[N], pt[N];
stack<int > st;
int dfn[N], low[N], tim, cut[N], con;
void Tarjan(int u, int pre) {
    dfn[u] = low[u] = ++tim;
    st.push(u);
    int cnt = 0;
    for (auto &v : es[u]) if (v ^ pre) {
        if (!dfn[v]) {
            ++cnt;
            Tarjan(v, u), low[u] = min(low[u], low[v]);
            if ((!pre && cnt > 1) || (pre && dfn[u] <= low[v])) cut[u] = 1;
            if (dfn[u] <= low[v]) {
                pt[++con].push_back(u);
                while (st.top() ^ v) pt[con].push_back(st.top()), st.pop();
                pt[con].push_back(v); st.pop();
            }
        } else low[u] = min(low[u], dfn[v]);
    }
}

void init(int n) {
    For (i, 0, n) es[i].resize(0);
    For (i, 1, con) pt[i].resize(0);
    tim = con = 0;
    memset(dfn, 0, sizeof dfn);
    memset(cut, 0, sizeof cut);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> m, m) {
        n = ans = 0; f = 1;
        Case++;
        init(500);
        For (i, 1, m) cin >> u >> v, es[u].push_back(v), es[v].push_back(u), n = max(n, max(u, v));
        For (i, 1, n) if (!dfn[i]) Tarjan(i, 0);
        For (i, 1, con) {
            int cnt = 0, s = pt[i].size();
            for (auto &u : pt[i]) cnt += cut[u];
            if (!cnt) ans += 2, f *= 1ll * s * (s - 1) / 2;
            else if (cnt == 1) ans++, f *= s - 1;
        }
        cout << "Case " << Case << ": " << ans << " " << f << endl;
    }

    return 0;
}
