r, c, d = map(int, input().split())
a = [list(map(int, input().split())) for _ in range(r)]

ans = -1
for i in range(r):
    for j in range(c):
        if i + j <= d and (i + j) % 2 == d % 2:
            ans = max(ans, a[i][j])

print(ans)