#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

char a[4];

int main() {
    For (i, 0, 3) a[getchar() - 'A']++;
    if (a[3]) puts("Never give up.");
    else if (a[0] && a[0] + a[1] == 4) puts("I'm so happy.");
    else puts("This is ok.");

    return 0;
}
