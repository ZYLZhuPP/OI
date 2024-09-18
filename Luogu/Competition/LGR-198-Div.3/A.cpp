#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105;

int n;
char s[N];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    putchar('/');
    For (i, 1, n) if (s[i] >= 'A' && s[i] <= 'Z') putchar(s[i] - 'A' + 'a'); else if (s[i] == ']') break; 

    return 0;
}
