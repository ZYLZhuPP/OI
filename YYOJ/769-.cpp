#include<bit/stdc++.h>
using namespace std;

bool ok(LDB d){
    vector<Edge > g_[N];
    for(int i=1; i<=n; i++){
        g_[i]=g[i];
        for(auto &e: g_[i]) e.val-=d;
    }

}

int main(){
    io>>n>>m;
    LDB l=0, r=0;
    for(int i=1; i<=m; i++){
        int u,v; LDB w;
        io>>u>>v>>w;
        r=max(r, w);
        add(u, v, w);
        add(v, u, w);
    }
    while(l<=r){
        LDB mid=(l+r)/2.0;
        if(ok(mid)) ans=mid, r=mid-dd;
        else l=mid+dd;
    }
    printf("%.8lf", ans);
    return 0;
}
