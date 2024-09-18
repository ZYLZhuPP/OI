#include<bits/stdc++.h>
using namespace std;

const int N=1<<23, M=1<<8;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^'-')) f=-1;
		for(x=0; isdigit(c); c=gc()) x=x*10+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int n;
vector<int > vec[N];

int main(){
    io>>n;
    for(int i=1; i<=n; i++){
        int x;
        io>>x;
        vec[x/M].emplace_back(x);
    }
    for(int i=0; i<N; i++){
        sort(vec[i].begin(), vec[i].end());
        for(auto x: vec[i]) printf("%d ", x);
    }
    return 0;
}
