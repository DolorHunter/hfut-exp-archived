# coding:utf-8

from queue import Queue
import operator
import copy
import string

grams = []  # 文法表
vt = []  # 终结符
vn = []  # 非终结符
simp_grams = []  # 简化后的语句(去除或)
first_langs = {}  # 非终结符的first集合
follow_langs = {}  # 非终结符的follow集合
collections = []  # 项目集
canonical_collections = []  # 项目集族
action = []  # 动作表
goto = []  # 转移表
action_heading = []  # 动作表首行
goto_heading = []  # 转移表首行

step_list = []  # 步骤表
status_stack_list = []  # 分析栈(状态)表
symbol_stack_list = []  # 分析栈(符号)表
input_string_list = []  # 输入串表
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
    grams.clear()  # 初始化文法表
    vt.clear()  # 初始化终结符
    vn.clear()  # 初始化非终结符
    simp_grams.clear()  # 初始化简化后的语句(去除或)
    first_langs.clear()  # 初始化非终结符的first集合
    follow_langs.clear()  # 初始化非终结符的follow集合
    collections.clear()  # 初始化项目集
    canonical_collections.clear()  # 初始化项目集族
    action.clear()  # 初始化动作表
    goto.clear()  # 初始化转移表
    action_heading.clear()  # 初始化动作表首行
    goto_heading.clear()  # 初始化转移表首行
    step_list.clear()  # 初始化步骤表
    status_stack_list.clear()  # 初始化分析栈(状态)表
    symbol_stack_list.clear()  # 初始化分析栈(符号)表
    input_string_list.clear()  # 初始化输入串表
    action_list.clear()  # 初始化动作表
    print('All the info on the list were wiped out!!')


# 建立文法(读文件)
def create_grammar_list(filename):
    file = open(filename, 'r')
    lines = file.read().split('\n')
    for line in lines:
        if line != '':  # 不为空行
            grams.append(line)
    file.close()
    # print('grams', grams)  # test
    print('Grammar list was created!!')


# 提取终结符与非终结符
def extract_terminal_symbol():
    # 遍历文法表g[], 提取终结符与非终结符
    for gram in grams:
        if gram == '':  # 空行跳过
            continue
        else:
            elems = gram.split('->')
            if gram[0] not in vn:
                vn.append(gram[0])  # 加入左端非终结符
            for elem in elems[1]:
                # 新元素入表
                if not(elem in vt or elem in vn):
                    if elem.isupper():
                        vn.append(elem)  # 非终结符加入vn{}
                    elif elem != 'ε' and elem != '|':
                        vt.append(elem)  # 终结符加入vt{}
    # print('vn', vn, 'vt:', vt)  # test
    print('Terminal & non-terminal symbols were extracted!!')


# 生成拓广文法
def extend_grammar():
    extend_vn = ''
    for upper in string.ascii_uppercase:
        if upper not in vn:
            extend_vn = upper
            break
    vn.insert(0, extend_vn)  # 加入新的vn
    extend_gram = extend_vn + '->' + grams[0][0]
    grams.insert(0, extend_gram)  # 添加拓广到文法头部
    print('vn', vn, 'vt:', vt, 'grams:', grams)
    print('The grammar was extended!!')


# 生成简化语句的列表simp_grams[]
def create_simplified_grammar():
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
    print('The grammar was simplified!!')


# 创建first{}集
def create_first_assemble():
    # 建立非终结符的first集合字典first_lang{}
    for i in vn:
        first_langs[i] = set()
    # 从simp_grams中找首个字符直到其为终结符
    for simp_gram in simp_grams:
        first = simp_gram.split('->')  # 分割得到潜在first集合元素 (first[1][0])
        if first[1][0] in vt or first[1][0] == 'ε':  # 如果是终结符或ep, 加入first集合(重复的epsilon会自动消除)
            first_langs[first[0]].add(first[1][0])
        else:  # 非终结符继续搜索
            next_elem = first[1][0]  # 当前元素为下次搜索的起始元素
            while next_elem in vn:  # 非终结符继续搜索
                for s_gram in simp_grams:  # 寻找生成式子左端(从下至上)  # reversed后续如何退出???
                    if s_gram[0] == next_elem:  # 找到符合的生成式
                        next = s_gram.split('->')
                        if next[1][0] in vt:  # 终结符
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
    # print(first_langs)  # test
    print('First assemble was created successfully!!')


