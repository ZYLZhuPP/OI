#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5, M = 105, D = 1e7 + 5;

template<class C> inline bool chkmax(C &x, const C y){return x<y? x=y,1: 0;}

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

struct Edge {
    int to, w;
};
vector<Edge > es[N];

int n, m, root, ques[M];
bool ans[M], judge[D], vis[N];
int Siz[N], siz[N], msiz[N], dis[N];

int getG_(int u, int pre, int sum) {
    msiz[u] = 0;
    siz[u] = 1;
    int ret = 0;

    for (auto e : es[u])
        if (e.to ^ pre && !vis[e.to]) {
            int v = e.to;
            ret |= getG_(v, u, sum);
            siz[u] += siz[v];
            chkmax(msiz[u], siz[v]);
        }

    if (ret) {
        Siz[u] = sum - msiz[u];
        return ret;
    }

    if (max(msiz[u], sum - siz[u]) <= sum / 2)
        return u;

    Siz[u] = siz[u];
    return 0;
}

int getG(int u) {
    return getG_(u, u, Siz[u]);
}

vector<int > now, change;

void init_dis(int u, int pre) {
    if (dis[u] > D)
        return;

    now.emplace_back(dis[u]);

    for (auto e : es[u])
        if (e.to ^ pre && !vis[e.to]) {
            int v = e.to;
            dis[v] = dis[u] + e.w;
            init_dis(v, u);
        }
}

void solve(int u) {
    vis[u] = judge[dis[u] = 0] = 1;

    for (auto e : es[u])
        if (!vis[e.to]) {
            int v = e.to;
            dis[v] = dis[u] + e.w;
            init_dis(v, u);

            for (int i = 1; i <= m; i++)
                if (!ans[i]) {
                    for (auto w : now)
                        if (ques[i] >= w)
                            ans[i] |= judge[ques[i] - w];
                }

            for (auto w : now)
                judge[w] = 1, change.emplace_back(w);

            vector<int >().swap(now);
        }

    for (auto w : change)
        judge[w] = 0;

    vector<int >().swap(change);
}

void Divide(int rt) {
    int G = getG(rt);
    solve(G);

    for (auto e : es[G])
        if (!vis[e.to])
            Divide(e.to);
}

int main() {
    io >> n >> m;

    for (int i = 1; i < n; i++) {
        int u, v, w;
        io >> u >> v >> w;
        es[u].emplace_back((Edge) {
            v, w
        });
        es[v].emplace_back((Edge) {
            u, w
        });
    }

    root = 1;
    Siz[root] = n;

    for (int i = 1; i <= m; i++)
        io >> ques[i];

    Divide(root);

    for (int i = 1; i <= m; i++)
        puts(ans[i] ? "AYE" : "NAY");

    return 0;
}
