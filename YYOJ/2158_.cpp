#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
const int N = 3e3 + 5;
const ull P = 1331;

struct IO {
    char c; int f;
#define gc() getchar()
    IO& operator >> (int &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
} io; 

int n, a[N], cnt[N], ans, lst[N][N];
ull ha[N];

int main() {
    io >> n;
    ans = n * (n + 1) / 2;
    For (i, 1, n) io >> a[i];
    For (len, 1, n - 1) {
        unordered_map<ull, bool> mp;
        For (i, len, n) {
            int c = a[i], j = i - len + 1, k = lst[j][c];
            if (!k) k = lst[j][c] = ++cnt[j];
            ha[j] = ha[j] * P + k;
            if (mp[ha[j]]) ans--;
            else mp[ha[j]] = 1;
        }
    }
    printf("%d", ans);

    return 0;
}
