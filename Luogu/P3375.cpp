#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

int la, lb, p[N];
char a[N], b[N];

int main() {
    scanf("%s", a + 1); la = strlen(a + 1);
    scanf("%s", b + 1); lb = strlen(b + 1);
    p[1] = 0;
    int j = 0;
    For (i, 2, lb) {
        while (j && b[i] ^ b[j + 1]) j = p[j];
        if (b[i] == b[j + 1]) j++;
        p[i] = j;
    }
    j = 0;
    For (i, 1, la) {
        while (j && a[i] ^ b[j + 1]) j = p[j];
        if (a[i] == b[j + 1]) j++;
        if (j == lb) printf("%d\n", i - lb + 1), j = p[j];
    }
    For (i, 1, lb) printf("%d ", p[i]);

    return 0;
}
