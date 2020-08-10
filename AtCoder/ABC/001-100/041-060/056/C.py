x = int(input())

ok = x
ng = -1
while ok - ng > 1:
    mid = (ok + ng) // 2
    if mid * (mid + 1) // 2 >= x:
        ok = mid
    else:
        ng = mid

print(ok)