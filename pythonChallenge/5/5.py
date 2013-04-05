import pickle
f = open("banner.p", "rb")
tmp = pickle.load(f)
for line in tmp:
    print("".join([x[0] * x[1] for x in line]))
f.close()
