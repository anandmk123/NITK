import random 
f = open("Randominputfile.txt", "w")
f.write('200000'+'\n')
for i in range(0,200000):
    n=random.randint(100000,300000)
    f.write(str(n)+'\n')
