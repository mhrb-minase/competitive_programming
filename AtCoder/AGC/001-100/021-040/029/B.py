import bisect

n = int(input())
a = sorted(list(map(int, input().split())))

cnt = {}
for x in a:
    if x in cnt:
        cnt[x] += 1
    else:
        cnt[x] = 1

ans = 0
for i in range(n - 1, -1, -1):
    for d in range(30, -1, -1):
        k = bisect.bisect_left(a, (1 << d) - a[i])
        if k < n and a[i] + a[k] == (1 << d) and (a[i] == a[k] and cnt[a[i]] >= 2 or a[i] != a[k] and cnt[a[i]] >= 1 and cnt[a[k]] >= 1):
            ans += 1
            cnt[a[i]] -= 1
            cnt[a[k]] -= 1

print(ans)