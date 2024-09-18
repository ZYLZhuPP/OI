#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;

ll T,n,k,x,y,fa[N];

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
    for(int i=1; i<=n; i++) fa[i]=i;
}

int find(int k){
    if(fa[k]^k) return fa[k]=find(fa[k]);
    return k;
}

int main(){
    read(T);
    while(T--){
        read(n); read(k); read(x); read(y);
        init();
        for(int i=k+1; i<=n; i++)
            for(int j=i; j<=n; j+=i){
                int fi=find(i), fj=find(j);
                fa[fi]=fj;
            }
        int fx=find(x), fy=find(y);
        if(fx==fy)printf("Possible\n");
        else printf("Impossible\n");
    }
    return 0;
}

