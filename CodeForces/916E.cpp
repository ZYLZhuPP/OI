#include<bits/stdc++.h>
using namespace std;
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define Rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define O(x) cerr << #x << ":" << x << endl
#define O_(x, y) cerr << #x << ":" << x << " " << #y << ":" << y << endl
#define LO(a, l, r)                                           \
    For(supervariable, l, r) cerr << a[supervariable] << " "; \
    putchar('\n')
#define FS(v, V, u, fa)  \
    for (int v : V[(u)]) \
        if (v != (fa))
#define FENGE cout << "----------------------------------------------------------" << endl;
int read()
{
    int x = 0, t = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            t = -t;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    return x * t;
}
const int N = 100005;
const long long yao = 1;
int a[N], rt = 1;;

namespace SEG
{
    long long tr[N << 3], lazy[N << 3];
    void pushUp(int x) { tr[x] = tr[x << 1] + tr[x << 1 | 1]; }
    void pushDown(int x, int l, int r)
    {
        //assert(x);
        int mid = (l + r) >> 1;
        tr[x << 1] += lazy[x] * (mid - l + 1);
        tr[x << 1 | 1] += lazy[x] * (r - mid);
        lazy[x << 1] += lazy[x];
        lazy[x << 1 | 1] += lazy[x];
        lazy[x] = 0;
    }
    void update(int x, int l, int r, int L, int R, int val)
    {
        //assert(L<=R&&L>=1&&L<=n&&R>=1&&R<=n);
        if (L <= l && R >= r)
        {
            tr[x] += yao * val * (r - l + 1);
            lazy[x] += val;
            return;
        }
        int mid = (l + r) >> 1;
        pushDown(x, l, r);
        if (L <= mid)
            update(x << 1, l, mid, L, R, val);
        if (R > mid)
            update(x << 1 | 1, mid + 1, r, L, R, val);
        pushUp(x);
    }
    long long query(int x, int l, int r, int L, int R)
    {
        //assert(L<=R&&L>=1&&L<=n&&R>=1&&R<=n);
        if (L <= l && R >= r)
            return tr[x];
        int mid = (l + r) >> 1;
        pushDown(x, l, r);
        long long res = 0;
        if (L <= mid)
            res += query(x << 1, l, mid, L, R);
        if (R > mid)
            res += query(x << 1 | 1, mid + 1, r, L, R);
        return res;
    }
}
using namespace SEG;

namespace Tree {
vector<int> V[N];
    int dep[N], n, fa[N][18];
    int dfn[N], out[N];
    void dfs(int u, int pre) {
        dfn[u] = ++dfn[0]; fa[u][0] = pre; dep[u] = dep[pre] + 1;
        update(1, 1, n, dfn[u], dfn[u], a[u]);
        For (i, 1, 17) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (auto &v : V[u]) if (v ^ pre) dfs(v, u);
        out[u] = dfn[0];
    }
    inline int jump(int u, int x) { Rfor (i, 17, 0) if (x >> i & 1) u = fa[u][i]; return u; }
    inline int getLca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        u = jump(u, dep[u] - dep[v]);
        if (u == v) return u;
        Rfor (i, 17, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];
    }
}
using namespace Tree;

bool inSub(int x, int y) { return dfn[x] <= dfn[y] && out[x] >= out[y]; }
void update(int x, int val) { update(1, 1, n, dfn[x], out[x], val); }
long long query(int x) { return query(1, 1, n, dfn[x], out[x]); }

int main()
{
    n = read();
    int q = read();
    For(i, 1, n) a[i] = read();
    For(i, 1, n - 1)
    {
        int x = read(), y = read();
        V[x].emplace_back(y);
        V[y].emplace_back(x);
    }
    dfs(1, 0);
    For(i, 1, q)
    {
        int op = read();
        if (op == 1)
        {
            rt = read();
            continue;
        }
        if (op == 2)
        {
            int u = read(), v = read(), x = read();
            int Luv = getLca(u, v), Lur = getLca(u, rt), Lvr = getLca(v, rt);
            u = Luv ^ Lur ^ Lvr;
            if (u == rt) {
                update(1, x);
                continue;
            }
            if (!inSub(u, rt))
            {
                update(u, x);
                continue;
            }
            update(1, x), update(jump(rt, dep[rt] - dep[u] - 1), -x);
        }
        if (op == 3)
        {
            int u = read();
            if (u == rt) {
                printf("%lld\n", query(1));
                continue;
            }
            if (!inSub(u, rt))
            {
                printf("%lld\n", query(u));
                continue;
            }
            printf("%lld\n", query(1) - query(jump(rt, dep[rt] - dep[u] - 1)));
        }
    }
}