import re
fin = open('inp', 'r')
print((re.findall('[^A-Z][A-Z]{3}([a-z])[A-Z]{3}[^A-Z]', fin.read())))
