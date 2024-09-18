#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5, Mo=10007;

struct F{
	int kh,lv;
	bool operator <= (const F x){
		if(kh^x.kh) return kh<=x.kh;
		return lv<=x.lv; 
	}
};

struct D{
	int _0,_1;
};

int n,kh,lv[256];
char a[N];
stack<F > st;
stack<D > data;

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
	inline IO& operator >> (char *x){
		while(c<33) c=gc();
		for(; c>32; c=gc()) (*x++)=c;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

void init(){
	lv['+']=1; lv['*']=2;
}

void popf(){
	int f=st.top().lv; st.pop();
	D d1=data.top(); data.pop(); D d2=data.top(); data.pop();
	D res;
	if(f==1){
		res._0=d1._0*d2._0%Mo;
		res._1=(d1._1*(d2._0+d2._1)+d1._0*d2._1)%Mo;
	}else{
		res._0=(d1._0*(d2._0+d2._1)+d1._1*d2._0)%Mo;
		res._1=d1._1*d2._1%Mo;
	}
	data.push(res);
} 

int main(){
	io>>n>>a+1;
	init();
	data.push({1,1});
	for(int i=1; i<=n; i++){
		if(a[i]=='(') kh++;
		else if(a[i]==')') kh--;
		else{
			F ne={kh, lv[a[i]]};
			while(!st.empty() && ne<=st.top()) popf();
			st.push(ne);
			data.push({1,1});
		}
	}
	while(!st.empty()) popf();
	printf("%d", data.top()._0);
} 
