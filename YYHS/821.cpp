#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
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
	inline bool operator ~ () {return ~c;}
} io;

int n, a[N], b[N], mi[N], ma[N], cnt;
int q[N];
ll m, ans, f[N], s[N];

namespace init {
    int main() {
        cnt = 0;
        mi[0] = INT_MAX;
        For (i, 1, n) mi[i] = min(mi[i - 1], b[i]);
        rFor (i, n, 1) ma[i] = max(ma[i + 1], a[i]);
        int A = 0; ll B = 0;
        For (i, 1, n) {
            A = max(A, a[i]);
            B += b[i];
            if (mi[i] > ma[i + 1]) {
                a[++cnt] = A; s[cnt] = B;
                A = 0;
            }
        }
        return 0;
    }
}

bool check(ll x) {
    multiset<ll > st;
    int h = 1, t = 0, le = 0;
    q[++t] = 0;

    For (i, 1, cnt) {
        while (h <= t && s[i] - s[q[h]] > x) {
            if (h < t) st.erase(f[q[h]] + a[q[h + 1]]);
            h++;
        }
        while (h <= t && a[q[t]] < a[i]) {
            if (h < t) st.erase(f[q[t - 1]] + a[q[t]]);
            t--;
        }
        if (h <= t) st.insert(f[q[t]] + a[i]);
        q[++t] = i;
        
        while (s[i] - s[le] > x) le++; if (le == i) return 0;
        f[i] = f[le] + (le==q[h]? a[q[h + 1]]: a[q[h]]);
        if (h < t) f[i] = min(f[i], *st.begin());
    }

    return f[cnt] <= m;
}

int main() {
    io >> n >> m;
    ll l = 1, r = 0;
    For (i, 1, n) {
        io >> a[i] >> b[i];
        r += b[i];
    }
    init::main();

    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }

    printf("%lld", ans);

    return 0;
}
