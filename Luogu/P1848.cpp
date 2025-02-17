#include<bits/stdc++.h>
#define ll long long
#define int ll
#define debug(x) cout<<#x<<":"<<x,puts("");
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
//
//
//
using namespace std;
inline ll read() {
    ll f = 0, t = 0;
    char c = getchar();
    while (!isdigit(c)) t |= (c == '-'), c = getchar();
    while (isdigit(c)) f = (f << 3) + (f << 1) + c - 48, c = getchar();
    return t ? -f : f;
}
const int MX = 1e6 + 10;
struct {
    int w, h;
} a[MX];
int f[MX];
const int inf = 1e18;
struct {
    int sum, sum2, Sum;
} tree[MX * 4];
int lzy[MX * 4];
#define lw(x) (x<<1)
#define rw(x) (x<<1|1)
#define mid ((l+r)/2)
void push_down(int x) {
    lzy[lw(x)] = lzy[rw(x)] = lzy[x];
    tree[x].sum = lzy[x];
    tree[x].Sum = tree[x].sum2 + tree[x].sum;
    lzy[x] = 0;
}
void push_up(int x) {
    if (tree[lw(x)].Sum < tree[rw(x)].Sum) tree[x].Sum = tree[lw(x)].Sum;
    else tree[x].Sum = tree[rw(x)].Sum;
    if (tree[lw(x)].sum2 < tree[rw(x)].sum2) tree[x].sum2 = tree[lw(x)].sum2;
    else tree[x].sum2 = tree[rw(x)].sum2;
}
void change(int x, int l, int r, int ln, int rn, int w) {
    if (lzy[x]) push_down(x);
    if (ln <= l && r <= rn) {
        tree[x].sum = lzy[x] = w;
        tree[x].Sum = tree[x].sum2 + tree[x].sum;
        return;
    }
    if (lzy[x]) push_down(x);
    if (ln <= mid) change(lw(x), l, mid, ln, rn, w);
    if (mid < rn) change(rw(x), mid + 1, r, ln, rn, w);
    push_up(x);
}
void change_p(int x, int l, int r, int id, int w) {
    if (lzy[x]) push_down(x);
    if (l == r) {
        tree[x].sum2 = w;
        tree[x].Sum = tree[x].sum2 + tree[x].sum;
        return;
    }
    if (lzy[x]) push_down(x);
    if (id <= mid) change_p(lw(x), l, mid, id, w);
    else change_p(rw(x), mid + 1, r, id, w);
    push_up(x);
}
int find(int x, int l, int r, int ln, int rn) {
    if (lzy[x]) push_down(x);
    if (ln <= l && r <= rn) {
        return tree[x].Sum;
    }
    if (lzy[x]) push_down(x);
    int A = inf;
    if (ln <= mid) A = min(A, find(lw(x), l, mid, ln, rn));
    if (mid < rn) A = min(A, find(rw(x), mid + 1, r, ln, rn));
    push_up(x);
    return A;
}
int lst[MX];
signed main() {
    ios::sync_with_stdio(0), cout.tie(0);
    int n = read(), L = read();
    FOR(i, 2, n + 1) a[i].h = read(), a[i].w = read();
    FOR(i, 2, n + 1) f[i] = inf;
    FOR(i, 2, n + 1) lst[i] = -1;
    lst[1] = 1;
    a[1].h = inf;
    FOR(i, 2, n + 1) for (lst[i] = i - 1; a[lst[i]].h < a[i].h; lst[i] = lst[lst[i]]);
    int l = 2, sum = 0;
    f[1] = 0;
    FOR(i, 2, n + 1) {
        sum += a[i].w;
        while (sum > L) sum -= a[l].w, l++;
        change(1, 1, n, lst[i], i, a[i].h);
        f[i] = find(1, 1, n, l - 1, i - 1);
        change_p(1, 1, n, i, f[i]);
    }
    cout << f[n + 1];
    return 0;
}
