#include<bits/stdc++.h>
using namespace std;

const int N=105;

string st;
int f[N][N];

int main(){
	while(cin>>st){
		int len=st.size();
		memset(f, 127, sizeof(f));
		for(int i=0; i<len; i++) f[i][i]=1; 
		for(int i=2; i<=len; i++){
			for(int j=0; i+j-1<len; j++){
				int l=j,r=j+i-1;
				if(st[l]==st[r]){
					f[l][r]=min(f[l+1][r], f[l][r-1]);
				}
				for(int k=l; k<r; k++) f[l][r]=min(f[l][r], f[l][k]+f[k+1][r]);
			}
		}
		printf("%d\n", f[0][len-1]);
	}
	return 0;
} 
