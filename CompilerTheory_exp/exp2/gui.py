# coding:utf-8

from tkinter import *
from tkinter import ttk
from tkinter import filedialog
from tkinter import messagebox
import ll1

MAX = 10


class Gui:
    def __init__(self, master):
        self.init_input = StringVar()
        # ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        # self.frame为按钮和输入栏的容器
        self.frame = Frame(master)
        self.frame.pack()
        self.new_button = Button(self.frame, text="新建", command=self.new, width=15)
        self.new_button.grid(row=0, column=0)
        self.open_button = Button(self.frame, text="打开", command=self.open_file, width=15)
        self.open_button.grid(row=0, column=1)
        self.start_button = Button(self.frame, text="开始", command=self.start_analysis, width=15)
        self.start_button.grid(row=0, column=2)
        self.help_button = Button(self.frame, text="帮助", command=self.help, width=14)
        self.help_button.grid(row=0, column=3)
        self.quit_button = Button(self.frame, text="退出", command=sys.exit, width=14)
        self.quit_button.grid(row=0, column=4)
        # --------------------------------------------------------------------------------------------------------------
        self.input_frame = Frame(master)
        self.input_frame.pack()
        self.input_label = Label(self.frame, text="输入串:", width=15)
        self.input_label.grid(row=1, column=0, columnspan=1)
        self.input_entry = Entry(self.frame, textvariable=self.init_input, state=NORMAL, width=60)
        self.input_entry.grid(row=1, column=1, columnspan=4)
        self.init_input.set('i+i*i#')  # 初始输入串'
        # ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        # self.info_frame为文法, first集, follow集的容器
        self.info_frame = Frame(master)
        self.info_frame.pack()
        # 实例化输入的文法
        self.grammar_tree = ttk.Treeview(
            self.info_frame,
            height=5,
            show="headings",  # 隐藏首列
        )
        self.grammar_tree.grid(row=0, column=0, columnspan=1, sticky="NSEW")
        # 表头设置
        self.grammar_tree["columns"] = ("grammar_tree")
        self.grammar_tree.column("grammar_tree", width=165, anchor="center")  # 表示列,不显示
        # 表列设置
        self.grammar_tree.heading("grammar_tree", text="文法表")  # 显示表头
        # 垂直滚动条
        vbar1 = ttk.Scrollbar(self.info_frame, orient="vertical", command=self.grammar_tree.yview)
        self.grammar_tree.configure(yscrollcommand=vbar1.set)
        vbar1.grid(row=0, column=1, sticky="NS")
        # --------------------------------------------------------------------------------------------------------------
        # 实例化first集
        self.first_tree = ttk.Treeview(
            self.info_frame,
            height=5,
            show="headings",  # 隐藏首列
        )
        self.first_tree.grid(row=0, column=2, columnspan=1, sticky="NSEW")
        # 表头设置
        self.first_tree["columns"] = ("first_tree")
        self.first_tree.column("first_tree", width=165, anchor="center")  # 表示列,不显示
        # 表列设置
        self.first_tree.heading("first_tree", text="first集")  # 显示表头
        # 垂直滚动条
        vbar2 = ttk.Scrollbar(self.info_frame, orient="vertical", command=self.first_tree.yview)
        self.first_tree.configure(yscrollcommand=vbar2.set)
        vbar2.grid(row=0, column=3, sticky="NS")
        # --------------------------------------------------------------------------------------------------------------
        # 实例化follow集
        self.follow_tree = ttk.Treeview(
            self.info_frame,
            height=5,
            show="headings",  # 隐藏首列
        )
        self.follow_tree.grid(row=0, column=4, columnspan=1, sticky="NSEW")
        # 表头设置
        self.follow_tree["columns"] = ("follow_tree")
        self.follow_tree.column("follow_tree", width=165, anchor="center")  # 表示列,不显示
        # 表列设置
        self.follow_tree.heading("follow_tree", text="follow集")  # 显示表头
        # 垂直滚动条
        vbar3 = ttk.Scrollbar(self.info_frame, orient="vertical", command=self.follow_tree.yview)
        self.follow_tree.configure(yscrollcommand=vbar3.set)
        vbar3.grid(row=0, column=5, sticky="NS")
        # ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        # self.info_frame为文法, first集, follow集的容器
        self.analysis_mat_frame = Frame(master)
        self.analysis_mat_frame.pack()
        # 实例化分析表
        self.analysis_mat_tree = ttk.Treeview(
            self.analysis_mat_frame,
            height=7,
            show="headings",  # 隐藏首列
        )
        self.analysis_mat_tree.grid(row=0, column=0, columnspan=1, sticky="NSEW")
        # 表头设置, 首行作为非终结符的标尺
        self.analysis_mat_tree["column"] = list(range(MAX))  # 先开辟足够大的空间(100)
        # 调整首行宽度与首列的信息
        self.analysis_mat_tree.column(0, width=40, anchor="center")
        self.analysis_mat_tree.heading(0, text="分析表")
        for i in range(1, MAX):
            self.analysis_mat_tree.column(i, width=55, anchor="center")  # 表示列,不显示
            self.analysis_mat_tree.heading(i, text=i)  # 表列设置

        # 垂直滚动条
        vbar = ttk.Scrollbar(self.analysis_mat_frame, orient="vertical", command=self.analysis_mat_tree.yview)
        self.analysis_mat_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=0, column=1, sticky="NS")
        # 水平滚动条
        hbar = ttk.Scrollbar(self.analysis_mat_frame, orient="horizontal", command=self.analysis_mat_tree.yview)
        self.analysis_mat_tree.configure(yscrollcommand=vbar.set)
        hbar.grid(row=1, column=0, sticky="WE")
        # ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        # self.info_frame为文法, first集, follow集的容器
        self.tree_frame = Frame(master)
        self.tree_frame.pack()
        # 实例化分析过程
        self.tree = ttk.Treeview(
            self.tree_frame,
            height=15,
            show="headings",  # 空白首列是显示的，设置show属性为 headings 即可隐藏首列
        )
        self.tree.grid(row=0, column=0, columnspan=1, sticky="NSEW")
        # 表头设置
        self.tree["columns"] = ("steps", "analysis_stack", "input_string", "production", "action")
        self.tree.column("steps", width=85, anchor="center")  # 表示列,不显示
        self.tree.column("analysis_stack", width=110)  # 表示列,不显示
        self.tree.column("input_string", width=110, anchor="e")  # 表示列,不显示
        self.tree.column("production", width=110, anchor="center")  # 表示列,不显示
        self.tree.column("action", width=120, anchor="center")  # 表示列,不显示
        # 表列设置
        self.tree.heading("steps", text="步骤")  # 显示表头
        self.tree.heading("analysis_stack", text="分析栈")
        self.tree.heading("input_string", text="剩余输入串")
        self.tree.heading("production", text="所用产生式")
        self.tree.heading("action", text="动作")
        # 垂直滚动条
        vbar = ttk.Scrollbar(self.tree_frame, orient="vertical", command=self.tree.yview)
        self.tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=0, column=1, sticky="NS")

    # 新建(清空)Entry
    def new_entry(self):
        self.input_entry.delete(0, END)  # 清空输入串

    # 新建(清空)语法
    def new_grammar(self):
        # 清空表格(tree), 删除子树
        items = self.grammar_tree.get_children()
        for item in items:
            self.grammar_tree.delete(item)  # 不可以self.tree.delete(self.tree.get_children())

    # 新建(清空)first集
    def new_first_lang(self):
        # 清空表格(tree), 删除子树
        items = self.first_tree.get_children()
        for item in items:
            self.first_tree.delete(item)  # 不可以self.tree.delete(self.tree.get_children())

    # 新建(清空)follow集合
    def new_follow_lang(self):
        # 清空表格(tree), 删除子树
        items = self.follow_tree.get_children()
        for item in items:
            self.follow_tree.delete(item)  # 不可以self.tree.delete(self.tree.get_children())

    # 新建(清空)分析表
    def new_analysis_mat_tree(self):
        # 清空表格(tree), 删除子树
        items = self.analysis_mat_tree.get_children()
        for item in items:
            self.analysis_mat_tree.delete(item)  # 不可以self.tree.delete(self.tree.get_children())

    # 新建(清空)Tree
    def new_tree(self):
        # 清空表格(tree), 删除子树
        items = self.tree.get_children()
        for item in items:
            self.tree.delete(item)  # 不可以self.tree.delete(self.tree.get_children())

    # 新建(清空)所有
    def new(self):
        self.new_entry()  # 新建输入串
        self.new_grammar()  # 新建语法
        self.new_first_lang()  # 新建first集
        self.new_follow_lang()  # 新建follow集
        self.new_analysis_mat_tree()  # 新建分析表
        self.new_tree()  # 新建tree表格
        ll1.init_list()  # 清空表及各种数据
        print("Delete all the input info(including grammar) successfully!!")

    # 打开文件导入语法
    def open_file(self):
        filename = filedialog.askopenfile()
        # print(filename.name)
        print("Open the file successfully!!")
        ll1.create_grammar_list(filename.name)
        for gram in ll1.grams:
            self.grammar_tree.insert("", END, values=gram)  # 打印grammar表

    # 获得输入串
    def get_input_string(self):
        return self.input_entry.get()

    def start_analysis(self):
        # self.new_tree()  # ???
        if len(ll1.grams) == 0 or len(self.get_input_string()) == 0:  # 文法表空或输入串空
            if len(ll1.grams) == 0:  # 文法表空
                messagebox.showerror('文法错误!!', '请先打开一个文法以开始分析!!')
                print("[ERROR] PLEASE OPEN A GRAMMAR FIRST!!")
            if len(self.get_input_string()) == 0:
                messagebox.showerror('输入错误!!', '请输入一个输入串以开始分析!!')
                print("[ERROR] PLEASE INPUT A STRING FIRST!!")
        else:  # 开始语法分析
            ll1.pre_analysis()  # 文法预处理

            if not ll1.verified_left():  # 文法左递归
                messagebox.showwarning('文法左递归!!', '文法包含直接/间接左递归!!')
            else:
                ll1.create_analysis_list()  # 建立分析表

                # 打印first集合(first_tree)
                for first_key in ll1.first_langs.keys():
                    value = "FIRST(" + first_key + ")=" + ",".join(ll1.first_langs[first_key])
                    self.first_tree.insert("", END, values=value)

                # 打印follow集合(follow_tree)
                for follow_key in ll1.follow_langs:
                    value = "FOLLOW(" + follow_key + ")=" + ",".join(ll1.follow_langs[follow_key])
                    self.follow_tree.insert("", END, values=value)

                # 打印分析表(analysis_tree)
                row = 0  # 打印行号
                for i in ll1.mat:
                    self.analysis_mat_tree.insert("", END, values=i)

                ll1.analysis_grammar(self.get_input_string())  # 分析文法

                # 打印分析数据(tree)
                for i in range(len(ll1.step_list)):
                    self.tree.insert("", END, values=(ll1.step_list[i], ll1.analysis_list[i], ll1.input_string_list[i],
                                                      ll1.production_list[i], ll1.action_list[i]))
                print("Analysis running successfully!!")

    def help(self):
        messagebox.showinfo('需要帮助?', '访问 https://github.com/DolorHunter/CompilerTheory_exp/issues 以得到帮助!!')
        print("NO, YOU DONT NEED HELP!!")
        # EXTREMELY IMPORTANT DONT DELETE
        # self.help()


# 主调函数(防止GUI自启动)
def main():
    root = Tk()
    root.resizable(False, False)
    root.title("LL(1)分析器")
    Gui(root)
    root.mainloop()


if __name__ == '__main__':
    main()
