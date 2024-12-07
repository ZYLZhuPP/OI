#include<bits/stdc++.h>
using namespace std;

const int N=15;

int n,x[N],y[N],ans;

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

void dfs(int sta, int a, int b, int to){
    for(int i=0; i<n; i++) if(!(sta & (1<<i))){
        if((to==0 && a==x[i] && b<y[i]) || (to==1 && a==x[i] && b>y[i])
        || (to==2 && b==y[i] && a>x[i]) || (to==3 && b==y[i] && a<x[i])){
            if(sta+(1<<i)==(1<<n)-1){
                if(i==n-1) ans++;
                return;
            }
            for(int ne=0; ne<4; ne++) if(ne^to){
                dfs(sta|(1<<i), x[i], y[i], ne);
            }
        }
    }
}

int main(){
    read(n);
    for(int i=0; i<n; i++){
        read(x[i]); read(y[i]);
    }
    n++;
    for(int i=0; i<4; i++) dfs(0, 0, 0, i);
    printf("%d", ans);
    return 0;
}
