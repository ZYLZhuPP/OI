#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5, MACH=10;

int T,n,trie[N][MACH],bo[N],triesiz;
char st[100];

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

bool insert(char *s){
	int len=strlen(s);
	int u=0;
	bool ret=0;
	for(int i=0; i<len; i++){
		int ch=s[i]-'0';
		if(!trie[u][ch]) trie[u][ch]=++triesiz;
		else if(i==len-1) ret=1;
		u=trie[u][ch];
		if(bo[u]) ret=1;
	} 
	bo[u]++;
	return ret;
}

int main(){
	while(~scanf("%s", st)){
		T++;
		memset(trie, 0, sizeof(trie));
		memset(bo, 0, sizeof(bo));
		triesiz=0;
		bool ans=0;
		while(st[0]^'9'){
			if(insert(st)) ans=1;
			scanf("%s", st);
		}
		if(!ans) printf("Set %d is immediately decodable\n", T);
		else printf("Set %d is not immediately decodable\n", T);
	}
	return 0;
} 
