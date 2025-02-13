#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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
	inline bool operator ~ () const { return ~c; }
} io;

int n, p[N], q[N];
ll ans;
char st[N];

int main() {
    io >> n;
    scanf("%s", st + 1);
    int j = 0;
    For (i, 2, n) {
        while (j && st[i] ^ st[j + 1]) j = p[j];
        if (st[i] == st[j + 1]) j++;
        p[i] = j; q[i] = q[j]? q[j]: j;
        if (q[i]) ans += i - q[i];
    }
    printf("%lld", ans);

    return 0;
}
