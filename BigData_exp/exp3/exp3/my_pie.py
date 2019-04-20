from matplotlib import pyplot as plt
from matplotlib import cm
import numpy as np
import my_count
plt.rcParams['font.sans-serif'] = ['SimHei']  # 解决中文乱码


def school_pie():
    labels = []
    sizes = []
    othersize = 0
    explode = (0.05, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    for (school, times), i in zip(my_count.schooltimes_list, range(999)):
        if i < 100:
            labels.append(school)
            sizes.append(times)
        else:
            othersize += times
    labels.append('其他')
    sizes.append(othersize)
    colors = cm.rainbow(1 - np.arange(len(sizes)) / len(sizes))
    plt.figure(figsize=(35, 25))
    plt.pie(sizes, explode=explode, labels=labels, autopct='%1.1f%%', colors=colors)
    plt.title('2017年双十学子高考录学校分布', fontsize='large', fontweight='bold')
    plt.legend(loc='upper right')
    plt.axis('equal')
    plt.savefig('school_pie.png')
    plt.show()


def schooltypes_pie():
    labels = []
    sizes = []
    explode = (0.05, 0, 0, 0, 0, 0, 0, 0, 0)
    for (schooltypes, times) in my_count.schooltypestimes_list:
        labels.append(schooltypes)
        sizes.append(times)
    colors = cm.rainbow(1 - np.arange(len(sizes)) / len(sizes))
    plt.figure(figsize=(20, 18))
    plt.pie(sizes, explode=explode, labels=labels, autopct='%1.1f%%', colors=colors)
    plt.title('2017年双十学子高考录学校类型分布', fontsize='large', fontweight='bold')
    plt.legend(loc='upper left')
    plt.axis('equal')
    plt.savefig('schooltypes_pie.png')
    plt.show()

def main():
    my_count.count(my_count.schooltimes, my_count.schooltypestimes,
                   my_count.schooltimes_list, my_count.schooltypestimes_list)
    school_pie()
    schooltypes_pie()


if __name__ == '__main__':
    main()
