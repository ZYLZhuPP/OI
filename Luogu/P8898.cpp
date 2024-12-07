#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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
    inline bool operator ~ () { return ~c; }
} io;

int n, K, T, now[2], cnt;
char s[N], ans[N];

int main() {
    io >> T;
    while (T--) {
        now[0] = now[1] = cnt = 0;
        io >> n >> K;
        For (i, 1, n) ans[i] = '.';
        ans[n + 1] = 0;
        scanf("%s", s + 1);
        For (i, 1, n) {
            int k = s[i] == 'G';
            if (now[k] < i) {
                rFor (j, min(i + K, n), i - K) if (ans[j] == '.') {
                    ans[j] = s[i]; now[k] = j + K; cnt++;
                    break;
                }
            }
        }
        printf("%d\n", cnt);
        printf("%s\n", ans + 1);
    }

    return 0;
}