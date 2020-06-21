n = int(input()) - 1

l = 1
s = 0
while s <= n:
    s += pow(26, l)
    l += 1

l -= 1
s -= pow(26, l)

ans = ['a' for _ in range(l)]

dif = n - s
for i in range(l):
    tmp = pow(26, l - i - 1)
    ans[i] = chr(ord(ans[i]) + dif // tmp)
    dif %= tmp

print(''.join(ans))