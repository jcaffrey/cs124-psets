import math

N = 10**5
M = 10**6
B = [3, 4, 5]

k = math.ceil((M/N)*math.log(2, math.e))

def ncr(n, r):
    return math.factorial(n) / math.factorial(r) / math.factorial(n - r)

for b in B:
    sum = 0
    for i in range(1,2**b):
        tmp = 0
        tmp = ncr(N, i) * (k/M)**i * (1-(k/M))**(N-i)
        sum += 1 - tmp
    print 'b: ' + str(b) + ' sum: ' + str(sum)
