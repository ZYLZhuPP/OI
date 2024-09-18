#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;
const ll inf = 2e18;

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

int T, n, q, a[N], stk[N], top;
ll b[N];

int main() {
    io >> T;
    while (T--) {
        top = 0;
        io >> n >> q;
        For (i, 0, n - 1) io >> a[i], a[n + i] = a[i], b[i] = inf;
        For (i, 0, 2 * n - 1) if (b[i % n] == inf) {
            if (a[i] == n + 1) stk[++top] = i;
            else if (a[i] == n - 1) {
                if (top) {
                    int x = stk[top--];
                    b[x] = b[i % n] = i + 1ll * (i - x) * n;
                }
            }
        }
        while (q--) {
            ll x;
            io >> x;
            int y = x % n, z = x % (n + 1);
            //cout << x << " " << y << " " << z << endl;
            if (a[y] == n - 1 && x < b[y]) printf("%d ", n - 1);
            else if (z < n && a[z] == n + 1 && x < b[z]) printf("%d ", n + 1);
            else printf("%d ", n);
        }
        puts("");
    }

    return 0;
}