# 创建follow{}集
def create_follow_assemble():
    # 建立非终结符的follow集合字典follow_lang{}
    for i in vn:
        follow_langs[i] = set()
    follow_langs[grams[0][0]].add('#')  # 情况一, 对于开始符号，加入'#'
    situ3_2 = False  # 情况三之2判断
    for i in vn:  # 遍历非终结符
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
                    if follow[1][0] in vt:  # follow为终结符
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
    print('Follow assemble was created successfully!!')


# 构造项目集
def create_collections():
    for simp_gram in simp_grams:
        elems = simp_gram.split('->')
        for i in range(len(elems[1])):
            if i == 0:  # 首个字符
                item = elems[0] + '->' + '•' + elems[1][i:]
                collections.append(item)
            item = elems[0] + '->' + elems[1][0:i+1] + '•' + elems[1][i+1:]
            collections.append(item)
    # print(collections)  # test
    print('The collections were created!!')


# 构造闭包函数(递归)
def closure(i, c):  # i为项目, c为闭包集
    if len(i) > i.index('•')+1:  # 点不是最后一个元素(排错+限定)
        next_elem = i[i.index('•') + 1]  # 点之后的元素为下一个访问的元素
        if next_elem in vn:
            for col in collections:
                # col不在c中, 且下一个元素与项目首元素相同且项目刚开始
                if col not in c and (next_elem == col[0] and col[3] == '•'):
                    c.append(col)  # 此项目加入闭包c
                    if len(col) > col.index('•')+1 and col[col.index('•')+1] in vn:  # 点不为最后元素且点后为非终结符
                        closure(col, c)  # 构造新闭包


# 构造项目的闭包Closure(I)
def create_closure(i):  # i为状态的项目集头
    c = [i]  # 首项目加入Closure(i)
    closure(i, c)  # 计算i的闭包, 项目加入c
    # print(c)  # test
    return c


# 构造Go(I, x)
def go(front_c, x):  # I为项目集, x为元素
    c = []  # 下一个状态的闭包(c建立于函数头, 防止状态内出现多个点后相同元素的项目无法合并)
    for f_c in front_c:
        if len(f_c) > f_c.index('•')+1 and x == f_c[f_c.index('•')+1]:  # 项目的点下一个元素为x
            next_i = f_c[0:f_c.index('•')] + x + '•' + f_c[f_c.index('•')+2:]  # 下一个状态的项目集头(识别两元素增加精度)
            c.append(next_i)
            if len(next_i) > next_i.index('•')+1 and next_i[next_i.index('•')+1] in vn:  # 点不为最后一个符号且点后为非终结符
                closure(next_i, c)  # 构建闭包, 结果返回c
    # print(c)  # test
    return c


