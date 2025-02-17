#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll Mo=1e5+3;

ll n,m;

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

ll q_pow(ll p, ll x){
    ll res=1;
    while(x){
        if(x&1) (res*=p)%=Mo;
        (p*=p)%=Mo;
        x>>=1;
    }
    return res;
}

int main(){
    read(m); read(n);
    printf("%lld", (q_pow(m,n)-(q_pow(m-1,n-1)*(m%Mo)%Mo)+Mo)%Mo);
    return 0;
}
