#include<bits/stdc++.h>
using namespace std;

const int N=3e4+5;
const int Mo1=1e6+3, Mo2=1e6+9, P1=47, P2=79;

int t,T,s1,s2,l;
int head[Mo1+5],nxt[N],val[N];
char k[10], st[300];

void insert(int x, int y){
    nxt[++t]=head[x];
    val[t]=y;
    head[x]=t;
}

bool query(int x, int y){
    for(int i=head[x]; i; i=nxt[i]){
        if(val[i]==y) return 1;
    }
    return 0;
}

int main(){
    cin>>T;
    while(T--){
        s1=s2=0;
        scanf("%s", k);
        fgets(st, sizeof st, stdin);
        l=strlen(st);
        for(int i=0; i<l; i++){
            ((s1*=P1)+=st[i])%=Mo1;
            ((s2*=P2)+=st[i])%=Mo2;
        }
        if(k[0]=='a') insert(s1, s2);
        else{
            if(query(s1, s2)) printf("yes\n");
            else printf("no\n");
        }
    }
    return 0;
} 
