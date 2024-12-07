#include<bits/stdc++.h>
using namespace std;

const int Mo=32764;

long long n,k;

struct X{
	int v[2][2];
	X(int a, int b, int c, int d){
		v[0][0]=a; v[0][1]=b; v[1][0]=c; v[1][1]=d;
	}
	X operator * (X x){
		X res(0,0,0,0);
		for(int i=0; i<2; i++)
			for(int j=0; j<2; j++)
				for(int k=0; k<2; k++) (res.v[i][j]+=v[i][k]*x.v[k][j])%=Mo;
		return res;
	}
}; 

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
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int main(){
	io>>n;
	while(n--){
		io>>k;
		if(k==1) puts("1");
		else{
			k-=2;
			X a(0,1,1,2), ans(0,1,1,2);
			while(k){
				if(k&1) ans=ans*a;
				a=a*a;
				k>>=1;
			}
			printf("%d\n", (ans.v[0][0]+ans.v[0][1]*2)%Mo);	
		}
	}
}
