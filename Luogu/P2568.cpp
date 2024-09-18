
#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e7 + 5;

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

int n, phi[N], pri[N], psz, mip[N];
ll sf[N], ans;

void init_Phi() {
    phi[1] = 1;
    For (i, 2, n) {
        if (!mip[i]) {
            pri[mip[i] = ++psz] = i;
            phi[i] = i - 1;
        }
        For (j, 1, mip[i]) {
            int ne = i * pri[j];
            if (ne > n) break;
            mip[ne] = j;
            if (j ^ mip[i]) phi[ne] = phi[i] * phi[pri[j]];
            else phi[ne] = phi[i] * pri[j];
        }
    }
    For (i, 1, n) sf[i] = sf[i - 1] + phi[i];
}

int main() {
    io >> n;
    init_Phi();
    For (i, 1, psz) ans += 2 * sf[n / pri[i]] - 1;
    printf("%lld", ans);

    return 0;
}
