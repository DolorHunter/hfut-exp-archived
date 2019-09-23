# coding:utf-8

import operator
from queue import Queue


mat = []  # 分析表
grams = []  # 文法表
t = []  # 终结符
nt = []  # 非终结符
simp_grams = []  # 简化后的语句(去除或)
first_langs = {}  # 储存非终结符的first集合
follow_langs = {}  # 储存非终结符的follow集合

step_list = []  # 步骤表
analysis_list = []  # 分析栈表
input_string_list = []  # 输入串表
production_list = []  # 所用产生式表
action_list = []  # 动作表


class Stack(object):
    def __init__(self):
        self.items = []

    def is_empty(self):
        return len(self.items) == 0

    def push(self, item):
        self.items.append(item)

    def pop(self):
        if not self.is_empty():
            return self.items.pop()

    def peek(self):
        if not self.is_empty():
            return self.items[len(self.items)-1]

    def size(self):
        return len(self.items)


# 初始化(清空)各个表与其中的数据
def init_list():
    mat.clear()  # 分析表
    grams.clear()  # 文法表
    t.clear()  # 终结符
    nt.clear()  # 非终结符
    simp_grams.clear()  # 简化后的语句(去除或)
    first_langs.clear()  # 储存非终结符的first集合
    follow_langs.clear()  # 储存非终结符的follow集合

    step_list.clear()  # 步骤表
    analysis_list.clear()  # 分析栈表
    input_string_list.clear()  # 输入串表
    production_list.clear()  # 所用产生式表
    action_list.clear()  # 动作表
    print('Wiped out all the info in the list!!')


# 建立文法(读文件)
def create_grammar_list(filename):
    file = open(filename, 'r')
    lines = file.read().split('\n')
    for line in lines:
        grams.append(line)
    file.close()
    # print(grams)  # test
    print('Grammar list created successfully!!')


# 提取终结符与非终结符
def extract_terminal_symbol():
    # 遍历文法表g[], 提取终结符与非终结符
    for gram in grams:
        if gram == '':  # 空行跳过
            continue
        else:
            if gram[0] not in nt:
                nt.append(gram[0])  # 加入左端非终结符
            elems = gram.split('->')
            for elem in elems[1]:
                # 新元素入表
                if not(elem in nt or elem in t):
                    if elem.isupper():
                        nt.append(elem)  # 非终结符加入nt[]
                    elif elem != 'ε' and elem != '|':
                        t.append(elem)  # 终结符加入t[]
    # print('t:', t)  # [test]
    # print('nt:', nt)  # [test]
    print('Extracted terminal & non-terminal symbol successfully!!')


# 建立简化语句的列表simp_grams[]
def create_language_dict():
    # 简化文法(分离或语句)
    for gram in grams:
        if '|' not in gram:  # 已经是最简语句(没有或)
            simp_grams.append(gram)
        else:  # 不是最简语句(有或)
            after_arrow = gram.split('->')  # 分割'->'左右, 为下一次分割作准备
            rules = after_arrow[1].split('|')  # 分割'|'左右
            for rule in rules:
                simp_gram = after_arrow[0] + '->' + rule
                simp_grams.append(simp_gram)
    # print(simp_grams)  # test
    print('Simplified the grammar successfully!!')


