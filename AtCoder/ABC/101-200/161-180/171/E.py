n = int(input())
a = list(map(int, input().split()))

val = 0
for x in a:
    val ^= x

for i in range(n):
    if(i < n - 1):
        print(val ^ a[i], end=' ')
    else:
        print(val ^ a[i])