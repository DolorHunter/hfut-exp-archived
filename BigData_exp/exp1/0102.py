# coding:utf-8

# 作业:   0102
# 作者:   王子翔
# 日期:   2019.03.30
# 计算输出100~200之间的全部素数

import math

def main():
    print("0102. 计算输出100~200之间的全部素数")
    low = (int)(input("请输入下限:"))
    high = (int)(input("请输入上限:"))
    if low >= high:
        print("范围错误!")
        return -1
    
    for i in range(low, high+1):
        prime = True
        # 从2到i^0.5都不为i的因数, 则i为素数
        for j in range(2, (int)(math.sqrt(i))):
            if (i%j) == 0:
                prime = False
                break
        if (prime):
            print(i, "为素数.", end = "\t")


if __name__ == '__main__':
    main()
