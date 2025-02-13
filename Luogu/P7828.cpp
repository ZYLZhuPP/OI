#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

int n, K, q, B, cnt[N], a[N], b[N], id[N], tot;
ll f[105][N], ans;
vector<int > pos[N];

inline ll get(int x, int y) {
    if (cnt[x] > B) return f[id[x]][y];
    if (cnt[y] > B) return 1ll * cnt[x] * cnt[y] - f[id[y]][x];
    int a = 0, b = 0, res = 0, s = 0;
    while (a < (int)pos[x].size() || b < (int)pos[y].size()) {
        if (a < (int)pos[x].size() && (b == (int)pos[y].size() || pos[x][a] < pos[y][b])) s++, a++;
        else res += s, b++;
    }
    return res;
}

int main() {
    io >> n >> K >> q; B = 500;
    For (i, 1, n) io >> a[i], cnt[a[i]]++, pos[a[i]].pb(i);
    rFor (i, n, 1) ans += query(a[i] - 1), upd(a[i], 1);
    For (i, 1, K) if (cnt[i] > B) {
        id[i] = ++tot;
        int s = 0;
        For (j, 1, n) {
            if (a[j] == i) s++;
            else f[tot][a[j]] += s;
        }
    }
    For (i, 1, K) b[i] = i;
    while (q--) {
        int x;
        io >> x;
        ans += 1ll * cnt[b[x]] * cnt[b[x + 1]] - 2 * get(b[x + 1], b[x]);
        swap(b[x], b[x + 1]);
        printf("%lld\n", ans);
    }

    return 0;
}
