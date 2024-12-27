#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define lowbit(x) ((x) & -(x))
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
    inline bool operator ~ () const { return ~c; }
} io;

int T, n, ans;
char a[N];
vector<int > es[N];

int main() {
    For (i, 1, 1e5) if (i + lowbit(i) <= 1e5) es[i + lowbit(i)].pb(i);
    io >> T;
    while (T--) {
        ans = 0;
        io >> n;
        scanf("%s", a + 1);
        For (i, 1, n) {
            int cnt = 0;
            for (auto &j : es[i]) if (a[j] & 1) cnt++;
            if (a[i] & 1) ans += !cnt;
            else ans += cnt==1;
        }
        printf("%d\n", ans);
    }

    return 0;
}
