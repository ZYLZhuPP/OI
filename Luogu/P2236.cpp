#include<bits/stdc++.h>
using namespace std;
int m,n,o[13],ans=0;
double a,b;
double anst;
bool mn[51]={0};
void dfs(int x,double sum,int mint){
	if(sum-anst>1e-10) return ;
	if(x==n+1){
		if(fabs(sum-anst)<1e-10) ans++;	
		else return ;	 
	}
	if(sum + 1/double(m)*double(n+1-x) > anst+1e-10) return ;
	if(sum + 1/(double(mint))*double(n+1-x) <anst-1e-10) return ;
	for(int i=mint;i<=m;i++){
		double temp=double(i);
		if((1/temp)-anst>1e-10) continue;
		if(mn[i]==0) {
			mn[i]=1;
			dfs(x+1,sum+double(1.0/temp),i+1);
			mn[i]=0;	
		}
	}
	return ;
}
int main(){
	cin>>n>>m>>a>>b;
	anst=a/b;
	dfs(1,0.0,1);
	cout<<ans;
	return 0;
}
