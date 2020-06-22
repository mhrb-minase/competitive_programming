from collections import deque

n = int(input())
d = list(map(int, input().split()))
d.append(0)
d.sort()

deq = deque()

for i in range(n + 1):
    if i & 1:
        deq.append(d[i])
    else:
        deq.appendleft(-d[i])

ans = abs(deq[0] + 24 - deq[n])
for i in range(n):
    ans = min(ans, deq[i + 1] - deq[i])

print(ans)