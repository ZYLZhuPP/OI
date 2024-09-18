#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=7e4+5;
const int M=1e6+5;

ll l,r,last,mi1,mi2,ma1,ma2;
bool pd[M],notpri[N];
ll mipri[N],pri[N],prisiz;

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(; !isdigit(ch); ch=gc())
		if(!(ch^'-')) f=-1;
		else if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc())
		x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
	return 1;
}

void init_pri(ll n){
    for(ll i=2; i<n; i++){
        if(!notpri[i]) pri[++prisiz]=mipri[i]=i;
        for(int j=1; j<=prisiz; j++){
            ll p=pri[j];
            if(p*i>=n || p>mipri[i]) break;
            notpri[i*p]=1;
            mipri[i*p]=mipri[i];
        }
    }
}

void init(){
    init_pri(N);
}

int main(){
    init();
    while(read(l) && read(r)){
        memset(pd, 0, sizeof(pd));
        for(int i=1; i<=prisiz; i++){
            ll p=pri[i];
            for(int j=max((ll)2,(l-1)/p+1); j<=r/p; j++){
                int x=j*p-l;
                pd[x]=1;
            }
        }
        last=-1;
        mi1=mi2=ma1=ma2=-1;
        for(int i=max((ll)2,l); i<=r; i++)if(!pd[i-l]){
            if(~last){
                if(!~mi1 || (i-last)<(mi2-mi1)) mi1=last, mi2=i;
                if(!~ma1 || (i-last)>(ma2-ma1)) ma1=last, ma2=i;
            }
            last=i;
        }
        if(!~mi1) printf("There are no adjacent primes.\n");
        else printf("%lld,%lld are closest, %lld,%lld are most distant.\n", mi1, mi2, ma1, ma2);
    }
    return 0;
}
