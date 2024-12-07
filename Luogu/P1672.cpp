#include<bits/stdc++.h>
using namespace std;

const int N=2e3+5;

int n,f1,f2,m,l,r,d,cnt[N];

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

int main(){
    read(n); read(f1); read(f2); read(m);
    while(n--){
        read(l); read(r);
        l=min(l, m+1);
        r=min(r, m);
        cnt[r]++; cnt[l-1]--;
    }
    for(int i=m; i>=1; i--){
        d+=cnt[i];
        f2+=d;
        if(f1==f2){
            printf("%d", i);
            return 0;
        }
    }
    return 0;
}
