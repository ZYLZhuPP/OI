#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=15;

ll n,a[N],b[N],Mu=1,ans;

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

void ex_gcd(ll x, ll y, ll &g, ll &a, ll &b){
    if(!y){g=x; a=1; b=0; return;}
    ex_gcd(y, x%y, g, b, a);
    b-=x/y*a;
}

ll inverse(ll x, ll Mo){
    ll g,a,b;
    ex_gcd(x,Mo,g,a,b);
    return (a%Mo+Mo)%Mo;
}

int main(){
    read(n);
    for(int i=1; i<=n; i++){
        read(a[i]); read(b[i]);
        Mu*=a[i];
    }
    for(int i=1; i<=n; i++){
        ll m=Mu/a[i];
        (ans+=b[i]*m*inverse(m, a[i]))%=Mu;
    }
    printf("%lld", ans);
    return 0;
}