# 创建first{}集
def create_first_assemble():
    # 建立非终结符的first集合字典first_lang{}
    for i in nt:
        first_langs[i] = set()
    # 从simp_grams中找首个字符直到其为终结符
    for simp_gram in simp_grams:
        first = simp_gram.split('->')  # 分割得到潜在first集合元素 (first[1][0])
        if first[1][0] in t or first[1][0] == 'ε':  # 如果是终结符或ep, 加入first集合(重复的epsilon会自动消除)
            first_langs[first[0]].add(first[1][0])
        else:  # 非终结符继续搜索
            next_elem = first[1][0]  # 当前元素为下次搜索的起始元素
            while next_elem in nt:  # 非终结符继续搜索
                for s_gram in simp_grams:  # 寻找生成式子左端(从下至上)  # reversed后续如何退出???
                    if s_gram[0] == next_elem:  # 找到符合的生成式
                        next = s_gram.split('->')
                        if next[1][0] in t:  # 终结符
                            first_langs[first[0][0]].add(next[1][0])  # 将此非终结符加入原起始符的first集合
                            # 继续寻找下一个潜在终结符, 直到找到表头
                            if s_gram == simp_grams[len(simp_grams)-1]:  # 当走到表尾
                                next_elem = next[1][0]  # 下一个元素(while退出)
                        elif 'ε' in first_langs[next[1][0]]:  # 推导出的元素是epsilon
                            first_langs[first[0][0]].add(next[1][0])  # ep加入first集合中
                            if len(first[1]) > 1:  # 当生成式右端为多个字符, 搜索邻位字符的first集
                                # print(first[1][1])
                                next_elem = first[1][1]
                        else:  # 非终结符
                            for elem in first_langs[next[1][0]]:  # 复制非终结符的first集给自己
                                first_langs[first[0][0]].add(elem)
                            next_elem = next[1][0]  # 继续寻找

    # first_langs['F'].add('i')  # test # set的重复自动消除测试
    # print(first_langs)  # test
    print('First assemble created successfully!!')


# 创建follow{}集
def create_follow_assemble():
    # 建立非终结符的follow集合字典follow_lang{}
    for i in nt:
        follow_langs[i] = set()
    follow_langs[grams[0][0]].add('#')  # 情况一, 对于开始符号，加入'#'
    situ3_2 = False  # 情况三之2判断
    for i in nt:  # 遍历非终结符
        for simp_gram in simp_grams:  # 遍历生成式
            source = simp_gram.split('->')  # 预分割
            if i in source[1]:  # 非终结符在当前simp_grams生成端
                follow = source[1].split(i)  # 分割当前非终结符左右
                # follow[1][0] == '' 会存在超限问题!!
                if len(follow[1]) == 0:  # follow为空 情况三之1: A->aB
                    # 情况三之1: A->aB, Follow(B)=Follow(A)
                    for follow_lang in follow_langs[source[0][0]]:
                        follow_langs[i].add(follow_lang)
                else:  # follow不为空
                    if follow[1][0] in t:  # follow为终结符
                        follow_langs[i].add(follow[1][0])  # 直接添加终结符到follow
                    else:  # follow为非终结符

                        # 情况二: A->aBb, Follow(B)=First(b)\{ep}
                        for first_lang in first_langs[follow[1][0]]:
                            if first_lang != 'ε':
                                follow_langs[i].add(first_lang)
                            else:
                                situ3_2 = True  # 执行情况三之2

                        # 情况三之2: A->aBb, Follow(B)=Follow(A)
                        if situ3_2:  # ep属于First(b)
                            for follow_lang in follow_langs[source[0][0]]:
                                follow_langs[i].add(follow_lang)
                        situ3_2 = False  # 状态清空

    # print(follow_langs)  # test
    print('Follow assemble created successfully!!')


# 判断左递归(递推非代入)
def verified_left():
    # 规则一: 文法不含左递归
    derivation_grams = simp_grams  # 推导后的最简文法
    for derivation_gram in derivation_grams:
        next_derivation = derivation_gram[3]  # 下一个推导的左端
        if next_derivation == derivation_gram[0]:
            print('[ERROR] Does not meet the first rule of LL(1)!!')
            return False
        while next_derivation in nt:  # ->后首位为非终结符, 潜在左递归文法
            for d_gram in derivation_grams:  # 找推导后的文法最左处是否存在非终结符
                if d_gram[0] == next_derivation:  # 找到了下一个推导式
                    # print(d_gram)
                    if d_gram[3] in nt:  # 推导后的文法最左为非终结符, 仍可能为左递归文法
                        next_derivation = d_gram[3]  # 提取下一个推导的左端

                    # 到了文法末尾时, 多推导一次, 赋值d_grams[3], 当d_grams[3]为非终结符自动退出while循环
                    if d_gram == derivation_grams[len(derivation_grams) - 1] and next_derivation in nt:
                        next_derivation = d_gram[3]  # 下一个元素(while退出)

                    if derivation_gram[0] == d_gram[3]:  # 出现左递归
                        print('[ERROR] Does not meet the first rule of LL(1)!!')
                        return False
    print('Not left recursion grammar!!')
    return True


