s = input()
s = s[ : : -1]

n = len(s)
k = 0

flg = True
while k < n:
    if s[k : min(k + 7, n)] == 'remaerd':
        k += 7
    elif s[k : min(k + 6, n)] == 'resare':
        k += 6
    elif s[k : min(k + 5, n)] == 'maerd' or s[k : min(k + 5, n)] == 'esare':
        k += 5
    else:
        flg = False
        break

if flg:
    print('YES')
else:
    print('NO')