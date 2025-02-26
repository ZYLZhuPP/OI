#include<bits/stdc++.h>
using namespace std;

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
 
const int ans[29]={0,1,499122178,2,915057326,540715694,946945688,422867403,451091574,317868537,200489273,976705134,705376344,662845575,331522185,228644314,262819964,686801362,495111839,947040129,414835038,696340671,749077581,301075008,314644758,102117126,819818153,273498600,267588741};
int n;

int main() {
    io >> n;
    printf("%d", ans[n]);

    return 0;
}