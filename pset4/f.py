word_ct = 0
p_store = {}  # key: word_ct/index of word, value: penalty of that word being the start of a line and the num words following it
                    # , ? - also store line_num?
M = 40

words = []
line_br = {} # key: line_num, value: word at end of line
line_ct = 0
br = []

for line in reversed(open('buffy.txt').readlines()):
    for word in reversed(line.strip().split()):
        words.append(word)
        if word_ct == 0:
            p_store[word_ct] = 0
            word_ct += 1

        #find best way to have 'word' start the line. want to store that error and associated num of words on line
        tmp_word_length = 0
        tmp_words = []
        space_ct = 0
        k = len(words)

        for k in reversed(range(0, word_ct)):
            space_ct += 1
            tmp_word_length += len(words[k-1])
            tmp_words.append(words[k-1])
            if M - len(word) - tmp_word_length - space_ct >= 0:
                print 'tmp words of ' + word + ' are ' + str(tmp_words) + ' at index k ' + str(k) + ' w/ pen: '
                print M - len(word) - tmp_word_length - space_ct + p_store[word_ct - k -1]
            # tmp.append(M - len(word) - tmp_word_length - space_ct + p_store[word_ct - k])
        # update the penalty cost for that word (act as if 'pulling up' all other possible words) need to know num of words that can fit on next line -->gives spaces, error for that line-->take the min of all cases

        tmp = []
        tmp_words = []
        tmp_word_length = 0
        space_ct = 0
        for k in reversed(range(1, word_ct + 1)):
            space_ct += 1
            tmp_word_length += len(words[k - 1])
            if M - len(word) - tmp_word_length - space_ct >= 0 and word_ct - k  in p_store.keys():  # if word fits on same line
                # print 'word_ct = ' + str(word_ct) + ' k-1 = ' + str(k-1) + ' tmp_word_length ' + str(tmp_word_length) + ' wordlen ' + str(len(words[k - 1]))
                tmp.append(M - len(word) - tmp_word_length - space_ct + p_store[word_ct - k ]) # don't want len(word) here?
        try:
            # print tmp
            #FIGURE OUT HERE WHAT MIN TELLS US ABOUT # OF WORDS TO PULL UP...
            min_k = 0
            tmp_min = tmp[0]
            print tmp
            for i in tmp:
                print i
            t = min(tmp)
            tmp_new = []
            for ele in tmp:
                if M - ele >= 0:
                    tmp_new.append(M-ele)
            p_store[word_ct] = min(tmp_new)
            print t, tmp_new
        except:
            pass

        print word_ct
        word_ct += 1

    print 'LINE NUM IS ' + str(line_ct)
    line_ct += 1
print p_store
tot = 0
for k in p_store.keys():
    # only add costs of each line...then cube that val
    tot += p_store[k]
print tot
# print words
