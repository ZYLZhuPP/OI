#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)

void program_pulibot();
void set_instruction(vector<int > S, int Z, char A);

const char mp[6] = {'H', 'T', 'W', 'S', 'E', 'N'};

void program_pulibot() {
    For (I, 0, 5) For (L, -2, 5) For (D, -2, 5) For (R, -2, 5) For (U, -2, 5) {
        vector<int > S = {I, L, D, R, U};
        if (!I) {
            if (L == -2 && U == -2) ~R? set_instruction(S, 4, 'E'): set_instruction(S, 3, 'S');
            else if (R == -2 && D == -2) set_instruction(S, 4, 'H');
            else For (i, 2, 5) if (S[i - 1] == i % 4 + 2) { set_instruction(S, i, mp[i]); break; }
        } else {
            if (S[I - 1] == I % 4 + 2) {
                int p = (I - 1) % 4 + 2, flag = 0;
                while (p ^ I && !flag) {
                    if (!S[p - 1] || S[p - 1] == p % 4 + 2) set_instruction(S, p, mp[p]), flag = 1;
                    p = (p - 1) % 4 + 2;
                }
                if (!flag) set_instruction(S, I, mp[I]);
            } else {
                int co = L == -2 && U == -2, flag = 0;
                For (p, 2, 5) if (!flag) {
                    if (S[p - 1] == p % 4 + 2) set_instruction(S, I, mp[p]), flag = 1;
                    co |= S[p - 1] == 1;
                }
                if (flag) continue;
                if (R == -2 && D == -2) set_instruction(S, 1, 'T');
                else set_instruction(S, co, mp[I]);
            }
        }
    }
}
