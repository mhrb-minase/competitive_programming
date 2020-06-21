def modpow(x, n, p):
    res = 1
    while n > 0:
        if n & 1:
            res = res * x % p
        x = x * x % p
        n >>= 1
    return res

MOD = pow(10, 9) + 7

k = int(input())
s = input()

n = len(s)

fact = [1 for _ in range(n + k + 1)]
p25 = [1 for _ in range(n + k + 1)]
for i in range(1, n + k + 1):
    fact[i] = fact[i - 1] * i % MOD
    p25[i] = p25[i - 1] * 25 % MOD

inv = [1 for _ in range(n + k + 1)]
inv[n + k] = modpow(fact[n + k], MOD - 2, MOD)
for i in range(n + k - 1, -1, -1):
    inv[i] = inv[i + 1] * (i + 1) % MOD

ans = modpow(26, n + k, MOD)
for i in range(n):
    ans -= fact[n + k] * inv[i] % MOD * inv[n + k - i] % MOD * p25[n + k - i] % MOD
    if ans < 0:
        ans += MOD

print(ans)