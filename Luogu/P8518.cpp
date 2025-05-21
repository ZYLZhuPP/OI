#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

vector<array<int, 2 > > ops[N];

namespace Seg {
    ll s[N << 2], mx[N << 2], mn[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { s[p] = s[ls] + s[rs]; mx[p] = max(mx[ls], s[ls] + mx[rs]); mn[p] = min(mn[ls], s[ls] + mn[rs]); }
    inline void upd(int p, int l, int r, int x, const int &d) {
        if (l == r) {
            s[p] += d;
            mx[p] = max(0ll, s[p]);
            mn[p] = min(0ll, s[p]);
            return;
        }
        M; x<=m? upd(goL, x, d): upd(goR, x, d); up(p);
    }
    inline int query(int p, int l, int r, ll S, ll Mx, ll Mn, const ll &C) {
        if (l == r) {
            S += s[p], Mx = max(mx[p], s[p] + Mx), Mn = min(mn[p], s[p] + Mn);
            if (S < 0 || Mx - Mn < C) return S - Mn;
            else return C - (Mx - S);
        }
        ll S_ = S + s[rs], Mx_ = max(mx[rs], s[rs] + Mx), Mn_ = min(mn[rs], s[rs] + Mn);
        M; return Mx_-Mn_>=C? query(goR, S, Mx, Mn, C): query(goL, S_, Mx_, Mn_, C);
    }
}
using namespace Seg;

vector<int > distribute_candies(vector<int > c, vector<int > l, vector<int > r, vector<int > v) {
    vector<int > ans;
    int n = c.size(), q = v.size();
    For (i, 0, q - 1) ops[l[i]].pb({i + 1, v[i]}), ops[r[i] + 1].pb({i + 1, -v[i]});
    For (i, 0, n - 1) {
        for (auto &[x, d] : ops[i]) upd(1, 1, q, x, d);
        ans.pb(query(1, 1, q, 0, 0, 0, c[i]));
    }
    return ans;
}