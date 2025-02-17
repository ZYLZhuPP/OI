#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m;
ll ans;

int main() {
    io >> n >> m;
    if (m == 0) {
        ans = 1ll * n * n;
        printf("%lld\n", ans);
        if (ans <= 2e6) For (i, 1, n) For (j, 1, n) printf("%d %d 0\n", i, j);
    } else if (m == 1) {
        ans = 8 * n - 24;
        printf("%lld\n", ans);
        cout<<1<<' '<<1<<' '<<8<<endl;
        cout<<1<<' '<<n<<' '<<4<<endl;
        cout<<n<<' '<<1<<' '<<2<<endl;
        cout<<n<<' '<<n<<' '<<1<<endl;
        if(n&1^1) {
            cout<<1<<' '<<2<<' '<<4<<endl;
            cout<<2<<' '<<1<<' '<<2<<endl;
            cout<<1<<' '<<n-1<<' '<<8<<endl;
            cout<<2<<' '<<n<<' '<<1<<endl;
            For (i, 1, n / 2 - 2) {
                printf("%d %d %d\n",i+1,n-1-i,8);
                printf("%d %d %d\n",i+2,n-i,1);
                printf("%d %d %d\n",n-i,i,8);
                printf("%d %d %d\n",n-i+1,i+1,1);
                printf("%d %d %d\n",i+2,i,2);
                printf("%d %d %d\n",i+1,i+1,4);
                printf("%d %d %d\n",n-i+1,n-i-1,2);
                printf("%d %d %d\n",n-i,n-i,4);
                
                printf("%d %d %d\n",i+1,n-1-i+1,8);
                printf("%d %d %d\n",i+2,n-i+1,1);
                printf("%d %d %d\n",n-i,i+1,8);
                printf("%d %d %d\n",n-i+1,i+1+1,1);
                printf("%d %d %d\n",i+2,i+1,2);
                printf("%d %d %d\n",i+1,i+1+1,4);
                printf("%d %d %d\n",n-i+1,n-i-1+1,2);
                printf("%d %d %d\n",n-i,n-i+1,4);
            }
        } else {
            For (i, 1, n / 2 - 1) {
                printf("%d %d %d\n",i,i+1,4);
                printf("%d %d %d\n",i+1,i,2);
                printf("%d %d %d\n",i,n-i,8);
                printf("%d %d %d\n",i+1,n-i+1,1);
                printf("%d %d %d\n",n-i,i,8);
                printf("%d %d %d\n",n-i+1,i+1,1);
                printf("%d %d %d\n",n-i,n-i+1,4);
                printf("%d %d %d\n",n-i+1,n-i,2);
                
                printf("%d %d %d\n",i+1,i+1,4);
                printf("%d %d %d\n",i+1+1,i,2);
                printf("%d %d %d\n",i+1,n-i,8);
                printf("%d %d %d\n",i+1+1,n-i+1,1);
                if(i ^ 1) {
                    printf("%d %d %d\n",n-i+1,i,8);
                    printf("%d %d %d\n",n-i+1+1,i+1,1);
                    printf("%d %d %d\n",n-i+1,n-i+1,4);
                    printf("%d %d %d\n",n-i+1+1,n-i,2);
                }
            }
        }
    } else if (m == 2) {
        ans = 4 * n - 4;
        printf("%lld\n", ans);
        For (i, 1, n) printf("1 %d 12\n%d %d 3\n", i, n, i);
        For (i, 2, n - 1) printf("%d 1 10\n%d %d 5\n", i, i, n);
    } else if (m == 3) {
        ans = 2 * n - 1;
        printf("%lld\n", ans);
        For (i, 1, n) printf("1 %d 14\n", i);
        For (i, 2, n) printf("%d %d 7\n", i, n);
    } else if (m == 4) {
        ans = 2 * n - 2;
        printf("%lld\n", ans);
        For (i, 1, n - 1) printf("1 %d 15\n%d %d 15\n", i, n, i);
    }

    return 0;
}
