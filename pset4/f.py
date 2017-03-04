word_ct = 0
p_store = {}  # key: word_ct/index of word, value: penalty of that word being the start of a line and the num words following it
                    # , ? - also store line_num?
M = 40

words = []
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
                #print 'tmp words of ' + word + ' are ' + str(tmp_words) + ' with space-ct ' +str(space_ct)+ ' at index k ' + str(k) + ' w/ pen: '
                #print M - len(word) - tmp_word_length - space_ct #+ p_store[word_ct - k -1]
                tmp.append(M - len(word) - tmp_word_length - space_ct)
            # tmp.append(M - len(word) - tmp_word_length - space_ct + p_store[word_ct - k])
        # update the penalty cost for that word (act as if 'pulling up' all other possible words) need to know num of words that can fit on next line -->gives spaces, error for that line-->take the min of all cases
        try:
            # idx = 0
            # for i in tmp:
            #     print 'got here!' + str(tmp(idx))
            #     idx += 1

            p_store[word_ct] = (tmp[len(tmp) - 1], word_ct - len(tmp))
        except:
            pass

        # print word_ct
        word_ct += 1

print p_store

start = max(p_store.keys())

next = p_store[start][1]
print start, next
tmp = next
tot_error = 0
try:
    while words[start-1]: # and start-1 != tmp:  #and p_store[start]:
        tot_error += p_store[start][0]

        # print p_store[start][0]
        # tot_error += p_store[start][0]
        while start - next >= 0: # and p_store[start]:
            print words[start - 1],
            start -= 1
        print p_store[start + 1][0],# p_store[start+1][1], start+1,
        print
        next = p_store[next][1]
        # print 'next val is ' +str(next) + ' and start val is ' +str(start)
except:
    print tot_error
