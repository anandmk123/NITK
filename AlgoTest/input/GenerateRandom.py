import random 
f = open("Random100000.txt", "w")
f.write('100000'+'\n')
for i in range(0,100000):
    n=random.randint(100000,200000)
    f.write(str(n)+'\n')