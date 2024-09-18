#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;

ll T,L,x,m,d,bkt[N],a,b;
bool ans;

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
    memset(bkt, 0, sizeof(bkt));
    ans=1;
}

void add(ll l, ll r){
    if(r<x){
        bkt[l]++; bkt[r+1]--;
    }else{
        bkt[l]++; bkt[x]--;
        bkt[0]++; bkt[r-x+1]--;
    }
}

int main(){
    read(T);
    while(T--){
        init();
        read(L); read(m); read(x); read(d);
        ll ma=x-d;
        for(int i=1; i<=m; i++){
            read(a); read(b);
            if(b-a>ma) ans=0;
            ll l=(b+d)%x;
            ll r=a%x;
            r+=(r<l)*x;
            add(l,r);
        }
        ll sum=0;
        bool pd=0;
        for(int i=0; i<x; i++){
            sum+=bkt[i]; if(sum==m) pd=1;
        }
        ans&=pd;
        if(ans) printf("Yes\n"); else printf("No\n");
    }
    return 0;
}
