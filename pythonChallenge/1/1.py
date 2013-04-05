haha = input().split(' ')
for x in haha:
	for y in x:
		if ('a' <= y) and (y <= 'z'):
			print(chr((ord(y)-ord('a')+2)%26+ord('a')))
		else:
			print (y)
	print
