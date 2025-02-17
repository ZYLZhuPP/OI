#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 305, M = N * N << 1, C = 26, INF = INT_MAX;

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    template<class C>
    inline IO& operator >> (C *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, len[N], S, T, cnt, ans = -1;
char st[N][N], me[M];
int num, nxt[M << 1], head[M], val[M << 1], go[M << 1];
int sum, to[M][C], lst[C], rt[N];
int tot, ch[M][C], fa[M];

void add(int u, int v, int d) {
    nxt[++num] = head[u];
    head[u] = num; val[num] = d;
    go[num] = v;
    nxt[++num] = head[v];
    head[v] = num; val[num] = 0;
    go[num] = u;
}

namespace Dinic {
    int lev[M];
    bool bfs() {
        memset(lev, -1, sizeof lev); lev[S] = 0;
        queue<int > q; q.push(S);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; i; i = nxt[i]) if (val[i]) {
                int v = go[i];
                if (lev[v] == -1) {
                    lev[v] = lev[u] + 1;
                    q.push(v);
                    if (v == T) return 1;
                }
            }
        }
        return 0;
    }
    int dfs(int u, int s) {
    //cout << u << endl;
        if (u == T || !s) return s;
        int flow = 0, f;
        for (int i = head[u]; i; i = nxt[i]) if (val[i]) {
            int v = go[i];
            if (lev[u] < lev[v] && (f = dfs(v, min(s - flow, val[i])))) {
                val[i] -= f; val[i ^ 1] += f;
                flow += f; if (flow == s) return flow;
            }
        }
        if (flow < s) lev[u] = -1;
        return flow;
    }
    int solve() {
        int res = 0;
        while (bfs()) res += dfs(S, INF);
        return res;
    }
}

void dfs(int i, int u, int chu, int mid) {
    assert(cnt <= n);
    assert(tot < S);
    if (cnt == n || !mid) return;
    For (k, 0, 25) if (to[u][k] && cnt < n) {
        int v = to[u][k];
        if (!ch[chu][k]) ch[chu][k] = ++tot, fa[tot] = chu, me[tot] = k + 'a';
        int chv = ch[chu][k];
        cnt++, add(i, chv, 1);
        dfs(i, v, chv, mid - 1);
    }
}

bool check(int mid) {
    S = M - 2; T = M - 1;
    tot = n; num = 1;
    memset(head, 0, sizeof head);
    memset(ch, 0, sizeof ch);
    For (i, 1, n) {
        cnt = 0;
        dfs(i, rt[i], n, mid);
    }
    For (i, 1, n) add(S, i, 1);
    For (i, n + 1, tot) add(i, T, 1); //puts("!");
    //cout << tot << endl;
    return Dinic::solve() == n;
}

void pre() {
    For (i, 1, n) {
        rt[i] = ++sum;
        memset(lst, 0, sizeof lst);
        rFor (j, len[i], 1) {
            sum++;
            For (k, 0, 25) if (lst[k]) to[sum][k] = lst[k];
            lst[st[i][j] - 'a'] = sum;
        }
        For (k, 0, 25) if (lst[k]) to[rt[i]][k] = lst[k];
    }
}

void put(int u) {
    if (u == n) return;
    put(fa[u]);
    putchar(me[u]);
}

int main() {
    io >> n;
    For (i, 1, n) io >> (st[i] + 1), len[i] = strlen(st[i] + 1);
    pre(); //puts("!");

    int l = 1, r = 300;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    //put(n + 1);
    if (ans == -1) { puts("-1"); return 0; }

    printf("%d\n", ans);
    check(ans);
    For (u, 1, n) {
        for (int i = head[u]; i; i = nxt[i]) if (!(i & 1) && !val[i])
            put(go[i]), puts("");
    }
 
    return 0;
}
