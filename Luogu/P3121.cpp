#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int n, m, top;
array<int, 2 > stk[N];
string s, t[N];

namespace ACAM {
    int ch[N][26], tot = 1, ed[N], fail[N];

    inline void add(string s, int id) {
        int n = s.length(), u = 1;
        For (i, 0, n - 1) {
            int c = s[i] - 'a';
            if (!ch[u][c]) ch[u][c] = ++tot;
            u = ch[u][c];
        }
        ed[u] = id;
    }

    inline void build() {
        For (i, 0, 25) ch[0][i] = 1;
        queue<int > q; q.push(1);
        fail[1] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            For (i, 0, 25) (ch[u][i]? q.push(ch[u][i]), fail[ch[u][i]]: ch[u][i]) = ch[fail[u]][i];
        }
    }
}
using namespace ACAM;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> s;
    n = s.length();
    cin >> m;
    For (i, 1, m) cin >> t[i], add(t[i], i);
    build();
    stk[++top] = {1, -1};
    For (i, 0, n - 1) {
        int c = s[i] - 'a', u = stk[top][0];
        stk[++top] = {u = ch[u][c], c};
        if (ed[u]) top -= t[ed[u]].length();
    }
    For (i, 2, top) putchar('a' + stk[i][1]);

    return 0;
}
