# coding: utf-8

from tkinter import *
from tkinter import ttk
from tkinter import filedialog
from tkinter import messagebox
import slr1


# 主窗口
class MainWindows:
    def __init__(self, master):
        self.init_input = StringVar()
        # ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        # self.frame为按钮和输入栏的容器
        self.button_frame = Frame(master)
        self.button_frame.pack()
        self.new_button = Button(self.button_frame, text="新建", command=self.init_mainwindows, width=10)
        self.new_button.grid(row=0, column=0)
        self.open_button = Button(self.button_frame, text="打开", command=self.open_file, width=10)
        self.open_button.grid(row=0, column=1)
        self.start_button = Button(self.button_frame, text="开始", command=self.start_analysis, width=10)
        self.start_button.grid(row=0, column=2)
        self.help_button = Button(self.button_frame, text="帮助", command=self.help, width=10)
        self.help_button.grid(row=0, column=3)
        self.quit_button = Button(self.button_frame, text="退出", command=sys.exit, width=10)
        self.quit_button.grid(row=0, column=4)
        # ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        self.input_frame = Frame(master)
        self.input_frame.pack()
        self.input_label = Label(self.input_frame, text="输入串:", width=10)
        self.input_label.grid(row=1, column=0, columnspan=1)
        self.input_entry = Entry(self.input_frame, textvariable=self.init_input, state=NORMAL, width=45)
        self.input_entry.grid(row=1, column=1, columnspan=4)
        self.init_input.set('i+i*i#')  # 初始输入串'
        # ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        # self.info_frame为文法, 扩广文法的容器
        self.info_frame = Frame(master)
        self.info_frame.pack()
        # 实例化输入的文法
        self.grammar_tree = ttk.Treeview(
            self.info_frame,
            height=7,
            show="headings",  # 隐藏首列
        )
        self.grammar_tree.grid(row=0, column=0, columnspan=1, sticky="NSEW")
        # 表头设置
        self.grammar_tree["columns"] = "grammar_tree"
        self.grammar_tree.column("grammar_tree", width=180, anchor="center")  # 表示列,不显示
        # 表列设置
        self.grammar_tree.heading("grammar_tree", text="文法表")  # 显示表头
        # 竖直滚动条
        vbar = ttk.Scrollbar(self.info_frame, orient="vertical", command=self.grammar_tree.yview)
        self.grammar_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=0, column=1, sticky="NS")
        # --------------------------------------------------------------------------------------------------------------
        # 实例化拓广文法
        self.extended_grammar_tree = ttk.Treeview(
            self.info_frame,
            height=7,
            show="headings",  # 隐藏首列
        )
        self.extended_grammar_tree.grid(row=0, column=2, columnspan=1, sticky="NSEW")
        # 表头设置
        self.extended_grammar_tree["columns"] = "extended_grammar_tree"
        self.extended_grammar_tree.column("extended_grammar_tree", width=180, anchor="center")  # 表示列,不显示
        # 表列设置
        self.extended_grammar_tree.heading("extended_grammar_tree", text="拓广文法表")  # 显示表头
        # 竖直滚动条
        vbar = ttk.Scrollbar(self.info_frame, orient="vertical", command=self.extended_grammar_tree.yview)
        self.extended_grammar_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=0, column=3, sticky="NS")
        # ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        # self.collections_frame为文法项目, 项目集族的容器
        self.collections_frame = Frame(master)
        self.collections_frame.pack()
        # 实例化项目
        self.collections_tree = ttk.Treeview(
            self.collections_frame,
            height=13,
            show="headings",  # 隐藏首列
        )
        self.collections_tree.grid(row=0, column=0, columnspan=1, sticky="NSEW")
        # 表头设置
        self.collections_tree["columns"] = ("sequence", "collections_tree")
        self.collections_tree.column("sequence", width=45, anchor="center")  # 序号列
        self.collections_tree.column("collections_tree", width=135, anchor="center")  # 项目列
        # 表列设置
        self.collections_tree.heading("sequence", text="序号")
        self.collections_tree.heading("collections_tree", text="项目")
        # 竖直滚动条
        vbar = ttk.Scrollbar(self.collections_frame, orient="vertical", command=self.collections_tree.yview)
        self.collections_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=0, column=1, sticky="NS")
        # --------------------------------------------------------------------------------------------------------------
        # 实例化项目集规范族
        self.canonical_collections_tree = ttk.Treeview(
            self.collections_frame,
            height=13,
            show="headings",  # 隐藏首列
        )
        self.canonical_collections_tree.grid(row=0, column=2, columnspan=1, sticky="NSEW")
        # 表头设置
        self.canonical_collections_tree["columns"] = ("sequence", "canonical_collections_tree")
        self.canonical_collections_tree.column("sequence", width=45, anchor="center")  # 序号列
        self.canonical_collections_tree.column("canonical_collections_tree", width=135, anchor="center")  # 项目列
        # 表列设置
        self.canonical_collections_tree.heading("sequence", text="状态")
        self.canonical_collections_tree.heading("canonical_collections_tree", text="项目集族")
        # 竖直滚动条
        vbar = ttk.Scrollbar(self.collections_frame, orient="vertical", command=self.canonical_collections_tree.yview)
        self.canonical_collections_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=0, column=3, sticky="NS")

    # 初始化输入框
    def init_entry(self):
        self.input_entry.delete(0, END)  # 清空输入串

    # 初始化语法树
    def init_grammar(self):
        items = self.grammar_tree.get_children()
        for item in items:
            self.grammar_tree.delete(item)  # 删除子树

    # 初始化拓广语法树
    def init_extension_tree(self):
        items = self.extended_grammar_tree.get_children()
        for item in items:
            self.extended_grammar_tree.delete(item)  # 删除子树

    # 初始化项目集树
    def init_collections_tree(self):
        items = self.collections_tree.get_children()
        for item in items:
            self.collections_tree.delete(item)  # 删除子树

    # 初始化项目集规范族树
    def init_canonical_collections_tree(self):
        items = self.canonical_collections_tree.get_children()
        for item in items:
            self.canonical_collections_tree.delete(item)  # 删除子树

    # 初始化主窗口
    def init_mainwindows(self):
        slr1.init_list()  # 初始化列表
        self.init_entry()  # 初始化输入框
        self.init_grammar()  # 初始化语法树
        self.init_extension_tree()  # 初始化拓广语法树
        self.init_collections_tree()  # 初始化项目集树
        self.init_canonical_collections_tree()  # 初始化项目集规范族树
        print("Delete all the input info(including grammar) successfully!!")

    # 获得输入串
    def get_input_string(self):
        return self.input_entry.get()

    # 展示文法
    def show_grammar(self):
        for gram in slr1.grams:
            self.grammar_tree.insert("", END, values=gram)  # 打印文法
        slr1.pre_process()  # 文法预处理(提取, 拓广, 简化)
        for extend_gram in slr1.grams:
            self.extended_grammar_tree.insert("", END, values=extend_gram)  # 打印拓广后的文法

    # 展示项目集
    def show_collections(self):
        slr1.create_collections()  # 构造项目集
        i = 0
        for collection in slr1.collections:
            self.collections_tree.insert("", END, values=(i, collection))
            i += 1

    # 展示项目集族
    def show_canonical_collections(self):
        slr1.create_canonical_collections()  # 构造项目集族
        for collection in slr1.canonical_collections:
            for c in collection[1]:
                self.canonical_collections_tree.insert("", END, values=(collection[0], c))

    # 打开分析表
    @staticmethod
    def open_analysis_list():
        if not slr1.create_analysis_list():  # 生成分析表(如果不是SLR(1)文法)
            messagebox.showerror('文法错误!!', '文法不是SLR(1)文法!!')
        else:  # 是slr1文法
            alw = Tk()
            alw.resizable(False, False)
            alw.title('SLR(1)分析表')
            AnalysisListWindows(alw)
            alw.mainloop()

    # 打开分析过程
    def open_analysis_process(self):
        slr1.analysis_input_string(self.get_input_string())  # 分析文法
        apw = Tk()
        apw.resizable(False, False)
        apw.title('SLR(1)分析过程')
        AnalysisProcessWindows(apw)
        apw.mainloop()

    # 打开文件导入语法
    def open_file(self):
        filename = filedialog.askopenfile()
        print("Open the file successfully!!")
        slr1.create_grammar_list(filename.name)
        self.show_grammar()  # 展示语法
        self.show_collections()  # 展示项目
        self.show_canonical_collections()  # 展示项目集族
        self.open_analysis_list()  # 打开生成表

    # 开始分析
    def start_analysis(self):
        if len(slr1.grams) == 0 or len(self.get_input_string()) == 0:  # 文法表空或输入串空
            if len(slr1.grams) == 0:  # 文法表空
                messagebox.showerror('文法错误!!', '请先打开一个文法以开始分析!!')
                print("[ERROR] PLEASE OPEN A GRAMMAR FIRST!!")
            if len(self.get_input_string()) == 0:
                messagebox.showerror('输入错误!!', '请输入一个输入串以开始分析!!')
                print("[ERROR] PLEASE INPUT A STRING FIRST!!")
        else:  # 开始文法分析
            self.open_analysis_process()  # 打开分析表

        print("Analysis running successfully!!")

    # 帮助
    @staticmethod
    def help():
        messagebox.showinfo('需要帮助?', '访问 https://github.com/DolorHunter/CompilerTheory_exp/issues 以得到帮助!!')
        print("NO, YOU DONT NEED HELP!!")
        # EXTREMELY IMPORTANT DONT DELETE
        # self.help()


