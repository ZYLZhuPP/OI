#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e6 + 5;

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

int T, n, z[N], num[N], sum, cnt[26];
ll ans;
char s[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (x++; x < N; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (x++; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

int main() {
    io >> T;
    while (T--) {
        ans = sum = 0;
        memset(o, 0, sizeof o);
        memset(cnt, 0, sizeof cnt);
        scanf("%s", s + 1);
        n = strlen(s + 1);
        z[1] = n;
        int l = 0, r = 0;
        For (i, 2, n) {
            z[i] = max(0, min(z[i - l + 1], r - i + 1));
            while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) z[i]++;
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
        num[n + 1] = 0;
        rFor (i, n, 1) {
            num[i] = num[i + 1];
            int c = s[i] - 'a';
            if (++cnt[c] & 1) num[i]++; else num[i]--;
        }
        memset(cnt, 0, sizeof cnt);
        For (i, 1, n - 1) {
            if (i >= 2) {
                int x = z[i + 1] / i + 1;
                if (i * x == n) x--;
                ans += 1ll * (x / 2) * query(num[2 * i + 1]) + 1ll * (x - x / 2) * query(num[i + 1]);
            }
            int c = s[i] - 'a';
            if (++cnt[c] & 1) sum++; else sum--;
            upd(sum, 1);
        }
        printf("%lld\n", ans);
    }

    return 0;
}
