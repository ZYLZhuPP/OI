#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;

int la,lb,j,p[N],ans;
string a,b;

int main(){
    cin>>a>>b;
    la=a.size(); lb=b.size();
    a=' '+a; b=' '+b;
    p[1]=j=0;
    for(int i=1; i<lb; i++){
        while(j && b[i+1]^b[j+1]) j=p[j];
        if(b[i+1]==b[j+1]) j++;
        p[i+1]=j;
    }
    j=0;
    for(int i=0; i<la; i++){
        while(j && a[i+1]^b[j+1]) j=p[j];
        if(a[i+1]==b[j+1]) j++;
        if(j==lb){
            ans++;
            j=p[j];
        }
    }
    printf("%d", ans);
    return 0;
}
