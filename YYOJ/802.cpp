#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;
const int M=1e5+5;

ll n,a[M],s[N];

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

int main(){
    read(n);
    for(int i=1; i<=n; i++){
        read(a[i]);
        s[a[i]]++;
    }
    for(int i=N-1; i>=1; i--)
        for(int j=i+i; j<N; j+=i) s[j]+=s[i];
    for(int i=1; i<=n; i++) printf("%lld\n", s[a[i]]-1);
    return 0;
}
