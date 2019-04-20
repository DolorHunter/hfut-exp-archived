# coding:utf-8

# 作业:   0101
# 作者:   王子翔
# 日期:   2019.03.30
# 通过for循环和sum函数分别实（写在一个程序中）现求1+2+…+n，其中n通过键盘输入

import math


def main():
    print("0101. 通过for循环和sum函数分别实（写在一个程序中）现求1+2+…+n，其中n通过键盘输入")
    n = int(input("请输入数字:"))
    print("sum求和结果为:", math.fsum(range(1, n+1)))
    _sum = 0
    for i in range (n+1):
        _sum = _sum + i
    print("for求和结果为:", _sum)


if __name__ == '__main__':
    main()
