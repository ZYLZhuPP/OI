import sys
sys.set_int_max_str_digits(50000)
import math
ans = 0
n, m = map(int, input().split())
def f(x):
    return math.factorial(x)
def A(x, y):
    return f(x) // f(x - y)
if n + 3 >= m:
    ans += A(n + 3, m) * A(n + 2, n + 2)
if n + 2 >= m:
    ans -= 2 * A(n + 2, m) * A(n + 1, n + 1)
print(ans)