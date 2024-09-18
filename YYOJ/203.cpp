#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n,m,k,x,ans;

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
		if(a&1) (res*=p)%=n;
		(p*=p)%=n;
		a>>=1;
	}
	return res;
}

int main(){
	read(n); read(m); read(k); read(x);
	ans=(x+(q_pow(10, k)*m))%n;
	printf("%lld", ans);
	return 0;
} 
