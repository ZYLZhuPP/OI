#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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
	inline IO& operator >> (char &x){
		while ((c = gc()) < 33 && ~c);
		x = c; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, B, R, s[N], a[N], t, st[N];
vector<int > ans;
char x;

int main() {
    io >> n >> R >> B;
    For (i, 1, n) io >> x, a[i] = x == 'B', s[a[i]]++;
    if (s[0] * B != s[1] * R || n % (B + R)) {
        puts("NO");
        return 0;
    }
    s[0] = s[1] = 0;

    For (i, 1, n) {
        st[++t] = i;
        s[t] = s[t - 1] + a[i];
        if (t >= B + R && s[t]  - s[t - B - R] == B)
            For (j, 1, B + R) ans.push_back(st[t--]);
    }
    printf("YES\n%d\n", n / (B + R));
    for (int i = n - 1; i >= 0; --i) {
        if (i % (B + R) == 0) printf("%d\n", ans[i]);
        else printf("%d ", ans[i]);
    }

    return 0;
}
