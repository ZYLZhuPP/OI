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
	inline bool operator ~ () const { return ~c; }
} io;

int T, n, tot, pos[N];
char a[N];

int main() {
    io >> T;
    while (T--) {
        tot = 0;
        scanf("%s", a + 1);
        n = strlen(a + 1);
        bool flag = 0;
        For (i, 1, n / 2) if (a[i] ^ a[n - i + 1]) { puts("2"); printf("1 %d\n", n + 1); flag = 1; break; }
        if (flag) continue;
        For (i, 1, n) if (a[i] ^ a[1]) {
            if (tot && (i - pos[tot] != pos[1] || a[pos[tot]] ^ a[pos[1]])) {
                puts("3");
                printf("1 %d %d\n", i, n + 1);
                flag = 1;
                break;
            }
            pos[++tot] = i;
        }
        if (flag) continue;
        if (tot <= 1 || pos[1] == 2) { puts("-1"); continue; }
        puts("3");
        printf("1 %d %d\n", pos[1] + 2, n + 1);
    }

    return 0;
}
