# -*- coding: utf-8 -*-
from tkinter import Tk
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
from tkinter import *
import tkinter as tk
from ctypes import *
import datetime
import threading

file = CDLL('./src/file.so')
pages_replacement = CDLL('./src/pagesReplacement.so')


class Pages(Structure):
    _fields_ = [("capacity", c_int), ("load", c_int), ("page", c_char * 8),
                ("pagePointer", c_int), ("pageTime", c_int * 8), ("postPageTime", c_int * 8)]


class PagesHistory(Structure):
    _fields_ = [("capacity", c_int), ("loc", c_int), ("missTime", c_int), ("history", c_char * 2048)]


class Info(Structure):
    _fields_ = [("pageSize", c_int), ("pageInfo", c_char * 256)]


class MainWindows:
    def __init__(self, master):
        self.pages = Pages()
        self.pages_history = PagesHistory()
        self.info = Info()
        self.time = 0
        self.case_timer = 0
        self.case_pages_replacement = 0
        self.start_style = 0
        self.replacement_column = 0
        self.filename = ""

        self.button_frame = Frame(master)
        self.button_frame.pack()
        self.new_button = Button(self.button_frame, text="新建", command=self.init_all, width=9)
        self.new_button.grid(row=0, column=0)
        self.open_button = Button(self.button_frame, text="打开", command=self.open_file, width=9)
        self.open_button.grid(row=0, column=1)
        self.replay_button = Button(self.button_frame, text="重放", command=self.replay_file, width=9)
        self.replay_button.grid(row=0, column=2)
        self.start_button = Button(self.button_frame, text="开始", command=self.start, width=9)
        self.start_button.grid(row=0, column=3)
        self.help_button = Button(self.button_frame, text="帮助", command=self.help, width=8)
        self.help_button.grid(row=0, column=4)
        self.quit_button = Button(self.button_frame, text="退出", command=sys.exit, width=8)
        self.quit_button.grid(row=0, column=5)

        self.timer_frame = Frame(master)
        self.timer_frame.pack()
        self.timer_label = Label(self.timer_frame, text="时间流逝:", width=11)
        self.timer_label.grid(row=1, column=0)
        self.timer1_button = Button(self.timer_frame, text="按键流逝",
                                    command=self.click_timer1, width=23)
        self.timer1_button.grid(row=1, column=1)
        self.timer2_button = Button(self.timer_frame, text="WM_TIMER",
                                    command=self.click_timer2, width=23)
        self.timer2_button.grid(row=1, column=2)

        self.replacement_frame = Frame(master)
        self.replacement_frame.pack()
        self.replacement_label = Label(self.replacement_frame, text="置换算法:", width=11)
        self.replacement_label.grid(row=2, column=0, columnspan=1)
        self.replacement1_button = Button(self.replacement_frame,
                                          text="FIFO", command=self.click_replacement1, width=11)
        self.replacement1_button.grid(row=2, column=1)
        self.replacement2_button = Button(self.replacement_frame,
                                          text="LRU", command=self.click_replacement2, width=10)
        self.replacement2_button.grid(row=2, column=2)
        self.replacement3_button = Button(self.replacement_frame,
                                          text="OPT", command=self.click_replacement3, width=11)
        self.replacement3_button.grid(row=2, column=3)
        self.replacement4_button = Button(self.replacement_frame,
                                          text="CLOCK", command=self.click_replacement4, width=11)
        self.replacement4_button.grid(row=2, column=4)

        self.pages_frame = Frame(master)
        self.pages_frame.pack()
        self.pages_tree = ttk.Treeview(
            self.pages_frame,
            height=10,
            show="headings"
        )
        self.pages_tree.grid(row=3, column=0, columnspan=1, sticky="NSEW")
        pages_slot = ('p1', 'p2', 'p3', 'p4', 'p5', 'p6', 'p7', 'p8')
        self.pages_tree["columns"] = pages_slot
        self.pages_tree.column("p1", width=50, anchor="center")
        self.pages_tree.column("p2", width=50, anchor="center")
        self.pages_tree.column("p3", width=50, anchor="center")
        self.pages_tree.column("p4", width=50, anchor="center")
        self.pages_tree.column("p5", width=50, anchor="center")
        self.pages_tree.column("p6", width=50, anchor="center")
        self.pages_tree.column("p7", width=50, anchor="center")
        self.pages_tree.column("p8", width=50, anchor="center")
        # 表列设置
        self.pages_tree.heading("p1", text="p1槽")  # 显示表头
        self.pages_tree.heading("p2", text="p2槽")  # 显示表头
        self.pages_tree.heading("p3", text="p3槽")  # 显示表头
        self.pages_tree.heading("p4", text="p4槽")  # 显示表头
        self.pages_tree.heading("p5", text="p5槽")  # 显示表头
        self.pages_tree.heading("p6", text="p6槽")  # 显示表头
        self.pages_tree.heading("p7", text="p7槽")  # 显示表头
        self.pages_tree.heading("p8", text="p8槽")  # 显示表头
        # 竖直滚动条
        vbar = ttk.Scrollbar(self.pages_frame, orient="vertical", command=self.pages_tree.yview)
        self.pages_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=3, column=1, sticky="NS", columnspan=2)

        self.terminal_frame = Frame(master)
        self.terminal_frame.pack()
        self.terminal_text = self.input_entry = Text(self.pages_frame, width=60, height=10)
        self.terminal_text.grid(row=4, column=0, columnspan=2)
        self.terminal_text.see(END)

        self.input_frame = Frame(master)
        self.input_frame.pack()
        self.input_label = Label(self.input_frame, text="$", width=1)
        self.input_label.grid(row=5, column=0)
        self.init_input = StringVar()
        self.input_entry = Entry(self.input_frame, textvariable=self.init_input, width=53)
        self.input_entry.grid(row=5, column=1)
        self.enter_button = Button(self.input_frame, text="Enter", command=self.click_enter, width=4)
        self.enter_button.grid(row=5, column=2)

    def click_timer1(self):
        self.timer1_button['state'] = tk.DISABLED
        self.timer2_button['state'] = tk.NORMAL
        self.case_timer = 1
        cur_dt = datetime.datetime.now()
        cur_time = "[{:2d}:{:2d}:{:2d}]".format(cur_dt.hour, cur_dt.minute, cur_dt.second)
        self.terminal_text.insert(END, cur_time + "Timer Algo: Typing Enter\n")
        self.terminal_text.see(END)

    def click_timer2(self):
        self.timer2_button['state'] = tk.DISABLED
        self.timer1_button['state'] = tk.NORMAL
        self.case_timer = 2
        cur_dt = datetime.datetime.now()
        cur_time = "[{:2d}:{:2d}:{:2d}]".format(cur_dt.hour, cur_dt.minute, cur_dt.second)
        self.terminal_text.insert(END, cur_time + "Timer Algo: WM_WAVER\n")
        self.terminal_text.see(END)

    def click_replacement1(self):
        self.replacement1_button['state'] = tk.DISABLED
        self.replacement2_button['state'] = tk.NORMAL
        self.replacement3_button['state'] = tk.NORMAL
        self.replacement4_button['state'] = tk.NORMAL
        self.case_pages_replacement = 1
        cur_dt = datetime.datetime.now()
        cur_time = "[{:2d}:{:2d}:{:2d}]".format(cur_dt.hour, cur_dt.minute, cur_dt.second)
        self.terminal_text.insert(END, cur_time + "PagesReplacement Algo: FIFO\n")
        self.terminal_text.see(END)

    def click_replacement2(self):
        self.replacement2_button['state'] = tk.DISABLED
        self.replacement1_button['state'] = tk.NORMAL
        self.replacement3_button['state'] = tk.NORMAL
        self.replacement4_button['state'] = tk.NORMAL
        self.case_pages_replacement = 2
        cur_dt = datetime.datetime.now()
        cur_time = "[{:2d}:{:2d}:{:2d}]".format(cur_dt.hour, cur_dt.minute, cur_dt.second)
        self.terminal_text.insert(END, cur_time + "PagesReplacement Algo: LRU\n")
        self.terminal_text.see(END)

    def click_replacement3(self):
        self.replacement3_button['state'] = tk.DISABLED
        self.replacement1_button['state'] = tk.NORMAL
        self.replacement2_button['state'] = tk.NORMAL
        self.replacement4_button['state'] = tk.NORMAL
        self.case_pages_replacement = 3
        cur_dt = datetime.datetime.now()
        cur_time = "[{:2d}:{:2d}:{:2d}]".format(cur_dt.hour, cur_dt.minute, cur_dt.second)
        self.terminal_text.insert(END, cur_time + "PagesReplacement Algo: OPT\n")
        self.terminal_text.see(END)

    def click_replacement4(self):
        self.replacement4_button['state'] = tk.DISABLED
        self.replacement1_button['state'] = tk.NORMAL
        self.replacement2_button['state'] = tk.NORMAL
        self.replacement3_button['state'] = tk.NORMAL
        self.case_pages_replacement = 4
        cur_dt = datetime.datetime.now()
        cur_time = "[{:2d}:{:2d}:{:2d}]".format(cur_dt.hour, cur_dt.minute, cur_dt.second)
        self.terminal_text.insert(END, cur_time + "PagesReplacement Algo: CLOCK\n")
        self.terminal_text.see(END)

    def init_pages_tree(self):
        items = self.pages_tree.get_children()
        for item in items:
            self.pages_tree.delete(item)

    def init_all(self):
        self.time = 0
        self.case_timer = 0
        self.case_pages_replacement = 0
        self.timer1_button['state'] = tk.NORMAL
        self.timer2_button['state'] = tk.NORMAL
        self.replacement1_button['state'] = tk.NORMAL
        self.replacement2_button['state'] = tk.NORMAL
        self.replacement3_button['state'] = tk.NORMAL
        self.replacement4_button['state'] = tk.NORMAL
        self.enter_button['state'] = NORMAL
        self.start_style = 0
        self.replacement_column = 0
        self.filename = ""
        self.init_pages_tree()
        self.terminal_text.delete("1.0", "end")
        self.pages = Pages()
        self.pages_history = PagesHistory()
        self.info = Info()

    def pick_replacement(self):
        cur_dt = datetime.datetime.now()
        cur_time = "[{:2d}:{:2d}:{:2d}]".format(cur_dt.hour, cur_dt.minute, cur_dt.second)
        self.terminal_text.insert(END, cur_time + "******PagesReplacement Algo******\n")
        self.terminal_text.insert(END, cur_time + "(1) FIFO\n")
        self.terminal_text.insert(END, cur_time + "(2) LRU\n")
        self.terminal_text.insert(END, cur_time + "(3) OPT\n")
        self.terminal_text.insert(END, cur_time + "(4) CLOCK\n")
        self.terminal_text.insert(END, cur_time + "Push the Button above.\n")
        self.terminal_text.see(END)

    def pick_timer(self):
        cur_dt = datetime.datetime.now()
        cur_time = "[{:2d}:{:2d}:{:2d}]".format(cur_dt.hour, cur_dt.minute, cur_dt.second)
        self.terminal_text.insert(END, cur_time + "******Timer Algo******\n")
        self.terminal_text.insert(END, cur_time + "(1) TYPING ENTER\n")
        self.terminal_text.insert(END, cur_time + "(2) WM_WAVER\n")
        self.terminal_text.insert(END, cur_time + "Push the Button above.\n")
        self.terminal_text.see(END)

    def open_file(self):
        self.start_style = 1
        self.pick_replacement()
        self.pick_timer()
        self.filename = filedialog.askopenfile()
        self.filename = self.filename.name
        file.readFile.restype = None
        file.readFile.argtypes = [POINTER(Info), c_char_p]
        c_filename = c_char_p(self.filename.encode('utf-8'))
        file.readFile(self.info, c_filename)
        pages_replacement.init_pages.restype = None
        pages_replacement.init_pages.argtypes = [POINTER(Pages), POINTER(Info), POINTER(PagesHistory)]
        pages_replacement.init_pages(self.pages, self.info, self.pages_history)

    def replay_file(self):
        self.start_style = 2
        self.replacement1_button['state'] = tk.DISABLED
        self.replacement2_button['state'] = tk.DISABLED
        self.replacement3_button['state'] = tk.DISABLED
        self.replacement4_button['state'] = tk.DISABLED
        self.pick_timer()
        self.filename = filedialog.askopenfile()
        self.filename = self.filename.name
        file.readReplayFile.restype = None
        file.readReplayFile.argtypes = [POINTER(PagesHistory), c_char_p]
        c_filename = c_char_p(self.filename.encode('utf-8'))
        file.readReplayFile(self.pages_history, c_filename)

    def click_enter(self):
        if self.pages_history.capacity:
            page_num = int(self.pages_history.loc / self.pages_history.capacity)
            if self.time + 1 >= page_num > 0:
                self.enter_button['state'] = DISABLED
                page_num = int(self.pages_history.loc / self.pages_history.capacity)
                miss_rate = self.pages_history.missTime / page_num
                messagebox.showinfo('页面置换完成',
                                    '页面置换次数{}, 缺页次数{}, 缺页率{:.3f}'.format(page_num,
                                                                         self.pages_history.missTime,
                                                                         miss_rate))
        input_command = self.input_entry.get()
        cur_dt = datetime.datetime.now()
        cur_time = "[{:2d}:{:2d}:{:2d}]".format(cur_dt.hour, cur_dt.minute, cur_dt.second)
        self.terminal_text.insert(END, cur_time + "$" + input_command + "\n")
        self.terminal_text.see(END)
        self.input_entry.delete(0, END)
        self.insert_replacement()
        self.time += 1

    def insert_replacement(self):
        values = []
        capacity = self.pages_history.capacity
        str_history = str(self.pages_history.history)
        str_history = str_history[2:-3]
        for i in range(capacity):
            elem = str_history[capacity * self.time + i]
            values.extend(elem)
        self.pages_tree.insert("", 0, values=values)

    def my_timer2(self):
        page_num = 0
        if self.pages_history.capacity:
            page_num = int(self.pages_history.loc / self.pages_history.capacity)
        if page_num > self.time:
            timer_2 = threading.Timer(1, self.my_timer2)
            self.insert_replacement()
            self.time += 1
            timer_2.start()
        else:
            miss_rate = self.pages_history.missTime / page_num
            messagebox.showinfo('页面置换完成',
                                '页面置换次数{}, 缺页次数{}, 缺页率{:.3f}'.format(page_num,
                                                                     self.pages_history.missTime,
                                                                     miss_rate))

    def my_timer(self):
        if self.case_timer < 1 or self.case_timer > 2:
            messagebox.showwarning('时间流逝错误!!', '请选择一个时间流逝方法!!')
            print("[WARNING] TIMER ERROR!!")
        elif self.case_timer == 2:
            self.my_timer2()
        elif self.case_timer == 1:
            # 按下Enter输出, 操作置于 self.click_enter()
            pass

    def start(self):
        if self.start_style == 1:
            if self.case_pages_replacement < 1 or self.case_pages_replacement > 4:
                messagebox.showwarning('页面置换算法错误!!', '请选择一个页面置换算法!!')
                print("[WARNING] PAGES REPLACEMENT ALGO ERROR!!")
            else:
                pages_replacement.chooseReplacement.restype = None
                pages_replacement.chooseReplacement.argtypes = [c_int, POINTER(Pages), POINTER(Info),
                                                                POINTER(PagesHistory)]
                pages_replacement.chooseReplacement(self.case_pages_replacement,
                                                    self.pages, self.info, self.pages_history)
                file.saveFile.restype = None
                file.saveFile.argtypes = [POINTER(PagesHistory), c_char_p]
                c_filename = c_char_p(self.filename.encode('utf-8'))
                file.saveFile(self.pages_history, c_filename)
                file.readReplayFile.restype = None
                file.readReplayFile.argtypes = [POINTER(PagesHistory), c_char_p]
                c_filename = c_char_p((self.filename + "_REPLAY").encode("utf-8"))
                file.readReplayFile(self.pages_history, c_filename)
                self.my_timer()
        elif self.start_style == 2:
            self.my_timer()
        else:
            messagebox.showwarning('页面置换演示错误!!', '请选择一个页面置换演示方式!!')
            print("[WARNING] PAGES REPLACEMENT ERROR!!")

    @staticmethod
    def help():
        messagebox.showinfo('需要帮助?', '访问 https://github.com/DolorHunter/OS_PR-DR/issues 以得到帮助!!')
        print("NO, YOU DONT NEED HELP!!")


def main():
    root = Tk()
    root.resizable(False, False)
    root.title("页面置换算法演示")
    MainWindows(root)
    root.mainloop()


if __name__ == '__main__':
    main()
