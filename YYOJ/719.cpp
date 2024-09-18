#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int N=2e6+5;
const ull Mo=1e6+9;

ull A,B,C,val[N],x,y;
int head[Mo],nxt[N],hashsiz,t;

void insert(ull x){
    ull u=x%Mo;
    nxt[++hashsiz]=head[u];
    val[hashsiz]=x;
    head[u]=hashsiz;
}

bool find(ull x){
    ull u=x%Mo;
    ull v;
    for(int i=head[u]; i, v=val[i]; i=nxt[i])if(v==x) return 1;
    return 0;
}

int main(){
    cin>>A>>B>>C;
    x=1;
    insert(1);
    while((++t)<=2e6){
        swap(x, y);
        x=(A*y+y%B)%C;
        if(find(x)){
            printf("%d", t);
            return 0;
        }
        insert(x);
    }
    printf("-1");
    return 0;
}
