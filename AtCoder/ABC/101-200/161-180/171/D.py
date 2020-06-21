n = int(input())
a = list(map(int, input().split()))

cnt = [0 for _ in range(101010)]

ans = 0
for x in a:
    cnt[x] += 1
    ans += x

q = int(input())

for _ in range(q):
    b, c = map(int, input().split())
    cnt[c] += cnt[b]
    ans += (c - b) * cnt[b]
    cnt[b] = 0
    print(ans)