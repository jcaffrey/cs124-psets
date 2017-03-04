word_ct = 0
p_store = {}  # key: word_ct/index of word, value: penalty of that word, ? - also store line_num?
M = 20


words = []

for line in reversed(open('buffy.txt').readlines()):
    for word in reversed(line.strip().split()):
        words.append(word)
        if word_ct == 0:
            p_store[word_ct] = 0
            word_ct += 1
        # update the penalty cost for that word (act as if 'pulling up' all other possible words)
            #need to know num of words that can fit on next line -->
            #gives spaces, error for that line-->take the min of all cases
        tmp = []
        tmp_words = []
        tmp_word_length = 0
        space_ct = 0
        for k in reversed(range(0, word_ct)):
            space_ct += 1
            tmp_word_length += len(words[k])
            if M - len(word) - tmp_word_length - space_ct >= 0 and word_ct - k - 1 in p_store.keys():  # if word fits on same line
                # print 'got here with word_ct = ' + str(word_ct) + ' and k = ' + str(k)
                tmp.append(M - len(word) - tmp_word_length - space_ct + p_store[word_ct - k - 1]) # don't want len(word) here?
        try:
            print tmp
            p_store[word_ct] = min(tmp)
        except:
            pass
        # print min(tmp)
        # print extra(word_ct, k) for k in range(0, word_ct)
        # p_store[word_ct] = min(extra(word_ct,k) + p_store[word_ct - k] for k in range(0, word_ct))
        # p_store[word_ct] = min(M - len_words - num_words + p_store[word_ct - ])
        print word_ct
        word_ct += 1
print p_store
tot = 0
for k in p_store.keys():
    tot += p_store[k]
print tot
# print words
