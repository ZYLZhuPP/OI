#include<bits/stdc++.h>
using namespace std;

const int N=1e4+5;
const int TRIESIZ=5e5+5, CHSIZ=2;

int n,m,book[TRIESIZ],trie[TRIESIZ][CHSIZ],down[TRIESIZ],triesiz=1;
int di[N],len;

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

void insert(){
    int u=1;
    for(int i=0; i<len; i++){
        int c=di[i];
        down[u]++;
        if(!trie[u][c]) trie[u][c]=++triesiz;
        u=trie[u][c];
    }
    book[u]++;
}

int find(){
    int u=1, res=0;
    for(int i=0; i<len && u; i++){
        int c=di[i];
        u=trie[u][c];
        res+=book[u];
    }
    res+=down[u];
    return res;
}

int main(){
    read(n); read(m);
    for(int i=1; i<=n; i++){
        read(len);
        for(int j=0; j<len; j++) read(di[j]);
        insert();
    }
    for(int i=1; i<=m; i++){
        read(len);
        for(int j=0; j<len; j++) read(di[j]);
        printf("%d\n", find());
    }
    return 0;
}