# 验证是否为LL1文法(公式是否错误)
def verified_ll1():
    verified_left()  # 左递归判断
    # 规则二: 候选first不相交
    for simp_gram in simp_grams:
        for s_gram in simp_grams:
            # 生成式左端相等(存在或结构) 且两个生成式不同
            if (not operator.eq(simp_gram, s_gram)) and simp_gram[0] == s_gram[0]:
                # 求simp_grams生成式右边的first集
                if simp_gram[3] in t:
                    first_simp_grams = simp_gram[3]
                elif simp_gram[3] == 'ε':
                    first_simp_grams = ''  # first集为空
                else:
                    first_simp_grams = first_langs[simp_gram[3]]
                # 求s_grams生成式右边的first集
                if s_gram[3] in t:
                    first_s_grams = s_gram[3]
                elif s_gram[3] == 'ε':
                    first_s_grams = ''  # first集为空
                else:
                    first_s_grams = first_langs[s_gram[3]]

                # 取交集判断是否为空, 若非空则报错
                for ch in first_simp_grams:
                    for c in first_s_grams:
                        if ch == c:
                            print('[ERROR] Does not meet the second rule of LL(1)!!')
                            return False

    # 规则三: 非终结符的候选集含有ep, first集和follow集不相交
    for key in nt:
        if 'ε' in first_langs[key]:
            # 取交集判断是否为空, 若非空则报错
            for ch in first_langs[key]:
                for c in follow_langs[key]:
                    if ch == c:
                        # print(first_langs[key], follow_langs[key])
                        print('[ERROR] Does not meet the third rule of LL(1)!!')
                        return False

    print('Equation verified successfully!!')
    return True  # 满足三个条件


# 建立分析表(作弊表)
def create_cheat_list():
    gt = t  # 作图专用列
    gt.append('#')  # 加入#
    mat.append(['']+gt)  # 填入首行信息
    line_info = []  # 存储行信息
    placeholder = True  # 作为Error的占位标记
    for i in nt:  # 遍历非终结符
        line_info.append(i)
        for j in gt:  # 遍历终结符
            for simp_gram in simp_grams:  # 遍历文法
                if i == simp_gram[0]:  # 生成式左边与行信息相同
                    # 当i的语法中, '->'后首位的first集(非终结符) 或 直接求列符号相等(终结符), 填入i语法
                    # eg. E->TE', FIRST(TE')={(,id} 所以E->TE', 填入M[E, id]和M[E, (]
                    if (simp_gram[3] in nt and j in first_langs[simp_gram[3]]) or (simp_gram[3] in t and simp_gram[3] == j):
                        line_info.append(simp_gram)  # 填入该文法
                        placeholder = False  # 不需要占位(error)
                    # 当i的first集有ep, 在i的follow集同列填入该(E->epsilon)文法
                    # eg. E'->ε FOLLOW(E')={), #} 所以E'->ε填入M[E', )]和M[E', #]
                    if ('ε' in first_langs[i] and j in follow_langs[i] and simp_gram[3] == 'ε') or (j == '#' and simp_gram[3] == 'ε'):
                        line_info.append(simp_gram)  # 填入该文法
                        placeholder = False  # 不需要占位(error)
            if placeholder:
                line_info.append('')
            placeholder = True  # 状态清空
        mat.append(line_info)
        line_info = []
    # print(mat)  # test
    print('Cheat list created successfully!!')


# 文法预处理
def pre_analysis():
    extract_terminal_symbol()  # 提取终结符与非终结符
    create_language_dict()  # 建立非终结符的直接推导结果汇总的字典simp_lang{}


# 建立分析表
def create_analysis_list():
    create_first_assemble()  # 求first集
    create_follow_assemble()  # 求follow集
    verified_ll1()  # 判断是否是LL1文法(验证公式)
    create_cheat_list()  # 建立分析表(作弊表)
    print('Analysis list created successfully!!')


