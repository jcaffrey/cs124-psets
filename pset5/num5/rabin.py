def rabin(n, k):
    # calc t, u
    orig_n = n
    t_ct = 0
    while n % 2 != 0:
        n = n / 2
        t_ct += 1
    t = t_ct
    u = n
    print t, u
    print orig_n-1, (2**t)*u
    #for i in range(k):

rabin(294409, 1)
