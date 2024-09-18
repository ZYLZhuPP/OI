#include<bits/stdc++.h>
using namespace std;

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
	inline bool operator ~() {return ~c;}
} io;

int n, ans, m, k, id[N];
ll T, x, y, a[N], b[N], c[35], f[N][35];
vector<ll > s(1, 0);

bool cmp(const int &x, const int &y) { return b[x] * (a[y] - 1) < b[y] * (a[x] - 1); }

int main() {
	io >> n >> T;
	For (i, 1, n) {
		io >> x >> y;
		if (!x) s.push_back(y + 1);
		else a[++m] = x + 1, b[m] = x + y + 1, id[m] = m;
	}
	sort(s.begin(), s.end());
	int n = s.size() - 1;
	For (i, 1, n) s[i] += s[i - 1];
	
	sort(id + 1, id + m + 1, cmp);
	memset(f, 31, sizeof(f));
	f[0][0] = 0;
	For (i, 1, m) {
	    f[i][0] = 0;
	    For (j, 1, 31) {
	        f[i][j] = f[i - 1][j];
	        if (f[i - 1][j - 1] <= T) f[i][j] = min(f[i][j], f[i - 1][j - 1] * a[id[i]] + b[id[i]]);
	    }
	}
	
	int d = 0;
	for (int i = 31; i >= 0; --i) if (f[m][i] <= T) {
		while (d < n && s[d + 1] + f[m][i] <= T) d++;
		ans = max(ans, i + d);
	}
	
	printf("%d", ans);
	
	return 0;
}

