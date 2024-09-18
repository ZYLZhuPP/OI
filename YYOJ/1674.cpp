#include<bits/stdc++.h>
using namespace std;

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

ll n, ans;
int cnt, m, P, s[N << 1];
vector<int > a[N << 1];

void write(int x, int y, int z) {
	for (auto &c : a[z + y]) {
		if (!cnt) return;
		cnt--;
		io << x << ' ' << y << ' ' << c << '\n'; 
	}
}

int main() {
	io >> n >> m >> P;
	n = n * n + 1;
	For (i, m + 1, P) {
		for (int j = m; j < 2 * P; j += i) {
			a[j].push_back(i);
			s[j]++;
		}
	}
	For (i, 1, 2 * P) s[i] += s[i - 1];
	
	cnt = 1e5;
	For (i, 1, P) {
		int x = n % i;
		ans += s[x + P] - (x? s[x - 1]: 0);
	}
	
	io << ans << '\n';
	For (i, 1, P) {
		if (!cnt) break;
		int x = n % i;
		For (j, max(0, m - x), P) write(i, j, x);
	}
	
	return 0;
} 
