#include<bits/stdc++.h>
using namespace std;

const int N=4e5+5;

char st[N];
int l,p[N];

void write(int k){
	if(!k) return;
	write(p[k-1]);
	printf("%d ", k);
}

int main(){
	while(~scanf("%s", st)){
		memset(p, 0, sizeof(p));
		l=strlen(st);
		int j=0;
		for(int i=1; i<l; i++){
			while(j && st[j]^st[i]) j=p[j-1];
			if(st[j]==st[i]) j++;
			p[i]=j;
		}
		write(l);
		printf("\n");
	}
	return 0;
}
