#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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
	inline bool operator ~ () const { return ~c; }
} io;

struct V { int x, y; };
V operator - (const V &a, const V &b) { return (V){a.x - b.x, a.y - b.y}; }
bool operator < (const V &a, const V &b) { return a.x^b.x? a.x<b.x: a.y<b.y; }
inline ll dot(const V &a, const V &b) { return 1ll * a.x * b.x + 1ll * a.y * b.y; }
inline ll cross(const V &a, const V &b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }
struct Node { V v; ll l, r; };

vector<Node > a, b;
int n;

namespace Seg {
    vector<V > o[N << 2];
    int pos[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void upd(int p, int l, int r, int x, int y, const V &v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) {
            int t = o[p].size() - 1;
            while (t > 0 && cross(v - o[p][t], v - o[p][t - 1]) <= 0) o[p].pop_back(), t--;
            return o[p].push_back(v);
        }
        M; upd(goL, x, y, v); upd(goR, x, y, v);
    }
    inline ll query(int p, int l, int r, int x, const V &v) {
        while (pos[p] < (int)o[p].size() - 1 && dot(v, o[p][pos[p]]) <= dot(v, o[p][pos[p] + 1])) pos[p]++;
        ll res = o[p].size()? dot(v, o[p][pos[p]]): 0;
        if (l == r) return res;
        M; return max(res, x<=m? query(goL, x, v): query(goR, x, v));
    }
}
using namespace Seg;

int main() {
    io >> n;
    For (i, 1, n) {
        int op, x, y;
        io >> op;
        if (op == 1) {
            io >> x >> y;
            a.pb((Node){(V){x, y}, i, n});
        } else if (op == 2) {
            io >> x;
            a[x - 1].r = i - 1;
        } else if (op == 3) {
            io >> x >> y;
            b.pb((Node){(V){x, y}, i, n});
        }
    }
    sort(a.begin(), a.end(), [](Node a, Node b) { return a.v < b.v; });
    for (auto &v : a) upd(1, 1, n, v.l, v.r, v.v);
    sort(b.begin(), b.end(), [](Node a, Node b) { return cross(a.v, b.v) < 0; });
    for (auto &v : b) v.r = query(1, 1, n, v.l, v.v);
    sort(b.begin(), b.end(), [](Node a, Node b) { return a.l < b.l; });
    for (auto &v : b) printf("%lld\n", v.r);

    return 0;
}
