#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)

int main() {
    int s1 = 1, s2 = 17, s3 = 34, s4 = 50, s5 = 66, s6 = 82;
    For (i, 0, 15) printf("%d=NXOR(%d, %d);\n", s3 + i, s1 + i, s2 + i);
    puts("65=49;");
    rFor (i, 14, 0) printf("%d=AND(%d, %d);\n", s4 + i, s4 + i + 1, s3 + i);
    For (i, 0, 15) printf("%d=NOT(%d);\n", s5 + i, s1 + i);
    For (i, 0, 15) printf("%d=AND(%d, %d);\n", s6 + i, s2 + i, s5 + i);
    cout << "98=OR(";
    rFor (i, 14, 9) printf("AND(%d, %d), ", s4 + i + 1, s6 + i);
    cout << "AND(59, 90));\n";
    cout << "99=OR(";
    rFor (i, 7, 1) printf("AND(%d, %d), ", s4 + i + 1, s6 + i);
    cout << "AND(51, 82));\n";
    puts("33=OR(98, 99, 97);");

    return 0;
}
