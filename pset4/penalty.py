# with open('buffy.txt') as d:
#     for lines in d:
#         line = lines.rstrip().split()
#         for word in line:
#             print word
#         # print line

for line in reversed(open('buffy.txt').readlines()):
    for word in reversed(line.strip().split()):
        print word
