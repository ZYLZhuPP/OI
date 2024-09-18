#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

template<class C> inline bool chkmax(C &x, const C &y) {return x<y? x=y, 1: 0;}
template<class C> inline bool chkmin(C &x, const C &y) {return x>y? x=y, 1: 0;}

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

int n, k, x, l[N], r[N], ma, mi;

void init() {
    for (int i = 1; i <= 1000000; i++) l[i] = n + 1, r[i] = 0;
}

int main() {
    io >> n >> k;
    init();
    for (int i = 1; i <= n; i++) {
        io >> x;
        chkmin(l[x], i);
        chkmax(r[x], i);
    }
    
    for (int i = 1000000; i >= 1; i--) {
        ma = 0, mi = n + 1;
        for (int j = 1; j * i <= 1000000; j++) chkmin(mi, l[j * i]), chkmax(ma, r[i * j]);
        if (ma - mi >= k) {
            printf("%d", i);
            break;
        }
    }

    return 0;
}
