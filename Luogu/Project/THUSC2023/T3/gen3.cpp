#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

void dot() { cout << ", "; }
void div() { cout << ";\n"; }

void is(int x, int k = 5, int s1 = 2, int s2 = 40, int E = 1) {
    cout << "AND(" << E; dot();
    For (i, 0, k - 1) {
        if (x >> i & 1) cout << i + s1;
        else cout << i + s2;
        dot();
    }
    cout << x + 7 << ')';
}

void no(int k = 5, int s1 = 2, int s2 = 40) {
    For (i, 0, k - 1) printf("%d=NOT(%d)", i + s2, i + s1), div();
}

int main() {
    no();
    cout << "45=OR(";
    For (i, 0, 8) is(i), dot();
    is(9);
    cout << ')'; div();
    cout << "46=OR(";
    For (i, 10, 18) is(i), dot();
    is(19);
    cout << ')'; div();
    cout << "47=OR(";
    For (i, 20, 28) is(i), dot();
    is(29);
    cout << ')'; div();
    cout << "39=OR(AND(45, 1), AND(46, 1), AND(47, 1), ";
    is(30); dot(); is(31);
    cout << ')'; div();

    return 0;
}