# 分析表窗口
class AnalysisListWindows:
    def __init__(self, master):
        # ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        # self.label_frame为标签容器
        self.label_frame = Frame(master)
        self.label_frame.pack()
        self.status_label = Label(self.label_frame, text='STATUS', width=10).grid(row=0, column=0)
        self.actions_label = Label(self.label_frame, text='ACTION', width=35).grid(row=0, column=1)
        self.goto_label = Label(self.label_frame, text='GOTO', width=25).grid(row=0, column=2)
        # ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        # self.analysis_list_frame为分析表的容器
        self.analysis_list_frame = Frame(master)
        self.analysis_list_frame.pack()
        # 实例化分析表
        self.analysis_list_tree = ttk.Treeview(
            self.analysis_list_frame,
            height=12,
            show="headings",  # 隐藏首列
        )
        self.analysis_list_tree.grid(row=0, column=0, columnspan=1, sticky="NSEW")
        # 垂直滚动条
        vbar = ttk.Scrollbar(self.analysis_list_frame, orient="vertical", command=self.analysis_list_tree.yview)
        self.analysis_list_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=0, column=1, sticky="NS")
        # 表头设置
        heading = ['Status']
        for action in slr1.action_heading:
            heading.append(action)
        for goto in slr1.goto_heading:
            heading.append(goto)
        self.analysis_list_tree["columns"] = heading
        self.analysis_list_tree.column("Status", width=50, anchor="center")  # 表示列,不显示
        for action in slr1.action_heading:
            self.analysis_list_tree.column(action, width=50, anchor="center")
        for goto in slr1.goto_heading:
            self.analysis_list_tree.column(goto, width=50, anchor="center")
        # 表列设置
        self.analysis_list_tree.heading("Status", text="Status")  # 显示表头
        for action in slr1.action_heading:
            self.analysis_list_tree.heading(action, text=action)
        for goto in slr1.goto_heading:
            self.analysis_list_tree.heading(goto, text=goto)

        self.show_analysis_list()  # 展示分析表数据

    # 展示分析表数据
    def show_analysis_list(self):
        for c_c in slr1.canonical_collections:
            values = [c_c[0]]
            for col in range(len(slr1.action_heading)):
                values.append(slr1.action[c_c[0] + 1][col])
            for col in range(len(slr1.goto_heading)):
                values.append(slr1.goto[c_c[0] + 1][col])
            self.analysis_list_tree.insert("", END, values=values)


