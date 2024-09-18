#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^'-')) f=-1;
		for(x=0; isdigit(c); c=gc()) x=x*10+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int n,m,a,b,s[N][N],p[N],ans,sum;

bool ok(int k){
    memset(p, 0, sizeof(p));
    int ct=0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) p[j]+=s[i][j];
        int cnt=0, lst=0;
        for(int j=1; j<=m; j++) if(p[j]-p[lst]>=k){
            cnt++; lst=j;
        }
        if(cnt>=b){
            memset(p, 0, sizeof(p));
            ct++;
        }
    }
    return ct>=a;
}

int main(){
    io>>n>>m>>a>>b;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            int x;
            io>>x;
            s[i][j]=s[i][j-1]+x;
        }
        sum+=s[i][m];
    }
    int l=0, r=sum/a/b;
    while(l<=r){
        int mid=(l+r)>>1;
        if(ok(mid)) ans=mid, l=mid+1;
        else r=mid-1;
    }
    printf("%d", ans);
    return 0;
}
