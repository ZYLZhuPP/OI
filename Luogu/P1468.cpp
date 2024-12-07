#include<bits/stdc++.h>
using namespace std;

int sta[8][6]={
	{0,0,0,0,0,0},//1
	{0,0,0,1,1,1},//34
	{1,0,1,0,1,0},//2
	{1,0,1,1,0,1},//4
	{0,1,0,0,1,0},//14
	{0,1,0,1,0,1},//3
	{1,1,1,0,0,0},//24
	{1,1,1,1,1,1},//0
};
int one[4]={0,2,3,5}, two[7]={0,1,2,4,5,6,7};
int n,c,x,on[6];
bool Imp;

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

bool ok(int k){
	for(int i=0; i<6; i++){
		if(on[i]^-1 && on[i]^sta[k][i]) return 0;
	}
	return 1;
}

void write(int k){
	Imp=1;
	for(int i=1; i<=n; i++) printf("%d", sta[k][i%6]);
	puts("");
}

void init(){
	memset(on, -1, sizeof(on));
	Imp=0;
}

int main(){
	read(n); read(c);
	init();
	while(read(x) && x^-1){
		on[x%6]=1;
	}
	while(read(x) && x^-1){
		if(on[x%6]==1) Imp=1;
		on[x%6]=0;
	}
	if(Imp) puts("IMPOSSIBLE");
	else if(c==0){
		if(ok(7)) write(7);
	}else if(c==1){
		for(int i=0; i<4; i++) if(ok(one[i])) write(one[i]);
	}else if(c==2){
		for(int i=0; i<7; i++) if(ok(two[i])) write(two[i]);
	}else{
		for(int i=0; i<8; i++) if(ok(i)) write(i);
	}
	if(!Imp) puts("IMPOSSIBLE");
	return 0;
}
