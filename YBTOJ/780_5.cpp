#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); i--)
typedef long long ll;
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
    inline IO& operator >> (char *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, Mo, S, a[N], s[N], cnt[N], o[N], O, _10[N];
ll ans, Ans[N];
char st[N];
unordered_map<int, int > mp;

struct OP {
    int x, y, t;
    bool operator < (const OP &a) const { return x/S^a.x/S? x/S<a.x/S: y<a.y; }
};
vector<OP > ops;

void init() {
    S = sqrt(n);
    _10[0] = 1; For (i, 1, n) _10[i] = (_10[i - 1] * 10ll) % Mo;
    rFor (i, n + 1, 1) s[i] = (s[i + 1] + 1ll * a[i] * _10[n - i]) % Mo, o[i] = !mp[s[i]]? mp[s[i]] = ++O: mp[s[i]];
    sort(ops.begin(), ops.end());
}

int main() {
    io >> Mo;
    io >> (st + 1);
    n = strlen(st + 1);
    For (i, 1, n) a[i] = st[i] ^ 48;
    io >> m;
    int l, r;
    For (i, 1, m) io >> l >> r, ops.pb({l, r, i});
    if (Mo == 2 || Mo == 5) {
        For (i, 1, n) {
            s[i] = s[i - 1]; cnt[i] = cnt[i - 1];
            if (a[i] % Mo == 0) cnt[i]++, s[i] += i;
        }
        For (i, 1, m) {
            l = ops[i - 1].x, r = ops[i - 1].y;
            printf("%lld\n", s[r] - s[l - 1] - 1ll * (l - 1) * (cnt[r] - cnt[l - 1]));
        }
        return 0;
    }
    init();
    l = 1, r = 0;
    for (auto &[x, y, id]: ops) {
        while (l > x) ans += cnt[o[--l]]++;
        while (r < y + 1) ans += cnt[o[++r]]++;
        while (l < x) ans -= --cnt[o[l++]];
        while (r > y + 1) ans -= --cnt[o[r--]];
        Ans[id] = ans;
    }
    For (i, 1, m) printf("%lld\n", Ans[i]);

    return 0;
}
