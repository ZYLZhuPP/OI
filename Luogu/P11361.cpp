#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int T, n, ans, ca[2], cb[2];
char a[N], b[N], A[N], B[N];

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n;
        scanf("%s", a + 1);
        scanf("%s", b + 1);
        scanf("%s", A + 1);
        scanf("%s", B + 1);
        For (i, 1, n) {
            if (!ca[0] && !ca[1]) {
                ca[a[i] & 1]++;
                if (A[i] & 1) {
                    int x = i + 1;
                    while (x <= n && A[x] == '1') ca[a[x++] & 1]++;
                }
            }
            if (!cb[0] && !cb[1]) {
                cb[b[i] & 1]++;
                if (B[i] & 1) {
                    int x = i + 1;
                    while (x <= n && B[x] == '1') cb[b[x++] & 1]++;
                }
            }
            if (ca[0] && cb[0]) ca[0]--, cb[0]--, ans++;
            else if (ca[1] && cb[1]) ca[1]--, cb[1]--, ans++;
            else {
                if (ca[0]) ca[0]--, cb[1]--;
                else ca[1]--, cb[0]--;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
