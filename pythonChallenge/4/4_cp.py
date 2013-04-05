import re
foo = re.compile(r"\D+(\d+$)")
import urllib.request
nothing = "16044"
dat = ""
while True:
    try:
        fin = urllib.request.urlopen("http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing={0}".format(nothing))
        dat = fin.read()
        fin.close()
        print(dat)
        nothing = foo.search(dat.decode()).group(1)
    except Exception as e:
        print(e)
        print(dat)
        dat = ((int)dat)//2
        break
