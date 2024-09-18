#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, inf = 1e9;

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

struct P { int l, r, kd, pos; };
bool cmp(const P &a, const P &b) { return a.r^b.r? a.r>b.r: a.l>b.l; }
bool cmpl(const P &a, const P &b) { return a.l < b.l; }
bool cmpr(const P &a, const P &b) { return a.r < b.r; }
struct Cmpr { bool operator () (const P &a, const P &b) const { return a.r < b.r; } };

int n, l, r, c, cnt, ans, ok[N];
map<int, int > kind;
vector<P > vs[N], v1, v2;
vector<int > del;
set<P, Cmpr > ps[N];
set<int > ks;

int main() {
    io >> n;
    For (i, 1, n) {
        io >> l >> r >> c;
        int k = kind[c]; if (!k) k = kind[c] = ++cnt;
        vs[k].pb((P){l, r, k, i});
    }

    For (i, 1, cnt) {
        sort(vs[i].begin(), vs[i].end(), cmp);
        int lst = inf;
        for (auto &v : vs[i]) {
            lst = v.r = min(lst - 1, v.r);
            if (v.r < v.l) { puts("Sorry"); return 0; }
            v1.pb(v); v2.pb(v);
        }
    }

    sort(v1.begin(), v1.end(), cmpr);
    sort(v2.begin(), v2.end(), cmpl);
    int j = 0;
    For (i, 0, n - 1) if (!ok[v1[i].pos]) {
        ans++;
        for (; j < n && v2[j].l <= v1[i].r; ++j) {
            if (ps[v2[j].kd].empty()) ks.insert(v2[j].kd);
            ps[v2[j].kd].insert(v2[j]);
        }
        for (auto &k : ks) {
            auto it = ps[k].begin();
            ok[it->pos] = 1;
            ps[k].erase(it);
            if (ps[k].empty()) del.pb(k);
        }
        for (auto &k : del) ks.erase(k);
        del.resize(0);
    }
    printf("%d", ans);

    return 0;
}
