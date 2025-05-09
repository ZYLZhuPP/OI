#include<bits/stdc++.h>
using namespace std;
extern "C" bool inside_shape(int x, int y);

inline int get_left_point(int x, int y, int p) {
    int l = p, r = y - 1, res = y;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (inside_shape(x, m)) res = m, r = m - 1;
        else l = m + 1;
    }
    return res;
}

inline int get_up_point(int x, int y, int p) {
    int l = p, r = x - 1, res = x;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (inside_shape(m, y)) res = m, r = m - 1;
        else l = m + 1;
    }
    return res;
}

inline int get_right_point(int x, int y, int p) {
    int l = y + 1, r = p, res = y;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (inside_shape(x, m)) res = m, l = m + 1;
        else r = m - 1;
    }
    return res;
}

extern "C" bool am_i_square(int N, int Q) {
    int d = ceil(0.2 * N);
    int x = N + 1, y = N + 1, X = 0, Y = 0;
    for (int i = d; i < N; i += d)
        for (int j = d; j < N; j += d)
            if (inside_shape(i, j)) {
                x = min(x, i);
                y = min(y, j);
                X = max(X, i);
                Y = max(Y, j);
            }
    if (X) {
        int a = get_right_point(X, Y, min(N, Y + d)) - get_left_point(x, y, y - d + 1);
        int b = get_up_point(x, y, x - d + 1) + a;
        return b<=N && (inside_shape(b, Y) && (b == N || !inside_shape(b + 1, Y)));
    }
    if (inside_shape(N, N)) return !inside_shape(N - d, N) && !inside_shape(N, N - d);
    for (int i = d; i < N; i += d) if (inside_shape(i, N)) {
        x = get_up_point(i, N, i - d + 1);
        return !inside_shape(x + d, N);
    }
    for (int j = d; j < N; j += d) if (inside_shape(N, j)) {
        y = get_left_point(N, j, j - d + 1);
        return !inside_shape(N, y + d);
    }
    return false;
}