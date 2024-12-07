#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5;

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
	inline bool operator ~() {return ~c;}
} io;

int T, n, m, s[N], ss[N], b[N][N];
char a[N][N];
bool flag;

int main() {
	io >> T;
	while (T--) {
		flag = 0;
		memset(s, 0, sizeof(s)); 
		io >> n >> m;
		For (i, 1, n) For (j, 1, m) io >> a[i][j];
		
		For (i, 2, n) {
			ss[1] = 0;
			For (j, 2, m) {
				b[i][j] = a[i - 1][j] == a[i][j - 1];
				ss[j] = ss[j - 1] + b[i][j];
				if (b[i][j] && (s[j - 1] || b[i - 1][j] || b[i][j - 1])) flag = 1;
			}
			For (j, 2, m) s[j] += ss[j];
		}
		
		puts(flag? "1": "0");
	}
	
	return 0;
} 
