#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll a,b,g,x,y;

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
	if(!y){
		a=1, b=0;
		g=x;
		return;
	}
	ll ret;
	ex_gcd(y,x%y,g,ret,a);
	b=ret-(x/y)*a;
}

int main(){
	read(a); read(b);
	ex_gcd(a,b,g,x,y);
	printf("%lld", (x%b+b)%b);
	return 0;
} 
