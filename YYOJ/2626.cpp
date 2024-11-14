#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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

int K, n, q, m, ans;
char s[N], t[N];

int main() {
    io >> K;
    scanf("%s", s + 1); n = strlen(s + 1);
    io >> q;
    while (q--) {
        ans = 0;
        scanf("%s", t + 1); m = strlen(t + 1);
        if (m <= K) { printf("%d\n", n - m + 1); continue; }
        For (i, 1, n - m + 1) {
            int l = m + 1, r = 0;
            For (j, 1, m) if (s[i + j - 1] ^ t[j]) { l = j; break; }
            rFor (j, m, 1) if (s[i + j - 1] ^ t[j]) { r = j; break; }
            if (r - l < K) ans++;
        }
        printf("%d\n", ans);
    }

    return 0;
}
