#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5, NN=5e3+5, M=5000;
const int INF=INT_MAX;

int n,a[N],b[N],f[N][NN],ans;

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(; !isdigit(ch); ch=gc())
		if(!(ch^'-')) f=-1;
		else if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc()) x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
	return 1; 
}

void init(){
    ans=INF;
    memset(f, 63, sizeof(f));
    memset(f[0], 0, sizeof(f[0]));
}

int main(){
    read(n);
    init();
    for(int i=1; i<=n; i++) read(a[i]);
    for(int i=1; i<=n; i++) read(b[i]);
    for(int i=1; i<=n; i++){
        for(int j=M; j>=0; j--){
            if(j>=a[i]) f[i][j]=min(f[i][j], f[i-1][j-a[i]]);
            f[i][j]=min(f[i][j], f[i-1][j]+b[i]);
        }
    }
    for(int i=0; i<=M; i++) ans=min(ans, max(i, f[n][i]));
    printf("%d", ans);
    return 0;
}
