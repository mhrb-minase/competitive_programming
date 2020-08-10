n, c = map(int, input().split())
a = list(map(int, input().split()))

for i in range(n):
    a[i] -= 1

ans = [0 for _ in range(c)]
pre = [-1 for _ in range(c)]

for i in range(n):
    ans[a[i]] += (i - pre[a[i]]) * (n - i)
    pre[a[i]] = i

for i in range(c):
    print(ans[i])
