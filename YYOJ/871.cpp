#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll Mo = 1e9 + 7;
const int N = 305;

ll len, f[N][N];
string st;

int main(){
    cin>>st;
    len = st.length();
    
    for (int i = 0; i < len; i++) 
        f[i][i]=1;
        
    for (int i = 2; i <= len; i++) {
        for(int j = 0; i + j - 1 < len; j++) {
            int l = j, r = i + j - 1;
            if (st[l] ^ st[r]) {
                f[l][r] = 0;
                continue;
            }
            f[l][r] = f[l+1][r-1];
            for (int k = l + 1; k <= r - 1; k++) 
                if (st[k] == st[l]) (f[l][r]+=(f[l][k]*f[k+1][r-1])%Mo)%=Mo;
        }
    }
    
    printf("%lld", f[0][len-1]);
    return 0;
}
