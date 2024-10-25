#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e6 + 5;

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
    inline IO& operator >> (char *x) {
    	while ((c = gc()) < 33 && ~c);
    	while (c > 32) *x++ = c, c = gc();
    	*x = 0; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, b[N][26], f[N];
ll ans;
char a[N];

int main() {
    io >> n;
    io >> (a + 1);

    for (int i = 1; i <= n; ++i) {
        int c = a[i] - 'a';
        int j = 0;
        if (a[i] == a[i - 1]) j = i - 1;
        else j = b[i - 1][c];

        if (j) {
            f[i] = f[j - 1] + 1;
            for (int k = 0; k < 26; ++k) b[i][k] = b[j - 1][k];
            if (j > 1) b[i][a[j - 1] - 'a'] = j - 1;
        }

        ans += f[i];
    }

    printf("%lld", ans);

    return 0;
}