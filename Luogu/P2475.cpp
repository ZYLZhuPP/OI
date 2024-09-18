#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 55;

struct IO {
	char c; int f;
#define gc() getchar()
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, ch[N][2], ans[N], rt;

int main() {
    memset(ch, -1, sizeof ch);
    io >> n;
    For (i, 1, n) {
        int x;
        io >> x;
        if (x < 100) ch[x][0] = i;
        else ch[x - 100][1] = i;
    }
    For (i, 1, n + 1) {
        int u = rt;
        while (~ch[u][1]) u = ch[u][0];
        if (~ch[u][0] && !~ch[ch[u][0]][0]) u = ch[u][0];
        ans[i] = u;
        if (u == rt) { rt = ch[rt][0]; continue; }
        int v = rt;
        while (ch[v][0] ^ u) {
            swap(ch[v][0], ch[v][1]);
            v = ch[v][1];
        }
        ch[v][0] = ch[v][1];
        ch[v][1] = ch[u][0];
    }
    rFor (i, n + 1, 1) printf("%d ", ans[i]);

    return 0;
}
