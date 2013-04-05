f = open('inp', 'r')
f2 = open('log', 'w')
mp = {}
for s in f.readlines():
	for c in s:
		if c == '\n':
			break
		if c in mp:
			mp[c] += 1
		else:
			mp[c] = 1
ans = '.', 1000000000
for x, y in mp.items():
	f2.write(str((x, y)))
	if y < ans[1]:
		ans = x, y
print(ans)
