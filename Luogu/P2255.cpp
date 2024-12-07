#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e4 + 5;

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

struct Node {
    int l, r;
    bool operator < (const Node &a) const { return a.r < r; }
};

int n, ed1, ed2, ans;
priority_queue<Node > q;

int main() {
    io >> n;
    int l, r;
    For (i, 1, n) io >> l >> r, q.push({l, r});
    For (i, 1, n) {
        int l = q.top().l, r = q.top().r; q.pop();
        if (l >= ed1) ans++, ed1 = r;
        else if (l >= ed2) ans++, ed2 = r;
        if (ed2 > ed1) swap(ed1, ed2);
    }
    printf("%d", ans);

    return 0;
}