#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int N=2e6+5;
const ull P=31;

int l;
ull p[N],f[N];
char st[N];
string ansst;
ull ans,ansp;

void init(){
	p[0]=1;
	for(int i=1; i<=N; i++) p[i]=p[i-1]*P;
}

ull getf(int l, int r){
    if(l>r) return 0;
    l--;
    return f[r]-f[l]*p[r-l];
}

string getst(int k){
	string res="";
    int x=l/2;
    x+=k<=(l/2);
	for(int i=1; i<=x; i++)if(i^k) res+=st[i];
	return res;
}

void ok(int k){
    int mid=l/2+1;
    ull p1=getf(1,mid-1),p2=getf(mid+1,l);
    if(k<mid) p1=f[k-1]*p[mid-k]+getf(k+1,mid);
    if(k>mid) p2=getf(mid,k-1)*p[l-k]+getf(k+1,l);
    if((p1==p2) && (p1^ansp || !ans)){
        ansp=p1;
        ans++;
        ansst=getst(k);
    }
}

int main(){
	init();
	cin>>l;
	scanf("%s", st+1);
    if(!(l%2)){
        printf("NOT POSSIBLE");
        return 0;
    }
	for(int i=1; i<=l; i++) f[i]=f[i-1]*P+st[i];
	for(int i=1; i<=l && ans<2; i++) ok(i);
	if(!ans) printf("NOT POSSIBLE");
	else if(ans>1) printf("NOT UNIQUE");
	else cout<<ansst;
	return 0;
} 
