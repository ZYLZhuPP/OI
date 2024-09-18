#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 405;
const ll Mo = 1e9 + 7;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

ll n, f[N][N], inv[N], fac[N], invfac[N];
char st[N];

ll C(int n, int m) {
    if (n < m) return 0;
    if (!m) return 1;
    return fac[n] * invfac[n - m] % Mo * invfac[m] % Mo;
}

void init() {
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= 400; i++) inv[i] = (Mo - Mo / i) * inv[Mo % i] % Mo;
    fac[0] = invfac[0] = 1;
    for (int i = 1; i <= 400; i++) fac[i] = (fac[i - 1] * i) % Mo, invfac[i] = (invfac[i - 1] * inv[i]) % Mo;
}

int main() {
    io >> n;
    init();
    scanf("%s", st + 1);

    for (int i = 1; i <= n + 1; i++) f[i][i - 1] = 1;
    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            for (int k = l; k <= r; k++) if (st[k] ^ st[r + 1]) {
                f[l][r] = (f[l][r] + f[l][k - 1] * f[k + 1][r] % Mo * C(r - l, k - l)) % Mo;
            }
        }
    }

    printf("%lld", f[1][n]);
    return 0;
}
