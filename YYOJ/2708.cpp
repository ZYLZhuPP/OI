#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll inf = 1e18;
const int N = 2e5 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

struct Node { int c, l, r; ll sz; } o[N + 26];

int n, tot, rt[26];
ll l, r;
char ch[N];
string s[N];

inline void solve(int p, ll l, ll r) {
    if (~o[p].c) putchar(o[p].c + 'a');
    if (!o[p].l) return;
    ll x = o[o[p].l].sz;
    if (x >= l) solve(o[p].l, l, r);
    if (x < r) solve(o[p].r, l - x, r - x);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> l >> r >> n;
    For (i, 1, n) cin >> ch[i] >> s[i];
    For (i, 0, 25) o[rt[i] = ++tot] = {i, 0, 0, 1};
    rFor (i, n, 1) {
        int c = ch[i] - 'a', p = 0;
        for (auto ch : s[i]) {
            int x = ch - 'a';
            if (!p) p = rt[x];
            else o[++tot] = {-1, p, rt[x], min(o[p].sz + o[rt[x]].sz, inf)}, p = tot;
        }
        rt[c] = p;
    }
    solve(rt[0], l, r);

    return 0;
}
