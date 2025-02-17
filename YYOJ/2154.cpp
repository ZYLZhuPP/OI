#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef pair<int, int > P;
const int N = 1e6 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    IO& operator >> (int &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
} io; 

int n, x[N], d, in[N], ans;
vector<int > es[N];
P l[N], r[N];

int dfn[N], low[N], tim, co[N], color, stk[N], top;
void Tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    stk[++top] = u;
    for (auto &v : es[u]) if (!co[v]) {
        if (dfn[v]) low[u] = min(low[u], dfn[v]);
        else Tarjan(v), low[u] = min(low[u], low[v]);
    }
    if (dfn[u] == low[u]) {
        co[u] = ++color;
        while (top && stk[top] ^ u) co[stk[top--]] = color;
        top--;
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> x[i] >> d, l[i] = P(x[i] - d, i), r[i] = P(x[i] + d, i);
    sort(l + 1, l + n + 1);
    priority_queue<int, vector<int >, greater<int > > ql;
    int p = 1;
    For (i, 1, n) {
        while (p <= n && l[p].st <= x[i]) ql.push(l[p].nd), p++;
        while (!ql.empty() && ql.top() <= i) ql.pop();
        if (!ql.empty()) es[ql.top()].pb(i);
    }
    sort(r + 1, r + n + 1);
    priority_queue<int > qr;
    p = n;
    rFor (i, n, 1) {
        while (p >= 1 && r[p].st >= x[i]) qr.push(r[p].nd), p--;
        while (!qr.empty() && qr.top() >= i) qr.pop();
        if (!qr.empty()) es[qr.top()].pb(i);
    }
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    For (u, 1, n) for (auto &v : es[u]) if (co[u] ^ co[v]) in[co[v]]++;
    For (i, 1, color) if (!in[i]) ans++;

    printf("%d\n%d", ans, color);

    return 0;
}
