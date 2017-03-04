word_ct = 0
p_store = {}  # key: word_ct/index of word, value: penalty of that word being the start of a line and the num words following it
                    # , ? - also store line_num?
M = 40

words = []
line_br = {} # key: line_num, value: word at end of line
br = []

for line in reversed(open('buffy.txt').readlines()):
    for word in reversed(line.strip().split()):
        words.append(word)
        if word_ct == 0:
            p_store[word_ct] = (0, 1)
            word_ct += 1

        #find best way to have 'word' start the line. want to store that error and associated num of words on line
        tmp_word_length = 0
        tmp_words = []
        space_ct = 0
        k = len(words)
        tmp = []
        for k in reversed(range(0, word_ct)):
            space_ct += 1
            tmp_word_length += len(words[k-1])
            tmp_words.append(words[k-1])
            if M - len(word) - tmp_word_length - space_ct >= 0:
                print 'tmp words of ' + word + ' are ' + str(tmp_words) + ' with space-ct ' +str(space_ct)+ ' at index k ' + str(k) + ' w/ pen: '
                print M - len(word) - tmp_word_length - space_ct #+ p_store[word_ct - k -1]
                tmp.append(M - len(word) - tmp_word_length - space_ct)
            # tmp.append(M - len(word) - tmp_word_length - space_ct + p_store[word_ct - k])
        # update the penalty cost for that word (act as if 'pulling up' all other possible words) need to know num of words that can fit on next line -->gives spaces, error for that line-->take the min of all cases
        try:
            # print tmp
            #FIGURE OUT HERE WHAT MIN TELLS US ABOUT # OF WORDS TO PULL UP...
            # num_words = 0
            # for i in tmp:
            #     num_words += 1
            print 'best num words is ' +str(len(tmp)) + ' and best error is ' + str(tmp[len(tmp)-1])
            p_store[word_ct] = (tmp[len(tmp) - 1], word_ct - len(tmp))
            # min_k = 0
            # tmp_min = tmp[0]
            # print tmp
            # for i in tmp:
            #     print i
            # t = min(tmp)
            # tmp_new = []
            # for ele in tmp:
            #     if M - ele >= 0:
            #         tmp_new.append(M-ele)
            # p_store[word_ct] = min(tmp_new)
            # print t, tmp_new
        except:
            pass

        # print word_ct
        word_ct += 1

print p_store
tot = 0
start = max(p_store.keys())

next = p_store[start][1]
for line in range(15):
    while start - next >= 0:
        print words[start - 1],
        start -= 1
    next = p_store[next][1]
    print


# while start >0:
#     print words[start -1]
#     print p_store[start]
#     start -= p_store[start][1]


#
# for k in reversed(p_store.keys()):
#     print 'line k is ' +str(k) + ' error of line k is ' +str(p_store[k][0]) +' num words '  + str(p_store[k][1])
#     print 'updating k by num words ' + str(p_store[k][1])
#     k += p_store[k][1]
print max(p_store.keys())
#reversed(p_store.keys()):
#     # only ad
# for k in d costs of each line...then cube that val
#     print k
#     print 'best num words is ' + str(len(tmp)) + ' and best error is ' + str(tmp[len(tmp) - 1])
#
#     tot += p_store[k][0]
# print tot
# print words
