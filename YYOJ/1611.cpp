#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

int n, a[N], b[N], s[N], ans;

void solve(int l, int r) {
	if (r - l + 1 <= ans) {For (i, l, r) s[a[i]] = 0; return;}

	int lim = b[r - l + 1];
    int lx = l, rx = r;
    while (lx <= rx && s[a[lx]] >= lim && s[a[rx]] >= lim) lx++, rx--;
    if (lx > rx) {ans = r - l + 1; For (i, l, r) s[a[i]] = 0; return;}
    
    int l1, r1, l2, r2;
    if (s[a[lx]] < lim) l1 = l, r1 = lx - 1, l2 = lx + 1, r2 = r, s[a[lx]]--;
    else l1 = rx + 1, r1 = r, l2 = l, r2 = rx - 1, s[a[rx]]--;

    For (i, l1, r1) s[a[i]]--;
    solve(l2, r2);
    For (i, l1, r1) s[a[i]]++;
    solve(l1, r1);
}

int main() {
	io >> n;
	For (i, 1, n) io >> a[i], s[a[i]]++;
	For (i, 1, n) io >> b[i];
	
	solve(1, n); 
	
	printf("%d", ans);
	
	return 0;
}

