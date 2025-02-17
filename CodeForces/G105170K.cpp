#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
typedef pair<ull, ull > P;
typedef __int128 lll;
const int S = 1e6 + 5;

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

int n, K;
char s[S];

namespace Hash {
    const ull base = 131, Mo = 1e17 + 1921;
    ull h1[S], h2[S], _1[S], _2[S];
    inline void init() {
        _1[0] = _2[0] = 1;
        For (i, 1, S - 1) _1[i] = _1[i - 1] * base, _2[i] = (_2[i - 1] * base) % Mo;
    }
    inline void init(char s[]) {
        init();
        int n = strlen(s + 1);
        For (i, 1, n) {
            int c = s[i];
            h1[i] = h1[i - 1] * base + c;
            h2[i] = (h2[i - 1] * base + c) % Mo;
        }
    }
    inline P ha(int l, int r) {
        return P(h1[r] - h1[l - 1] * _1[r - l + 1], (h2[r] - (lll)h2[l - 1] * _2[r - l + 1] % Mo + Mo) % Mo);
    }
}
using namespace Hash;

int main() {
    io >> n >> K;
    if (K == 1) return printf("%d", n), 0;
    scanf("%s", s + 1);
    init(s);
    rFor (i, n / K, 1) {
        P x = ha(1, i);
        int L = 1, cnt = 1;
        for (int j = i + 1; j <= n; j += i) {
            P y = ha(j, min(n, j + i - 1));
            if (x == y) {
                cnt++;
                if (cnt == K) return printf("%d", i * K), 0;
            } else {
                if (cnt == K - 1) {
                    int R = j - 1;
                    int l = 1, r = min(i - 1, L - 1), a = 0, b = 0;
                    while (l <= r) {
                        int mid = (l + r) >> 1;
                        if (ha(L - mid, L - 1) == ha(L + i - mid, L + i - 1)) a = mid, l = mid + 1;
                        else r = mid - 1;
                    }
                    l = 1, r = min(i - 1, n - R);
                    while (l <= r) {
                        int mid = (l + r) >> 1;
                        if (ha(R + 1, R + mid) == ha(R - i + 1, R - i + mid)) b = mid, l = mid + 1;
                        else r = mid - 1;
                    }
                    if (a + b >= i) return printf("%d", i * K), 0;
                }
                cnt = 1, x = y, L = j;
            }
        }
    }
    puts("0");

    return 0;
}
