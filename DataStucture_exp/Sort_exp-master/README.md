# Sort_exp

Datastucture exp-10 Sort(排序)(快速排序|希尔排序|堆排序|二路归并排序)

#### 2018.12.31修改记录: 修正了希尔排序的增量错误.
#### 2018.12.24首次上传

数据结构 exp-10 第十次实验作业 排序实验 /**************************************** 版本说明: @exp-10为作业版本, 为小程序 (如有需要借鉴代码请使用此版本!!!) ****************************************/


参考资料: 
          
          希尔排序(缩小增量排序)Shell http://data.biancheng.net/view/69.html

          归并排序 http://data.biancheng.net/view/73.html
          
          快速排序算法（QSort，快排) http://data.biancheng.net/view/71.html
          

10.1.实验目的
(1) 掌握各种内部排序算法。
(2) 理解各种内部排序算法的特性、时间性能和空间性能，在此基础上能根据具体情况选择合适的排序算法。
(3) *掌握运用实验分析算法的正确性、时间性能和空间性能的方法。    
    排序是软件设计中最常用的运算之一，有多种不同的算法，每种算法各有其特定性和最合适的适用范围。因此，了解这些特性对于实际应用时选择最恰当算法是软件设计中的重要技术。通过本次实验，应注意体会各种实验的性能特点，包括时间性能、空间性能以及其它相关的性能。同时，通过实验的方法来分析算法的各种性能是计算机科学与技术领域重要的手段，是研究各类问题求解的新算法所必需的技术，应引起足够的重视。

10.2.实验任务
算法设计：设计算法实现下列问题的求解，并通过记录和分析过对给定的数据的运行过程中的比较和交换元素次数来分析算法的时间性能。
(1) 采用不同实验数据来观察快速排序的实验中比较和交换元素的次数，并分析数据的规模和初始特性与比较与交换次数之间的函数关系。	
测试数据要求：至少5组以上；每组数据规模不小于100。

(2) 完成下面功能：将一个整型数组调整为这样的数组：所有３的倍数在最左边，所有除以３余１的数在中间，而所有除以３余２的数在最右边。要求算法的时间尽可能少。	
测试数据：数组元素分别为：
第一组数据：
（1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26）
第二组数据：	
（11,12,13,14,15,1,2,3,4,5,6, 10, 16, 1,22,23,2,17,18,19,20,24, 7,8,9,25,26）
第三组数据：	
（5,6,7, 1,2,3,4,8,9,10,11,12,13, 16,17,18, 14, 25,26,15,19,20,21,22,23,24） 

(3) 实现shell排序算法，并观察在采用不同的步长选取方法对排序过程中数据的比较和移动次数的影响。	
测试数据：数组元素分别为：
第一组数据：
（180,203,32,46,25,76,17,58,99,100,11,102,13,54,75,6,27,18,19,29,2,82）
其余数据的规模应不少于第一组数。

(4) 设计算法实现快速排序，要求能用数组或树来演示排序过程，以清晰地表示出排序过程。	
测试数据：
数组元素分别为：
第一组数据：
(106,213,325,446,579,654,721,870,917,510,21,632,73,14,815,316,412,18,619,720,21,808,923,25,26 )

(5)以数组和二叉树形式动态演示堆排序算法的排序过程。	
测试数据：
数组元素分别为：
第一组数据：
（106,213,325,446,579,654,721,870,917,510,21,632,73,14,815,316,412,18,619,720,21,808,923,25,26）

(6)利用二路归并方法进行排序。	
测试数据：
数组元素分别为：    
第一组数据：
( 106,213,325,446,579,654,721,870,917,510,21,632,73,14,815,316,412,18,619,720,21,808,923,25,26  )    
其余数据的规模应不少于第一组数的两倍。

10.3.实验说明
(1) 关于排序算法性能实验的数据要求和实现为了能有效检验排序算法的各种性能（正确性，时间性能、空间性能等），一般要用大量的数据来运行算法，不仅要求数据的规模要有较大的变化范围（如从数十个元素到数千甚至数万个元素的规模），而且还要求数据元素的取值特性有更大的覆盖范围。只有在实验数据方面更充分了，才能有更好的说服力。这事实上也是采用实验方法来验证大多数算法性能是所采用的方法。
由此可知，实验时，需要分别在数组的规模上和数据元素的取值特性方面大量选取。下面分别讨论：
① 对数组的规模的变化可依次取不同规模的数组来实验，例如，对某实验分两种取法：
第一种规模：可以人工检验的规模，如10~100，每次增长10，便于人工方式检查和比较。		
第二种方式：程序方式检验，如100，1000，2000，3000，5000，10000等。
② 数组元素的取值	对元素值的取值一般采用随机产生的方法更易于得到更多特性的数据。关于随机产生数据的方法，一般程序设计环境中都提供有相关的功能或函数，读者可参考相关手册。

(2) 关于实验测试数据的记录、展示和分析	对于实验测试数据，如实验用时间和空间的记录一般采用程序设计语言中的功能函数来实现；测试数据的展示通常是采用表格、图标的形式，直观地给出；数据分析则需要实验者在认真比较和分析的基础上给出，这也是培养严谨的治学态度所必需的，必须本着实事求是的态度来完成此项工作。
