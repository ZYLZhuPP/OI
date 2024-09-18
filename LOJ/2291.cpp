#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5, C = 12;

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline IO& operator >> (char *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int n, op, tot, ch[N * 65][C], cnt[N * 65];
ll a, b, c, ans;
vector<int > t[N * 65];
char st[65];

void add(char st[], int d, int tim) {
    int len = strlen(st);
    int u = 0;
    For (i, 0, len - 1) {
        int c = st[i] - 'a';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c]; cnt[u] += d;
        if (cnt[u] > t[u].size()) t[u].push_back(tim);
    }
}

int query(char st[], int x) {
    int len = strlen(st);
    int u = 0;
    For (i, 0, len - 1) {
        int c = st[i] - 'a';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    if (t[u].size() > x) return t[u][x];
    return -1;
}

int main() {
    io >> n;
    For (i, 1, n) {
        io >> op >> st;
        if (op == 1) add(st, 1, i);
        else if (op == 2) add(st, -1, i);
        if (op == 3) {
            io >> a >> b >> c;
            ans = query(st, (a * abs(ans) + b) % c);
            printf("%lld\n", ans);
        }
    }

    return 0;
}