# 构造LR(0)项目集规范族族
def create_canonical_collections():
    # 第一个状态的状态拓展
    clos = create_closure(collections[0])  # 从拓广语句开始首个状态
    ct = 0  # 状态计数
    # 第一个参数表示状态数, 第二个参数表示是否拓展过, 第三个参数表示该状态的项目集
    canonical_collections.append([ct, clos])  # 加入初始状态I0
    # 拓展剩余状态, 直到所有状态都经过拓展
    old_canonical_collections = []
    while not operator.eq(old_canonical_collections, canonical_collections):  # 当新旧c_cs不等, 表示仍有未访问的状态
        old_canonical_collections = copy.deepcopy(canonical_collections)  # 将c_cs赋给旧c_cs
        for i in range(len(canonical_collections)):
            elem = []  # 用于消除不同项目的同元素产生的重复状态
            for c_collection in canonical_collections[i][1]:  # 遍历状态中的项目集
                if len(c_collection) > c_collection.index('•')+1:  # 项目中的点不为最后一个元素(其他情况无下一状态)
                    x = c_collection[c_collection.index('•')+1]
                    go_result = go(canonical_collections[i][1], x)  # go运算结果(减少重复运算)
                    new_result = True  # 新状态标记
                    for j in range(len(canonical_collections)):
                        if operator.eq(go_result, canonical_collections[j][1]):  # 与已有状态相等, 为旧状态(重复状态)
                            new_result = False
                    # go非空且不属于c且为新状态
                    if go_result != [] and go_result not in clos and new_result:
                        if x not in elem:  # 该状态的触发元素第一次出现(合并同状态中, 不同项目的同个触发条件, 以合并下个状态)
                            elem.append(x)  # 加入元素
                        canonical_collections.append([ct+elem.index(x)+1, go_result])  # 加入状态In, 新状态设置为True
            ct += len(elem)  # 前进elem个状态(len(elem)为当前状态新产生的状态数量)
    # print(canonical_collections)  # test
    print('The canonical collections were created!!')


# 文法预处理(提取, 拓广, 简化)
def pre_process():
    extract_terminal_symbol()
    extend_grammar()
    create_simplified_grammar()


