'''
FileName:   0201.py
Auther:     Wang Zixiang
Date:       04.20.2019

Function:   word frequency analysis
'''

import collections
import re
from nltk.corpus import stopwords


# Using split to cut the string
def analysis(file):
    with open(file) as f:
        words_box = []
        for line in f: 
            words_box.extend(re.split(r'[;\.\s]', line))
        new_words_box = []
        stop_words = set(stopwords.words('english'))
        for word in words_box:
            # Delete some useless words
            if word not in stop_words and word.isalpha():
                new_words_box.append(word)
    return collections.Counter(new_words_box)


def main():
    print('filename: ', end='  ')
    print('NYT.txt\tCNN.txt\tBBC.txt\tRFI.txt')
    print(analysis('NYT.txt') + analysis('CNN.txt') + analysis('BBC.txt') + analysis('RFI.txt'))


if __name__ == "__main__":
    main()


