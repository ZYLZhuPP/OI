#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e4 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

struct Node {
    int x, y;
    string s0, s1, s2, s3;
    bool operator < (const Node &a) const { return x^a.x? x<a.x: y<a.y; }
} a[N];
vector<Node > ans;

unordered_map<string, bool > vis;

int n, m, t, K;

int main() {
    io >> n >> m >> t >> K;
    string s0, s1, s2, s3; int x, y;
    For (i, 1, n) cin >> s0 >> s1 >> s2 >> s3 >> y >> x, a[i] = {x, y, s0, s1, s2, s3};
    sort(a + 1, a + n + 1);
    For (i, 1, n) if ((int)ans.size() < K && !vis[a[i].s1] && !vis[a[i].s2] && !vis[a[i].s3]) ans.pb(a[i]), vis[a[i].s1] = 1, vis[a[i].s2] = 1, vis[a[i].s3] = 1;
    printf("%d\n", (int)ans.size());
    for (auto &[x, y, s0, s1, s2, s3] : ans) cout << s0 << " " << s1 << " " << s2 << " " << s3 << endl; 

    return 0;
}
