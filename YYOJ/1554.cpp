#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e3 + 5, M = 3e5 + 5, KK = 1e4 + 5;

struct IO {
	char c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

struct Edge {
    int u, v;
    ll w;
    int id;

    bool operator < (const Edge &x) const {
        return w > x.w;
    }
};
vector<Edge > es;

int n, m, K, tim[M], in[N][N], u, v, f[N][KK];
ll w;

int find(int k, int u) {
    if (f[u][k] ^ u) return f[u][k] = find(k, f[u][k]);
    return f[u][k];
}

void merge(int k, int u, int v) {
    f[u][k] = v;
}

void init() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) in[i][j] = in[j][i] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= K; ++j) f[i][j] = i;
}

int main() {
    io >> n >> m >> K;
    init();
    for (int i = 0; i < m; ++i) {
        io >> u >> v >> w;
        es.push_back({u, v, w, i});
    }
    sort(es.begin(), es.end());

    for (int i = 0; i < m; ++i) {
        int u = es[i].u, v = es[i].v, id = es[i].id;
        int k = in[u][v];
        while (find(k, u) == find(k, v) && k <= K) k++;
        if (k > K) continue;
        tim[id] = k;
        merge(k, f[u][k], f[v][k]);
        in[u][v] = in[v][u] = k + 1;
    }

    for (int i = 0; i < m; ++i) printf("%d\n", tim[i]);

    return 0;
}
