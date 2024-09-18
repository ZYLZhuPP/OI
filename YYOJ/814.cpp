#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=25;
const ll Mo=9901;

ll a,b,ans;
ll pri[N],prisiz,cnt[N];

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

void init_pri(ll n){
    for(int i=2; i<=sqrt(n)+1; i++){
        if(n%i==0) pri[++prisiz]=i;
        while(n%i==0) cnt[prisiz]++, n/=i;
    }
    if(n^1) pri[++prisiz]=n, cnt[prisiz]=1;
}

void init(){
    ans=1;
    init_pri(a);
}

ll q_pow(ll a, ll b){
    ll res=1;
    while(b){
        if(b&1) (res*=a)%=Mo;
        (a*=a)%=Mo;
        b>>=1;
    }
    return res;
}

ll inverse(ll x){
    return q_pow(x, Mo-2);
}

int main(){
    read(a); read(b);
    init();
    for(int i=1; i<=prisiz; i++){
        ll p=pri[i], c=cnt[i]*b;
        if((p-1)%Mo==0){
            ll ne=c+1;
            (ans*=ne)%=Mo;
        }else{
            ll ne=q_pow(p, c+1)-1+Mo;
            (ne*=inverse(p-1))%=Mo;
            (ans*=ne)%=Mo;
        }
    }
    printf("%lld", ans);
    return 0;
}
