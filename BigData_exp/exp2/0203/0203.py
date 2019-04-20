'''
FileName:   0203.py
Auther:     Wang Zixiang
Date:       04.20.2019

Function:   draw a func
'''

import matplotlib.pyplot as plt
import numpy as np


def draw():
    x = np.linspace(-5, 5, 1000)
    y = [np.arcsin(i)/np.tan(x) for i in x]
    plt.plot(x, y)
    plt.show()


def main():
    draw()


if __name__ == "__main__":
    main()