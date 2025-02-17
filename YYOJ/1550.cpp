#include<bits/stdc++.h>
using namespace std;

const int N = 105;

struct IO {
    char c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
}io;

mt19937 rnd(time(0));

int n, m, siz[N], cnt;
string st, a, ban[5];
vector<int > q, es[N];

int choose() {
    int s = 0;
    for (auto &u : q) s += siz[u];
    int pos = rnd() % s + 1;
    int sq = q.size();
    for (int i = 0; i < sq; ++i) {
        pos -= siz[q[i]];
        if (pos <= 0) return i;
    }
    return 0;
}

void dfs(int u) {
    siz[u] = 1;
    for (auto &v : es[u]) 
        dfs(v), siz[u] += siz[v];
}

bool test() {
    string st;
    q.push_back(0);

    while (!q.empty()) {
        int pos = choose();
        int u = q[pos];
        q.erase(q.begin() + pos);
        st += a[u];
        for (auto &v : es[u])
            q.push_back(v);
    }

    for (int i = 0; i < m; ++i) if (~st.find(ban[i]))
        return 0;
    return 1;
}

int main() {
    io >> n;
    int u;
    for (int i = 1; i <= n; ++i) {
        io >> u;
        es[u].push_back(i);
    }
    dfs(0);

    cin >> a; a = ' ' + a;
    io >> m;
    for (int i = 0; i < m; ++i) 
        cin >> ban[i];

    for (int i = 1; i <= 10000; ++i) if (test())
        cnt++;

    printf("%.2lf", (double)cnt / 10000.0);

    return 0;
}
