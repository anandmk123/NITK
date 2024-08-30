import random 
f = open("Randominputfile.txt", "w")
f.write('20000'+'\n')
for i in range(0,20000):
    n=random.randint(100000,200000)
    f.write(str(n)+'\n')
