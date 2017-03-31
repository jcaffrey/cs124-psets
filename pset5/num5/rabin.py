import random
# def rabin(n, k):
#     # calc t, u
#     orig_n = n
#     t_ct = 0
#     while (n) % 2 != 0:
#         n = n / 2
#         t_ct += 1
#     t = t_ct
#     u = n
#
#     # find witness
#     for i in range(k):
#         a = 2
#         x = (a ** t) % orig_n
#         if x != 1 or x = n - 1:
#
#
#     # print t, u
#     # print orig_n-1, (2**t)*u
#
# rabin(294409, 1)


# def rabinMiller(n):
#     orig_n = n
#     t_ct = 0
#
#     n = n - 1
#     while n % 2 != 0:
#


def rabinMiller(num, k):
    # Returns True if num is a prime number.

    s = num - 1
    t = 0
    while s % 2 == 0:
        # keep halving s while it is even (and use t
        # to count how many times we halve s)
        s = s / 2
        t += 1
    print t, s
    #
    for trials in range(k): # try to falsify num's primality 5 times
        a = random.randrange(2, num - 1)
        v = pow(a, s, num)
        if v != 1: # this test does not apply if v is 1.
            i = 0
            while v != (num - 1):
                if i == t - 1:
                    print a, v
                    return False
                else:
                    i = i + 1
                    v = (v ** 2) % num
    return True
print rabinMiller(294409, 1)
# print rabinMiller(636127, 25)
