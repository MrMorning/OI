import re
foo = re.compile(r"\D+(\d+$)")
import urllib.request
nothing = "12345"
dat = ""
while True:
    try:
        fin = urllib.request.urlopen("http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing={0}".format(nothing))
        dat = fin.read().decode()
        fin.close()
        print(dat)
        nothing = foo.search(dat).group(1)
    except Exception as e:
        if "html" in dat:
            break
        print(e)
        print(dat)
        nothing = str(int(nothing)//2)
