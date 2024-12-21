#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 15e3 + 5;

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

int n, m, pos[N], cnt[N], C, S, p, s[N];
char a[N];
ll ans;

inline void add(int x) {
    cnt[x]++;
    if (x < p) C++, S -= x;
    else C--, S += x;
}

inline void inc() {
    C += 2 * cnt[p], S -= 2 * cnt[p] * p;
    p++;
}

inline void dec() {
    p--;
    C -= 2 * cnt[p], S += 2 * cnt[p] * p;
}

int main() {
    scanf("%s", a + 1); n = strlen(a + 1);
    For (i, 1, n) s[i] = s[i - 1] + (a[i] == 'G');
    For (i, 1, n) if (a[i] == 'G') pos[++m] = i;
    pos[m + 1] = n + 1;
    For (l, 1, n) For (r, l, n) ans -= ((r - l) & 1) & ((s[r] - s[l - 1]) & 1);
    For (i, 1, m) {
        C = S = p = 0;
        memset(cnt, 0, sizeof cnt);
        for (int l = i, r = i; l >= 1 && r <= m; l--, r++) {
            if (l ^ r) add(pos[l] + pos[r]);
            For (x, pos[l - 1] + 1, pos[l]) For (y, pos[r], pos[r + 1] - 1) {
                while (p < x + y) inc();
                while (p > x + y) dec();
                if ((y - x + 1) & 1) ans += abs((x + y) / 2 - pos[i]) + C * (x + y) + S;
            }
        }
    }
    For (i, 1, m - 1) {
        C = S = p = 0;
        memset(cnt, 0, sizeof cnt);
        for (int l = i, r = i + 1; l >= 1 && r <= m; l--, r++) {
            add(pos[l] + pos[r]);
            For (x, pos[l - 1] + 1, pos[l]) For (y, pos[r], pos[r + 1] - 1) {
                while (p < x + y) inc();
                while (p > x + y) dec();
                ans += C * (x + y) + S;
            }
        }
    }
    printf("%lld", ans);

    return 0;
}
