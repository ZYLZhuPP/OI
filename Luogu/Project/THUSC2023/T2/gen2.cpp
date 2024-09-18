#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

int main() {
    For (i, 1, 5) printf("%d=NOT(%d);\n", i + 38, i + 1);
    For (i, 0, 31) printf("%d=AND(1, %d, %d, %d, %d, %d);\n", i + 7, 2 + (~i&1)*37, 3 + (~i>>1&1)*37, 4 + (~i>>2&1)*37, 5 + (~i>>3&1)*37, 6 + (~i>>4&1)*37);

    return 0;
}