# 利用分析表对文法进行分析分析
def analysis_grammar(input_string):  # input_string 为输入串
    # 建立输入串队列, 初始化符号串
    input_queue = Queue()
    for input_char in input_string:
        input_queue.put(input_char)  # 逐个输入符号入队

    # 初始化分析串
    analysis_stack = Stack()  # 创建分析栈
    analysis_stack.push('#')  # 栈底放入'#'
    analysis_stack.push(simp_grams[0][0])  # 放入文法开始符号

    # 各个表初始化
    current_step = 0  # 当前步骤
    step_list.append(current_step)  # 步骤表初始化
    analysis_list.append("".join(analysis_stack.items))  # 分析表初始化
    input_string_list.append("".join(input_queue.queue))  # 输入串表初始化
    production_list.append("")  # 产生式表初始化
    action_list.append('初始化')  # 动作表初始化
    # 若 not X=a='#', 即size大于1, 继续分析
    while not (input_queue.queue[0] == '#' and analysis_stack.peek() == '#'):
        current_step += 1
        step_list.append(current_step)  # 当前步骤加入s_l表

        # 情况二: 栈顶元素X为终结符 X=a!=#
        if analysis_stack.peek() == input_queue.queue[0] and analysis_stack.size() > 1:
            action_list.append('GETNEXT(' + analysis_stack.peek() + ')')  # 当前动作加入a_l表
            analysis_stack.pop()  # X逐出栈顶
            input_queue.get()  # a指向下一个符号
            analysis_list.append("".join(analysis_stack.items))  # 当前分析串加入a_l表(join化简)
            input_string_list.append("".join(input_queue.queue))  # 当前输入串加入i_s_l表(join化简)
            production_list.append('')  # 加入空产生式

        # 情况三: 栈顶元素X为非终结符
        elif analysis_stack.peek() in nt:
            # 遍历分析表, 查找生成式
            row = 0
            col = 0
            for i in range(len(mat)):  # 遍历行(非终结符)
                if mat[i][0] == analysis_stack.peek():  # 分析栈的顶(非终结符或终结符) [陈其迈的手]
                    row = i
                    break
            for j in range(len(mat[0])):  # 遍历列(终结符)
                if mat[0][j] == input_queue.queue[0]:  # 输入串的头(非终结符) [韩国瑜的头]
                    col = j
                    break
            if mat[row][col] == '':  # M[A, a]为出错标志, 调用出错检测程序
                analysis_list.append("ERROR!!")  # 出错
                input_string_list.append("ERROR!!")  # 出错
                production_list.append("ERROR!!")  # 出错
                action_list.append("ERROR!!")  # 出错
                print('[ERROR] No production in M[A, a]!!')
                break  # 退出, 防止死循环
            else:
                # X出栈, 产生式右边反序入栈(ep不入)
                analysis_stack.pop()  # X逐出栈顶
                rule = mat[row][col].split('->')
                if rule[1][0] != 'ε':  # 生成式右边不为epsilon入栈, 否则不入栈
                    for ch in rule[1][::-1]:  # 产生式右部串反序(倒叙)入栈
                        analysis_stack.push(ch)  # 单个字符入栈, 否则会匹配错误
                    action_list.append('POP, PUSH(' + rule[1][::-1] + ')')  # 当前动作加入a_l表
                else:  # 生成式右边为ep, 不入栈
                    action_list.append('POP')  # 当前动作加入a_l表
                analysis_list.append("".join(analysis_stack.items))  # 当前分析串加入a_l表(join化简)
                input_string_list.append("".join(input_queue.queue))  # 当前输入串加入i_s_l表(join化简)
                production_list.append(mat[row][col])  # 当前产生式加入p_l表

        # 其他情况报错
        else:
            print("[ERROR]")
            break  # 退出, 防止死循环

    # print(step_list)  # test
    # print(analysis_list)  # test
    # print(input_string_list)  # test
    # print(production_list)  # test
    # print(action_list)  # test
    # print("Analysis grammar successfully!!")


'''
# 主调函数(调试)
def main():
    create_grammar_list("C://Users//ultrabook//Desktop//exp2//G(E)_eg.txt")
    create_analysis_list()
    analysis_grammar('i+i*i#')
if __name__ == '__main__':
    main()
'''