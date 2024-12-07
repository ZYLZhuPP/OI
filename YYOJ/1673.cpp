#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
inline void chkmin(ll &x, const ll &y) { x>y? x=y: 0; }
const int N = 8005;

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
	int st[66], t;
#define pc(c) putchar(c)
	template<class C>
	inline IO& operator << (C x) {
		if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
		while (x) st[++t] = x % 10, x /= 10;
		while (t) pc(st[t--] ^ 48);
		return *this;
	}
	inline IO& operator << (char x) {
		pc(x); return *this;
	}
	inline bool operator ~() {return ~c;}
} io;

int n;
ll a[N << 1], S, s[N << 1], ss[N << 1], f[N];

int main() {
	io >> n;
	For (i, 1, n) io >> a[i], S += a[i];
	For (i, n + 1, n * 2) a[i] = a[i - n];
	For (i, 1, 2 * n) ss[i] = ss[i - 1] + a[i];
	s[1] = a[1]; For (i, 2, 2 * n) s[i] = s[i - 2] + a[i];
	
	memset(f, 31, sizeof(f));
	For (i, 1, 2 * n) {
		int L = max(1, i - n + 1), R = min(i, n);
		int t = i;
		ll s_ = i>1? s[i - 2]: 0;
		ll sum = S - 2*(ss[i - 1] - s_);
		For (j, L, R) {
			int r = j + n - 1;
			while (t + 2 < r && abs(sum - ((s[t + 2] - ss[j - 1])<<1)) <= abs(sum - ((s[t] - ss[j - 1])<<1))) t += 2;
			chkmin(f[j], abs(sum - ((s[t] - ss[j - 1])<<1)));
		}
	} 
	
	For (i, 1, n) io << f[i] << '\n';
	
	return 0;
}
