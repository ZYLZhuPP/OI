#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 22e5 + 5, lgN = 22;

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
    inline bool operator ~() {return ~c;}
} io;

int n, u, s[N], in[N], out[N], tim, stk[N], t;
vector<int > es[N];

void dfs(int u, int pre) {
    in[u] = ++tim;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
    }
    out[u] = tim;
}

int main() {
    io >> n;
    For (i, 2, n) io >> u, es[u].push_back(i);
    dfs(1, 0);
    
    stk[++t] = 1;
    For (i, 2, n) {
        while (in[i] < in[stk[t]] || in[i] > out[stk[t]]) s[i]--, t--;
        stk[++t] = i;
    }
    
    For (i, 1, n) s[i] += s[i - 1] + 1, printf("%d\n", s[i]);
    
    return 0;
} 
