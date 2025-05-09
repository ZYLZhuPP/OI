#include"nile.h"
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

int n, m;
array<int, 3 > pt[N];
array<int, 2 > qs[N], d1[N], d2[N];
ll ans[N];

namespace Seg {
    struct mat {
        ll o[3][3];
        mat() { memset(o, -0x3f, sizeof o); }
        mat operator * (const mat &a) const {
            mat r;
            For (k, 0, 2)  For (i, 0, 2) For (j, 0, 2) cmax(r.o[i][j], o[i][k] + a.o[k][j]);
            return r;
        }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = o[ls] * o[rs]; }
    inline void build(int p, int l, int r) {
        if (l == r) {
            o[p] = mat();
            o[p].o[1][0] = o[p].o[2][1] = o[p].o[2][2] = o[p].o[1][2] = o[p].o[0][2] = 0;
            return;
        }
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int p, int l, int r, int x, int k) {
        if (l == r) return o[p].o[2 - k][2] = pt[x][1] + pt[x - k][1], void();
        M; x<=m? upd(goL, x, k): upd(goR, x, k); up(p);
    }
}
using namespace Seg;

vector<ll > calculate_costs(vector<int > W, vector<int > A, vector<int > B, vector<int > E) {
    ll sum = 0;
    n = W.size();
    For (i, 0, n - 1) pt[i + 1] = {W[i], A[i], B[i]};
    sort(pt + 1, pt + n + 1);
    m = E.size();
    For (i, 0, m - 1) qs[i + 1] = {E[i], i + 1};
    sort(qs + 1, qs + m + 1);
    For (i, 1, n) sum += pt[i][1], pt[i][1] -= pt[i][2];
    build(1, 1, n);
    For (i, 2, n) d1[i] = {pt[i][0] - pt[i - 1][0], i};
    For (i, 3, n) d2[i] = {pt[i][0] - pt[i - 2][0], i};
    sort(d1 + 2, d1 + n + 1); sort(d2 + 3, d2 + n + 1);
    int k1 = 2, k2 = 3;
    For (i, 1, m) {
        while (k1 <= n && d1[k1][0] <= qs[i][0]) upd(1, 1, n, d1[k1++][1], 1);
        while (k2 <= n && d2[k2][0] <= qs[i][0]) upd(1, 1, n, d2[k2++][1], 2);
        ans[qs[i][1]] = sum - o[1].o[2][2];
    }
    vector<ll > res;
    For (i, 1, m) res.pb(ans[i]);
    return res;
}
