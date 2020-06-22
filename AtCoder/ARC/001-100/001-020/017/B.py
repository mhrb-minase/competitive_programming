n, k = map(int, input().split())
a = [int(input()) for _ in range(n)]
a.append(-1)

ans = 0
cnt = 1
for i in range(n):
    if a[i] < a[i + 1]:
        cnt += 1
    else:
        ans += max(cnt - k + 1, 0)
        cnt = 1

print(ans)