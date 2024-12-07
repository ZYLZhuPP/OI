#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

#define vec_ll vector<ll>

const int N=14;

ll a,b,p10[N];
vec_ll zero,vec,f[N][10];

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

void add(vec_ll &a, vec_ll &b){
    for(int i=0; i<=9; i++) a[i]+=b[i];
}

vec_ll solve(ll x){
    vec.clear();
    if(!x) return zero;
    while(x) vec.push_back(x%10), x/=10;
    int siz=vec.size();
    vec_ll res=zero;
    for(int i=1; i<vec[siz-1]; i++) add(res, f[siz-1][i]);
    for(int pos=siz-2; pos>=0; pos--)
        for(int i=1; i<=9; i++) add(res, f[pos][i]);
    for(int pos=siz-2; pos>=0; pos--)
        for(int i=0; i<vec[pos]; i++) add(res, f[pos][i]);
    for(int pos=0; pos<siz; pos++){
        res[vec[pos]]+=x;
        x+=vec[pos]*p10[pos];
    }
    return res;
}

void init(){
    p10[0]=1;
    for(int pos=1; pos<N; pos++) p10[pos]=p10[pos-1]*10;
    for(int i=0; i<=9; i++){
        f[0][i]=zero;
        f[0][i][i]+=1;
    }
    for(int pos=1; pos<N; pos++)
        for(int i=0; i<=9; i++){
            f[pos][i]=zero;
            f[pos][i][i]+=p10[pos];
            for(int j=0; j<=9; j++) add(f[pos][i], f[pos-1][j]);
        }
}

int main(){
    for(int i=0; i<=9; i++) zero.push_back(0);
    init();
	read(a); read(b);
	vec_ll ans1=solve(a),ans2=solve(b+1);
	for(int i=0; i<=9; i++) printf("%lld ", ans2[i]-ans1[i]);
	return 0;
}
