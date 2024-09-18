#include<bits/stdc++.h>
using namespace std;

#define P printf
#define For(i, l, r) for (int i = (l); i <= (r); ++i)

void dot() { P(", "); }
void div() { puts(";"); }
int tot;
void ne(int &x) { x = ++tot; P("%d=", x); }

int main() {
    tot = 48;
    int s1 = 1, s2 = 17, s3 = 33;
    int ls[4] = { 0, 4, 8, 12 }, rs[4] = { 3, 7, 11, 15 };
    int o[16], a[16], p[16], g[16], d[16];
    For (i, 0, 15) {
        int b = i / 4, l = ls[b];
        ne(o[i]); P("OR(%d, %d)", s1 + i, s2 + i); div();//T1
        ne(a[i]); P("AND(%d, %d)", s1 + i, s2 + i); div();//T1
        ne(g[i]);
            P("OR(");
                For (j, l, i - 1) {
                    P("AND(");
                        For (k, j + 1, i) P("%d", o[k]), dot();
                        P("%d", a[j]);
                    P(")"); dot();
                }
                P("AND(%d)", a[i]);
            P(")"); div();//T2
        ne(p[i]);
            P("AND(");
                For (j, l, i - 1) P("%d", o[j]), dot();
                P("%d", o[i]);
            P(")"); div();//T2
        ne(d[i]);
            P("OR(");
                For (j, 0, b - 1) {
                    P("AND(");
                        P("%d", g[rs[j]]); dot();
                        For (k, j + 1, b - 1) P("%d", p[rs[k]]), dot();
                        P("%d", p[i]);
                    P(")"); dot();
                }
                P("AND(%d)", g[i]);
            P(")"); div();//T3
        P("%d=XOR(%d, %d, %d)", s3 + i, s1 + i, s2 + i, i? d[i - 1]: 0); div();//T4
    }

    return 0;
}
