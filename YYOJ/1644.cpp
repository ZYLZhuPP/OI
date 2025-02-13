#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

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
	inline bool operator ~() {return ~c;}
} io;

int n, ans[7] = {0, 1, 2, 2, 2, 3, 3};
int a[7][7] = {{},{0, 1}, {0, 1, 2}, {0, 1, 1, 2}, {0, 1, 1, 2, 2}, {0, 1, 1, 2, 2, 3}, {0, 1, 1, 2, 2, 3, 3}};

int main() {
	io >> n;
	if (n <= 6) {
		printf("%d\n", ans[n]);
		For (i, 1, n) printf("%d ", a[n][i]);
	} else {
		puts("4");
		For (i, 1, n) printf("%d ", (i - 1) % 4 + 1);
	}
	
	return 0;
}

