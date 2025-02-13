#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4205;
int Mo;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }

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

int n, f0[N], f1[N], ans;

int main() {
    io >> n >> Mo;
    if (n == 1) { printf("%d", 1); return 0; }
    
    f1[2] = 1;
    For (i, 3, n) {
        swap(f0, f1);
        For (j, 2, i) f1[j] = mo(f1[j - 1] + f0[i + 1 - j]);
    }
    
    For (i, 2, n) ans = mo(ans + f1[i]);
    printf("%d", mo(ans << 1));

    return 0;
}
