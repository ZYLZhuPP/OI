#include<bits/stdc++.h>
using namespace std;

#define pb push_back
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

int T, n, l[N], r[N], flag;

int main() {
    io >> T;
    while (T--) {
        flag = 1;
        io >> n;
        priority_queue<int, vector<int >, greater<int > > q;
        vector<int > p[n + 1];
        For (i, 1, n) io >> l[i];
        For (i, 1, n) io >> r[i], p[l[i]].pb(r[i]);
        For (i, 0, n - 1) {
            for (auto &r : p[i]) q.push(r);
            if (q.empty() || q.top() < i) { flag = 0; break; }
            else q.pop();
        }
        puts(flag? "YES": "NO");
    }

    return 0;
}