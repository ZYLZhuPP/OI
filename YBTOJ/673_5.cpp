#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e4 + 5;

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
	inline bool operator ~ () { return ~c; }
} io;

namespace tr {
    const int N = 505, M = 5505; 
    int o[N][M];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int y, int v) {
        for (int i = x; i < N; i += lowbit(i))
            for (int j = y; j < M; j += lowbit(j))
                o[i][j] = max(o[i][j], v);
    }
    inline int pre(int x, int y) {
        int r = 0;
        for (int i = x; i; i -= lowbit(i))
            for (int j = y; j; j -= lowbit(j))
                r = max(r, o[i][j]);
        return r;
    }
}

int n, K, a[N];

int main() {
    io >> n >> K;
    For (i, 1, n) io >> a[i];

    For (i, 1, n)
        rFor (k, K, 0)
            tr::upd(k + 1, a[i] + k, tr::pre(k + 1, a[i] + k) + 1);
    printf("%d", tr::pre(K + 1, 5500));
   
    return 0;
}
