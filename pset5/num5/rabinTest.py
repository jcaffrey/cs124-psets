import random

def rabin(num, k):

    for i in range(k):
        a = random.randrange(2, num - 1)
        #find t_ct (s here), u (d here)
        d = num - 1
        t_ct = 0
        while d % 2 == 0:
            d = d / 2
            t_ct = t_ct + 1
        t = modExp(a, d, num)
        if t == 1:
            return True
        while s > 0:
            if t == num - 1:
                return True
            t = (t * t) % num
            s = s - 1
        print a
    return False

def modExp(b, e, m):
    x = 1
    while e > 0:
        if e % 2 != 0:
            x = (b * x) % m
        b = (b * b) % m
        e = e / 2
    return x

# print rabin(294409,25)

######-------- vvvvvv PART 6 vvvvvv ----------###########
m = "Give me an A"
m = int(''.join(format(ord(ch), '08b') for ch in m),2)
print
print

N = 46947848749720430529628739081
E = 37267486263679235062064536973

print str(modExp(m, E, N))
#27016764340118192395712492378
