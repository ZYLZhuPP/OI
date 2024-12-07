#include<bits/stdc++.h>
using namespace std;

typedef int ll;
const int N = 130005;
const ll INF = 1e9;

namespace Dinic {
    struct Edge {
        int u, v;
        ll w;
        
        inline bool operator < (const Edge &a) const {
            return w > a.w;
        }
    };
    
    struct Node {
        int to, id;
        ll f;
    };
    
    vector <Edge> Tmp;
    vector <Node> E[N];
    
    int Now[N];
    
    inline void Add_Edge(const int u, const int v, const ll w) {
        Tmp.push_back({u, v, w});
    }
    
    inline void add_edge(const int x) {
        E[Tmp[x].u].push_back({Tmp[x].v, Now[Tmp[x].v]++, Tmp[x].w});
        E[Tmp[x].v].push_back({Tmp[x].u, Now[Tmp[x].u]++, 0});
    }
    
    int Cur[N], Dep[N];
    int S, T;
    
    inline bool BFS() {
        memset(Cur, 0, sizeof Cur);
        memset(Dep, 0, sizeof Dep);
        queue <int> q; 
        q.push(S), Dep[S] = 1;
        int u;
        while (!q.empty()) {
            u = q.front(), q.pop();
            for (auto i : E[u]) 
                if(!Dep[i.to] && i.f) {
                    Dep[i.to] = Dep[u] + 1, q.push(i.to);
                    if(i.to == T) return 1;
                }
        }
        return 0;
    }
    
    inline ll DFS(const int x, const ll MAXF) {
        if(x == T || MAXF == 0) return MAXF;
        ll f = 0;
        for (int i = Cur[x]; i < (int) E[x].size() && f < MAXF; ++i) {
            Cur[x] = i;
            if(Dep[E[x][i].to] == Dep[x] + 1 && E[x][i].f) {
                ll TmpF = DFS(E[x][i].to, min(MAXF - f, E[x][i].f));
                if(!TmpF) Dep[E[x][i].to] = 0;
                f += TmpF, E[x][i].f -= TmpF, E[E[x][i].to][E[x][i].id].f += TmpF;
            }
        }
        return f;
    }
    
    inline ll Solve() {
        ll f = 0;
        while (BFS()) f += DFS(S, INF);
        return f;
    }
    
    inline ll dinic() {
        sort(Tmp.begin(), Tmp.end());
        ll Ans = 0;
        for (int i = 1e9, j = 0; j < (int) Tmp.size(); i /= 20) {
            while (Tmp[j].w >= i && j < (int) Tmp.size()) add_edge(j), ++j;
            Ans += Solve();
        }
        return Ans;
    }
}

namespace Value {
    using namespace Dinic;
    int N, M, u, v, f;
    
    inline void Solve() {
        ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

        cin >> N >> M >> S >> T;
        for (int i = 1; i <= M; ++i) 
            cin >> u >> v >> f, Add_Edge(u, v, f);
        
        cout << dinic() << endl;
    }
}

int main() {
   
    Value::Solve();
    
    return 0;
}
