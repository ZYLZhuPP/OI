#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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
    inline bool operator ~ () const { return ~c; }
} io;

struct Q {
    ll T; int u, v;
    bool operator < (const Q &a) const { return T > a.T; }
};
priority_queue<Q > q;

int T, n, s[N];
ll a[N], ans[N];
set<int > pos;

inline void add(int u, int v) {
    ll T = (a[v] - a[u] - 1) / (s[u] + s[v]) * 2 + 2 - (u & 1);
    q.push({T, u, v});
}

int main() {
    io >> T;
    while (T--) {
        io >> n;
        For (i, 1, n) io >> a[i], ans[i] = 0;
        For (i, 1, n) io >> s[i];
        pos.insert(1);
        For (i, 2, n) add(i - 1, i), pos.insert(i);
        while (!q.empty()) {
            auto [T, u, v] = q.top(); q.pop();
            if (ans[u] || ans[v]) continue;
            ans[u] = ans[v] = T;
            if (u > *pos.begin()) {
                auto a = prev(pos.find(u)), b = next(pos.find(v));
                if (b != pos.end()) add(*a, *b);
            }
            pos.erase(u), pos.erase(v);
        }
        For (i, 1, n) printf("%lld%c", ans[i], " \n"[i==n]);
    }

    return 0;
}
