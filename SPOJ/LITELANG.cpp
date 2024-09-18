#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e4 + 5, inf = 1e9;

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

int T, n, m, sum, ans, w[N];

int main() {
    io >> T;
    while (T--) {
        sum = 0; ans = inf;
        multiset<int > s;
        io >> n >> m;
        For (i, 1, m) io >> w[i], s.insert(w[i]), sum += w[i];
        while ((int)s.size() > n) sum -= *s.rbegin(), s.erase(prev(s.end()));
        while (sum < ans) {
            if ((int)s.size() == n) ans = sum;
            int x = *s.begin(); s.erase(s.begin()); sum -= x;
            For (i, 1, m) s.insert(x + w[i]), sum += x + w[i];
            while ((int)s.size() > n) sum -= *s.rbegin(), s.erase(prev(s.end()));
        }
        printf("%d\n", ans);
    }

    return 0;
}
//Luogu SP186
