#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll Mo=200907;

ll T,x1,x2,x3,k;

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

ll q_pow(ll p, ll a){
    ll res=1;
    while(a){
        if(a&1) (res*=p)%=Mo;
        (p*=p)%=Mo;
        a>>=1;
    }
    return res;
}

int main(){
    read(T);
    while(T--){
        read(x1); read(x2); read(x3); read(k);
        if((x3+x1)^(x2<<1)) printf("%lld\n", (x1*q_pow(x2/x1, k-1))%Mo);
        else printf("%lld\n", (x1+(x2-x1)*(k-1))%Mo);
    }
    return 0;
} 

