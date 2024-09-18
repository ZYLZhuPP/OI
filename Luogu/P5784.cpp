#include <bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll Mo = 1e17;
ll n, c[109], r[309], f[2][129][129], s;

int main() {
	scanf("%lld", &n);
	For(i, 1, 3) scanf("%lld", c + i), s += c[i];
	For(i, 1, n) scanf("%lld", r + i), s -= r[i];
	if (s) return puts("0"), 0;
	f[0][0][0] = 1;
	For(i, 1, n) For(j, 0, c[1]) For(k, 0, c[2]) {
		f[i & 1][j][k] = 0;
		for (int l = 0; l <= j && l <= r[i]; ++l)
			for (int m = 0; m <= k && l + m <= r[i]; ++m)
				f[i & 1][j][k] = (f[i & 1][j][k] + f[i & 1 ^ 1][j - l][k - m]) % Mo;
	}
	printf("%lld\n", f[n & 1][c[1]][c[2]]);
	return 0;
}