# 生成分析表
def create_analysis_list():
    create_first_assemble()  # 求follow集
    create_follow_assemble()  # 求first集
    # 构建action表
    action_first_line = vt
    action_first_line.append('#')
    action_heading.extend(action_first_line)  # 写入首行信息(制表用)
    action.append(action_first_line)  # 写入首行信息
    for c in canonical_collections:  # 状态数量(仅用于增加行数)
        line_info = []
        for f in action_first_line:  # first_line数量(仅用于增加列数)
            line_info.append('')
        action.append(line_info)

    # 构建goto表
    goto_first_line = vn  # 更新first_line
    goto_first_line.remove(simp_grams[0][0])  # vn删去拓广产生的元素
    goto_heading.extend(goto_first_line)  # 写入首行信息(制表用)
    goto.append(goto_first_line)  # 写入首行信息
    for c in canonical_collections:  # 状态数量(仅用于增加行数)
        line_info = []
        for f in goto_first_line:  # first_line数量(仅用于增加列数)
            line_info.append('')
        goto.append(line_info)

    # 填写action表, goto表
    for i in range(len(canonical_collections)):  # 遍历项目集规范族中的每个状态
        for k in range(len(canonical_collections[i][1])):  # 遍历该状态的每个项目
            # 情况一: A->a•ab属于Ik且Go(Ik,a)=Ij, a为终结符
            if len(canonical_collections[i][1][k]) > canonical_collections[i][1][k].index('•')+1:  # 点不为尾元素(潜在移进)
                x = canonical_collections[i][1][k][canonical_collections[i][1][k].index('•')+1]  # 点后的元素
                go_result = go(canonical_collections[i][1], x)  # go下一个状态的项目集
                for c_c in canonical_collections:
                    j = c_c[0]  # j为新状态状态序号(c_c[0]), 新状态Ij为c_c[1]
                    if operator.eq(go_result, c_c[1]):  # Go(Ik,a)=Ij
                        if x in vt:  # x为终结符(情况一)
                            if action[canonical_collections[i][0] + 1][action_first_line.index(x)] != '' and \
                                    action[canonical_collections[i][0] + 1][action_first_line.index(x)][0] != 's' + str(j):
                                print('[ERROR]: NOT SLR(1) GRAMMAR!!')
                                return False  # 存在多重入口, 不是SLR(1)文法
                            action[canonical_collections[i][0] + 1][action_first_line.index(x)] = 's' + str(j)  # ACTION[k,a]=sj
                        # 情况四: Go(Ik,A)=Ij, A为非终结符, Goto[k,A]=j
                        elif x in vn:  # x为非终结符(情况四)
                            if goto[canonical_collections[i][0] + 1][goto_first_line.index(x)] != '' and \
                                    goto[canonical_collections[i][0] + 1][goto_first_line.index(x)] != j:
                                print('[ERROR]: NOT SLR(1) GRAMMAR!!')
                                return False  # 存在多重入口, 不是SLR(1)文法
                            goto[canonical_collections[i][0] + 1][goto_first_line.index(x)] = j  # Goto[k,A]=j
                        else:
                            print('[ERROR]: x not in vt or vn!!')
            # 情况二: A→a•属于Ik, 对任何终结符a属于FOLLOW(A), 置ACTION[k,a]为rj. (假定A->a为文法G'的第j个产生式)
            elif len(canonical_collections[i][1][k]) == canonical_collections[i][1][k].index('•')+1:  # 点为最后元素(潜在规约)
                # 情况三: (拓广文法)若项目S'→S·属于Ik，则置ACTION[k,#]为“acc”
                if operator.eq(canonical_collections[i][1][k], simp_grams[0]+'•'):  # 项目为拓广文法(状态启动文法)
                    if action[canonical_collections[i][0]+1][action_first_line.index('#')] != '' and \
                            action[canonical_collections[i][0] + 1][action_first_line.index('#')] != 'acc':
                        print('[ERROR]: NOT SLR(1) GRAMMAR!!')
                        return False  # 存在多重入口, 不是SLR(1)文法
                    action[canonical_collections[i][0]+1][action_first_line.index('#')] = 'acc'  # 完成标志(移进-规约完成)
                else:  # 情况二: (非拓广文法)A→a•属于Ik, 对任何终结符a属于FOLLOW(A), 置ACTION[k,a]为rj. (假定A->a为文法G'的第j个产生式)
                    for x in follow_langs[canonical_collections[i][1][k][0]]:  # 对a属于FOLLOW(A)
                        row_gram = str(canonical_collections[i][1][k]).replace('•', '')  # 消去点(得到产生式)
                        for j in range(len(simp_grams)):
                            if operator.eq(row_gram, simp_grams[j]):
                                if action[canonical_collections[i][0] + 1][action_first_line.index(x)] != '' and \
                                        action[canonical_collections[i][0] + 1][action_first_line.index(x)] != 'r' + str(j):
                                    print('[ERROR]: NOT SLR(1) GRAMMAR!!')
                                    return False  # 存在多重入口, 不是SLR(1)文法
                                action[canonical_collections[i][0] + 1][action_first_line.index(x)] = 'r' + str(j)  # ACTION[k,a]=rj
            else:
                print("[ERROR]: len(c_cs) < c_cs[i][1][k].index('•')+1, WTF??")
    return True  # 是SLR(1)文法
    # print(action)  # test
    # print(goto)  # test
    print('Created the analysis list!!')


