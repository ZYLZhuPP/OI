#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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
	inline IO& operator >> (char &x) {
		while ((c = gc()) < 33 && ~c);
		x = c; return *this;
	}
	int st[66], t;
	inline bool operator ~() {return ~c;}
} io;

int T, n, a[N], b[N], s[3][3], s1, s2, d;
bool flag; 

bool ok(int x) {
	if (x < 0) return 0;
	if (!s[1][1]) {
		if (x & 1 || x > 2 * s[2][2]) return 0;
		s[2][2] = x / 2;
		return 1;
	}
	if (x <= s[1][1] + 2 * s[2][2]) {
		if (2 * s[2][2] <= x) x -= 2*s[2][2], s[1][1] = x;
		else s[2][2] = x / 2, s[1][1] = x & 1;
		return 1;
	}
	return 0;
}

#define pc(c) putchar(c)
void write() {
	For (i, 1, n) {
		s[a[i]][b[i]]? s[a[i]][b[i]]--, pc('1'): pc('0');
		pc(' ');
	}
	pc('\n');
}

int main() {
	io >> T;
	while (T--) {
		flag = 0;
		memset(s, 0, sizeof(s));
		s1 = s2 = 0;
		io >> n;
		For (i, 1, n) io >> a[i], s1 += a[i];
		For (i, 1, n) {
			io >> b[i];
			s2 += b[i];
			s[a[i]][b[i]]++;
		}
		if (s1 & 1 || s2 & 1) {
			puts("-1");
			continue;
		}
		s1 /= 2; s2 /= 2;
		
		d = s1 - s2;
		int &S1 = d>0? s[2][1]: s[1][2];
		int &S2 = d>0? s[1][2]: s[2][1];
		d = abs(d);
		if (S1 < d) {
			puts("-1");
			continue;
		}
		
		For (i, 0, min(S1 - d, S2)) {
			if (ok((s1 + s2 - 3 * (d + 2 * i)) / 2)) {
				S1 = d + i;
				S2 = i;
				write();
				flag = 1;
				break;
			}
		}
		if (!flag) puts("-1");
	}
	
	return 0;
} 
