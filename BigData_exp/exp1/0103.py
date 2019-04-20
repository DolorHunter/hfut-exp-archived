# coding:utf-8

# 作业:   0103
# 作者:   王子翔
# 日期:   2019.03.30
# 通过for循环和sum函数分别实（写在一个程序中）现求1+2+…+n，其中n通过键盘输入

import turtle as t
import time

def main():
    t.screensize(800, 600, "red")
    t.color("yellow", "blue")
    t.speed(100)
    x = 0
    y = 200
    for i in range(10):
        t.up()
        t.goto(x, y)
        t.down()
        if i %2 ==  1:
            x = x - 200
        else:
            y = y + 200
        t.begin_fill()
        for _ in range(50):
            t.forward(120)
            t.left(170)
        t.end_fill()
        y = y - 200
        

if __name__ == '__main__':
    main()