# 用分析表分析输入串
def analysis_input_string(input_string):
    # 建立输入串队列, 初始化符号串
    input_queue = Queue()
    for char in input_string:
        input_queue.put(char)  # 逐个输入符号入队

    # 初始化分析栈
    analysis_stack = Stack()  # 分析栈(状态符号栈)
    analysis_stack.push(['0', '#'])  # 栈底放入初始状态, 符号

    # 各个表初始化
    current_step = 0  # 当前步骤
    status_stack_list.append(" ".join(item[0] for item in analysis_stack.items))
    symbol_stack_list.append(" ".join(item[1] for item in analysis_stack.items))
    input_string_list.append(" ".join(input_queue.queue))  # 输入串表初始化
    # 动作说明滞后一步, 故初始化时无动作说明

    while True:
        current_step += 1
        step_list.append(current_step)  # 当前步骤加入s_l表

        current_status = int(analysis_stack.peek()[0])  # 当前状态(int)
        current_string_head = input_queue.queue[0]  # 当前输入串头(str)

        # 情况三: 接受
        if action[current_status + 1][action[0].index(current_string_head)] == 'acc':
            action_list.append('Acc: 分析成功')
            break  # 退出
        # 情况一: 移进
        elif action[current_status + 1][action[0].index(current_string_head)][0] == 's':
            new_status = int(action[current_status + 1][action[0].index(current_string_head)][1])  # 新状态为s后数字
            analysis_stack.push([str(new_status), current_string_head])  # 新状态, 新符号入栈
            input_queue.get()  # 输入串头出队
            status_stack_list.append(" ".join(item[0] for item in analysis_stack.items))
            symbol_stack_list.append(" ".join(item[1] for item in analysis_stack.items))
            input_string_list.append(" ".join(input_queue.queue))
            action_list.append('ACTION[' + str(current_status) + ', ' + current_string_head + ']=' +
                               action[current_status + 1][action[0].index(current_string_head)] + ', 状态' +
                               action[current_status + 1][action[0].index(current_string_head)][1] + '入栈')  # 添加动作说明
        # 情况二: 规约
        elif action[current_status + 1][action[0].index(current_string_head)][0] == 'r':
            rule_number = int(action[current_status + 1][action[0].index(current_string_head)][1])  # 规约使用的公式序号
            protocol_string = simp_grams[rule_number].split('->')[1][::-1]  # 切分语法, 倒序规约串
            new_symbol = simp_grams[rule_number][0]
            for char in protocol_string:  # 遍历倒序规约串
                if operator.eq(char, analysis_stack.peek()[1]):  # 规约字符 = 栈顶字符, 出栈
                    analysis_stack.pop()  # 分析栈出栈
                else:  # 排错
                    print('[ERROR]: Protocol string not equal to symbol in stack!!')
                    break
            current_top_status = int(analysis_stack.peek()[0])  # 出栈后的临时栈顶
            if goto[current_top_status + 1][goto[0].index(new_symbol)] == '':
                print('[ERROR]: No element in goto list!!')
                break
            new_status = int(goto[current_top_status + 1][goto[0].index(new_symbol)])  # 新状态为goto(临时栈顶状态, 规约获得符号)
            analysis_stack.push([str(new_status), new_symbol])  # 新状态, 新符号入栈
            status_stack_list.append(" ".join(item[0] for item in analysis_stack.items))
            symbol_stack_list.append(" ".join(item[1] for item in analysis_stack.items))
            input_string_list.append(" ".join(input_queue.queue))
            action_list.append(action[current_status + 1][action[0].index(current_string_head)] + ': ' +
                               simp_grams[rule_number] + '规约,' + 'GOTO(' + str(current_top_status) + ', ' +
                               new_symbol + ')=' + str(new_status) + '入栈')  # 添加动作说明
        # 情况四: 报错
        elif action[current_status + 1][action[0].index(current_string_head)] == '':
            print('[ERROR]: No element in action list!!')
            action_list.append('ERROR')
            break  # 退出
        # 其他情况
        else:
            print('[ERROR]: Other situations in analysis process??')
            break
    # print(step_list)  # test
    # print(status_stack_list)  # test
    # print(symbol_stack_list)  # test
    # print(input_string_list)  # test
    # print(action_list)  # test
    print("Analysis grammar successfully!!")


'''
def main():
    # create_grammar_list("C://Users//ultrabook//Desktop//exp3//G(E)_eg.txt")  # test1
    create_grammar_list("C://Users//ultrabook//Desktop//exp3//G(S)_notSLR.txt")
    pre_process()
    create_collections()
    # create_closure(collections[0])  # test
    # go(collections[0], 'T')  # test
    create_canonical_collections()
    create_analysis_list()
    analysis_input_string('i+i*i#')  # test1 & test2


if __name__ == '__main__':
    main()
'''