
COST = {}

BUFF_CT = 176

# can we memoize this?
p_store = {} # holds line num as key and (word, word_ct) tuple as value


def p(word, i, line, M):
    # fill first line - base case
    #loop through each word that can be pulled up
    print 'in p'
    try:
        num_on_line = len(p_store[line] / 2)
        words_on_line = []
        count = 0
        for ele in p_store[line]:
            if count % 2 == 0:
                print ele
                words_on_line.append(ele)
        # p_store[line]
    except:
        print 'key error?'
    if line == 0 and M - num_on_line - len(words_on_line) > len(word):
        p_store[line] += (word, i)
        print 'got here'

        # last line (first line in iteration)
    return p_store
    # k = 0
    # while M - cost(i,j) + p_store[]
    # return min(cost(i,j) + p[j] for j in range(i+1, BUFF_CT+1))

word_ct = 0
tot_penalty = 0
line_num = 0

for line in reversed(open('buffy.txt').readlines()):
    word_ind = 0
    hmm = {}
    for word in reversed(line.strip().split()):
        # p_store[word_ct] = p[word, word_ct, line_num, 40]

# breaking modularity
        if word_ct == 0:
            p_store[line_num] = (word, word_ct)

        try:
            num_on_line = len(p_store[line_num]) / 2
            words_on_line = []
            count = 0
        for ele in p_store[line_num]:
            if count % 2 == 0:
                print ele
                words_on_line.append(ele)
            # p_store[line]
        except:
            print 'key error?'
        if line == 0 and M - num_on_line - len(words_on_line) > len(word):
            p_store[line_num] += (word, i)
            print 'got here'





# breaking modularity


        # p[word, word_ct, line_num, 40]  'function' object has no attribute '__getitem__'
        word_ct += 1
        word_ind += 1
        # p(word, word_ct, 40)
    line_num += 1
print 'words on last line' + str(p_store)

#  print p_store if all goes well