# 分析过程窗口
class AnalysisProcessWindows:
    def __init__(self, master):
        # self.analysis_process_frame为分析过程容器
        self.analysis_process_frame = Frame(master)
        self.analysis_process_frame.pack()
        # 实例化分析表
        self.analysis_process_tree = ttk.Treeview(
            self.analysis_process_frame,
            height=15,
            show="headings",  # 隐藏首列
        )
        self.analysis_process_tree.grid(row=0, column=0, columnspan=1, sticky="NSEW")
        # 垂直滚动条
        vbar = ttk.Scrollbar(self.analysis_process_frame, orient="vertical", command=self.analysis_process_tree.yview)
        self.analysis_process_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=0, column=1, sticky="NS")
        # 表头设置
        self.analysis_process_tree["columns"] = ('steps', 'status_stack', 'symbol_stack', 'input_string', 'actions')
        self.analysis_process_tree.column("steps", width=65, anchor="center")  # 表示列,不显示
        self.analysis_process_tree.column("status_stack", width=90)  # 表示列,不显示
        self.analysis_process_tree.column("symbol_stack", width=75)  # 表示列,不显示
        self.analysis_process_tree.column("input_string", width=75, anchor="e")  # 表示列,不显示
        self.analysis_process_tree.column("actions", width=230, anchor="center")  # 表示列,不显示
        # 表列设置
        self.analysis_process_tree.heading("steps", text="步骤")
        self.analysis_process_tree.heading("status_stack", text="状态栈")
        self.analysis_process_tree.heading("symbol_stack", text="符号栈")
        self.analysis_process_tree.heading("input_string", text="输入串")
        self.analysis_process_tree.heading("actions", text="动作说明")
        # 垂直滚动条
        vbar = ttk.Scrollbar(self.analysis_process_frame, orient="vertical", command=self.analysis_process_tree.yview)
        self.analysis_process_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=0, column=1, sticky="NS")

        self.show_analysis_process()  # 展示分析过程

    # 展示分析过程
    def show_analysis_process(self):
        for i in range(len(slr1.step_list)):
            values = (slr1.step_list[i], slr1.status_stack_list[i], slr1.symbol_stack_list[i],
                      slr1.input_string_list[i], slr1.action_list[i])
            self.analysis_process_tree.insert("", END, values=values)


# 主调函数
def main():
    root = Tk()
    root.resizable(False, False)
    root.title("SLR(1)分析器")
    MainWindows(root)
    root.mainloop()


if __name__ == '__main__':
    main()
