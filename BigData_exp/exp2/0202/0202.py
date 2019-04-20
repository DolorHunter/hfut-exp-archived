'''
FileName:   0202.py
Auther:     Wang Zixiang
Date:       04.20.2019

Function:   encrypt file
'''

import re


def encrypt(file):
    with open(file) as f:
        words_box = []
        for symbol in f:
            # Delete symbol except a-zA-Z0-9
            symbol = re.sub(r'[^a-zA-Z0-9]', '', symbol)
            words_box.extend(symbol)
        # open the encrypt file
        fw = open('Cy0204.txt', 'w')
        for symbol in words_box:
            # Encrypt symbol
            symbol = chr(ord(symbol)+13)
            fw.write(symbol)
        fw.close()
    return words_box


def main():
    encrypt('NYT.txt')
    print('Encrypt done!!')


if __name__ == "__main__":
    main()