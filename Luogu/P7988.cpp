#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); i++)
typedef set<int >::iterator It;
const int N = 2e5 + 5;

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

int n, h[N], pos[N], ans, ad[N];

set<int > tr;
void init() {
    pos[0] = 0;
    pos[N - 1] = -1;
    tr.insert(0);
    tr.insert(N - 1);
    For (i, 1, n){
        It it = upper_bound(tr.begin(), tr.end(), h[i]);
        int r = *it, l = *(--it);
        if (pos[r] > pos[l]) ad[h[i]]++;
        tr.insert(h[i]);
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> h[i], pos[h[i]] = i;
    init();
    puts("0");
    For (i, 1, n) {
        if (pos[i] < pos[i - 1]) ans--;
        ans += ad[i];
        printf("%d\n", ans);
    }
    return 0;
}
