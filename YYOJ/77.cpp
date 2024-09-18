#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;

int n,a[N],b[N];
long long ans;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^'-')) f=-1;
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline IO& operator >> (char &x){
		while(c<33) c=gc(); x=c;
		return *this;
	}
	inline bool operator ~ (){return (f? c: c=gc())^EOF;}
}io; 

void msort(int l, int r){
	if(l==r) return;
	int mid=(l+r)>>1, i=l, j=mid+1, k=l;
	msort(l, mid); msort(mid+1, r);
	while(i<=mid && j<=r){
		if(a[i]<=a[j]) b[k++]=a[i++];
		else b[k++]=a[j++], ans+=mid-i+1;
	}
	while(i<=mid) b[k++]=a[i++];
	while(j<=r) b[k++]=a[j++];
	for(int o=l; o<=r; o++) a[o]=b[o];
} 

int main(){
	io>>n;
	for(int i=1; i<=n; i++) io>>a[i];
	msort(1, n);
	printf("%lld", ans);
	return 0;
} 
