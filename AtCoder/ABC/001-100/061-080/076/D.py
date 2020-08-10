n = int(input())
t = list(map(float, input().split()))
v = list(map(float, input().split()))

for i in range(n):
    t[i] *= 2.0
    v[i] *= 2.0

v.append(0.0)

for i in range(n - 1, -1, -1):
    v[i] = min(v[i], v[i + 1] + t[i])

for i in range(1, n):
    t[i] += t[i - 1]

ans = 0.0
speed = 0.0
k = 0
st = int(t[n - 1] + 0.1)

for i in range(st):
    if i >= t[k]:
        k += 1
    
    ans += speed

    limit = min(v[k], v[k + 1] + t[k] - i - 1)
    if speed < limit:
        ans += 0.5
        speed += 1.0
    elif speed > limit:
        ans -= 0.5
        speed -= 1.0

ans /= 4.0

print(ans)