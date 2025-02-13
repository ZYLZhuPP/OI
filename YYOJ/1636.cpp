#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2e4 + 5, Mo = 998244353, M = 505;
inline int mo(int &x) {return x -= (x >= Mo? Mo: 0);}
inline int gmo(int x) {return mo(x);}
template<class C> inline void clear(C &a) {C().swap(a);}

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, q, v[N], w[N];

struct Ask {
    int l, r, m, id;
    void get() {
        io >> l >> r >> m;
    }
};

struct Ans {
    int ans, cnt;
    Ans operator + (const Ans &x) const {
        if (x.ans ^ ans) return x.ans < ans? *this: x;
        return (Ans){ans, gmo(x.cnt + cnt)};
    }
    Ans operator + (const int &w) const {
        return (Ans){ans + w, cnt};
    }
    Ans operator * (const Ans &x) const {
        return (Ans){ans + x.ans, int(1ll * cnt * x.cnt % Mo)};
    }
};
vector<Ans > ans;
Ans f1[N][M], f2[N][M];

void trans(Ans a[], Ans b[], int v, int w) {
    rFor (i, M - 1, 0) {
        b[i] = a[i];
        if (i >= v) b[i] = b[i] + (a[i - v] + w);
    }
}

void solve(vector<Ask > &a, int l, int r) {
    if (a.empty()) return;
    if (l == r) {
        for (auto x : a) ans[x.id] = x.m >= v[l]? (Ans){w[l], 1}: (Ans){0, 0};
        return;
    }

    int m = (l + r) >> 1;
    vector<Ask > a1, a2;
    For (i, 0, M - 1) f1[m + 1][i] = (Ans){0, 0}, f2[m][i] = (Ans){0, 1};
    f1[m + 1][0] = (Ans){0, 1};
    rFor (i, m, l) trans(f1[i + 1], f1[i], v[i], w[i]);
    For (i, m + 1, r) trans(f2[i - 1], f2[i], v[i], w[i]);
    for (auto &x : a) {
        if (x.l <= m && x.r > m) {
            ans[x.id] = (Ans){0, 0};
            For (j, 0, x.m) ans[x.id] = ans[x.id] + f1[x.l][j] * f2[x.r][x.m - j];
        } else if (x.r <= m) {
            a1.push_back(x);
        } else a2.push_back(x);
    }
    clear(a);
    solve(a1, l, m);
    solve(a2, m + 1, r);
}

int main() {
    io >> n;
    For (i, 1, n) io >> w[i] >> v[i];
    io >> q; ans.resize(q);
    vector<Ask > a(q);
    For (i, 0, q - 1) a[i].get(), a[i].id = i;

    solve(a, 1, n);

    for (auto &x : ans) {
        if (!x.ans) puts("0 0");
        else printf("%d %d\n", x.ans, x.cnt);
    }

    return 0;
}
