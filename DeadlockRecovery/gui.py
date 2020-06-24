# -*- coding: utf-8 -*-
from tkinter import Tk
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
from tkinter import *
import tkinter as tk
from ctypes import *

file = CDLL('./src/file.so')
deadlock_recovery = CDLL('./src/deadlockRecovery.so')


class ResourceAllocation(Structure):
    _fields_ = [("proNum", c_int), ("process", c_int * 8), ("resource", c_int * 8),
                ("resApply", c_int * 64), ("resAllocate", c_int * 64), ("relResource", c_int * 8),
                ("relProcess", c_int * 8), ("relProPos", c_int), ("leftProNum", c_int),
                ("resProcess", c_int * 8), ("searchProcess", c_int * 262140), ("seaProPos", c_int)]


class MainWindows:
    def __init__(self, master):
        self.resource_allocation = ResourceAllocation()
        self.filename = ""

        self.button_frame = Frame(master)
        self.button_frame.pack()
        self.new_button = Button(self.button_frame, text="新建", command=self.init_all, width=9)
        self.new_button.grid(row=0, column=0)
        self.open_button = Button(self.button_frame, text="打开", command=self.open_file, width=9)
        self.open_button.grid(row=0, column=1)
        self.start_button = Button(self.button_frame, text="开始", command=self.start, width=9)
        self.start_button.grid(row=0, column=2)
        self.help_button = Button(self.button_frame, text="帮助", command=self.help, width=8)
        self.help_button.grid(row=0, column=3)
        self.quit_button = Button(self.button_frame, text="退出", command=sys.exit, width=8)
        self.quit_button.grid(row=0, column=4)

        self.diagram_frame = Frame(master)
        self.diagram_frame.pack()
        #self.diagram_label = Label(self.diagram_frame, text="前述资源分配图", width=50, height=50)
        #self.diagram_label.grid(row=1, column=0)
        self.diagram_text = Text(self.diagram_frame, width=50, height=10)
        self.diagram_text.grid(row=2, column=0)

        self.search_process_frame = Frame(master)
        self.search_process_frame.pack()
        self.search_process_tree = ttk.Treeview(
            self.search_process_frame,
            height=10,
            show="headings"
        )
        self.search_process_tree.grid(row=3, column=0, columnspan=1, sticky="NSEW")
        pages_slot = ('process', 'resource', 'resApply', 'resAllocate')
        self.search_process_tree["columns"] = pages_slot
        self.search_process_tree.column("process", width=83, anchor="center")
        self.search_process_tree.column("resource", width=83, anchor="center")
        self.search_process_tree.column("resApply", width=83, anchor="center")
        self.search_process_tree.column("resAllocate", width=83, anchor="center")
        # 表列设置
        self.search_process_tree.heading("process", text="搜索进程")  # 显示表头
        self.search_process_tree.heading("resource", text="申请资源")  # 显示表头
        self.search_process_tree.heading("resApply", text="分配资源")  # 显示表头
        self.search_process_tree.heading("resAllocate", text="最佳进程")  # 显示表头
        # 竖直滚动条
        vbar = ttk.Scrollbar(self.search_process_frame, orient="vertical", command=self.search_process_tree.yview)
        self.search_process_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=3, column=1, sticky="NS", columnspan=2)

    def init_search_process_tree(self):
        items = self.search_process_tree.get_children()
        for item in items:
            self.search_process_tree.delete(item)

    def init_all(self):
        self.filename = ""
        self.init_search_process_tree()
        self.diagram_text.delete("1.0", "end")
        deadlock_recovery.initDeadlockRecovery.restype = None
        deadlock_recovery.initDeadlockRecovery.argtypes = [POINTER(ResourceAllocation)]
        deadlock_recovery.initDeadlockRecovery(self.resource_allocation)

    '''
    def show_diagram(self):
        global diagram
        self.filename = str(self.filename)
        diagram_num = self.filename[-1]
        if diagram_num == '1':
            diagram = PhotoImage(file='./data/DIAGRAM1.gif')
            self.diagram_label['image'] = diagram
        elif diagram_num == '2':
            diagram = PhotoImage(file='./data/DIAGRAM2.gif')
            self.diagram_label['image'] = diagram
        elif diagram_num == '3':
            diagram = PhotoImage(file='./data/DIAGRAM3.gif')
            self.diagram_label['image'] = diagram
        else:
            print(diagram_num)
            messagebox.showwarning('错误!!', '图序号非法!!')
        '''

    def show_diagram_file(self):
        values = (self.resource_allocation.proNum, '\n', *self.resource_allocation.process, '\n',
                  *self.resource_allocation.resource, '\n', *self.resource_allocation.resApply, '\n',
                  *self.resource_allocation.resAllocate)
        self.diagram_text.insert(END, values)

    def open_file(self):
        self.filename = filedialog.askopenfile()
        self.filename = self.filename.name
        file.readFile.restype = None
        file.readFile.argtypes = [POINTER(ResourceAllocation), c_char_p]
        c_filename = c_char_p(self.filename.encode('utf-8'))
        file.readFile(self.resource_allocation, c_filename)
        #self.show_diagram()
        self.show_diagram_file()

    def insert_search_process(self):
        search_process = list(self.resource_allocation.searchProcess)
        values = []
        for i in range(len(search_process)):
            if i % 4 == 0 and i != 0:
                if sum(values) == 0:
                    break
                self.search_process_tree.insert("", END, values=values)
                values = []
            values.append(search_process[i])

    def start(self):
        deadlock_recovery.deadlockRecovery.restype = None
        deadlock_recovery.deadlockRecovery.argtypes = [POINTER(ResourceAllocation)]
        deadlock_recovery.deadlockRecovery(self.resource_allocation)
        self.insert_search_process()

    @staticmethod
    def help():
        messagebox.showinfo('需要帮助?', '访问 https://github.com/DolorHunter/OS_PR-DR/issues 以得到帮助!!')
        print("NO, YOU DONT NEED HELP!!")


def main():
    root = Tk()
    root.resizable(False, False)
    root.title("进程死锁的解除")
    MainWindows(root)
    root.mainloop()


if __name__ == '__main__':
    main()
