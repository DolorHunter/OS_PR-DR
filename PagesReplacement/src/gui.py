from tkinter import Tk
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
from tkinter import Frame
from tkinter import Button
from tkinter import Label
from tkinter import Text
from tkinter import Entry
from tkinter import sys
from tkinter import StringVar
import tkinter as tk


class MainWindows:
    def __init__(self, master):
        self.timer = 0
        self.pages_replacement = 0
        self.start_style = 0
        self.button_frame = Frame(master)
        self.button_frame.pack()
        self.new_button = Button(self.button_frame, text="新建", command=self.init_all, width=9)
        self.new_button.grid(row=0, column=0)
        self.open_button = Button(self.button_frame, text="打开", command=self.open_file, width=9)
        self.open_button.grid(row=0, column=1)
        self.replay_button = Button(self.button_frame, text="重放", command=self.reply_file, width=9)
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
        self.timer1_button = Button(self.timer_frame, text="按键流逝", command=self.click_timer1, width=23)
        self.timer1_button.grid(row=1, column=1)
        self.timer2_button = Button(self.timer_frame, text="WM_TIMER", command=self.click_timer2, width=23)
        self.timer2_button.grid(row=1, column=2)

        self.replacement_frame = Frame(master)
        self.replacement_frame.pack()
        self.replacement_label = Label(self.replacement_frame, text="置换算法:", width=11)
        self.replacement_label.grid(row=2, column=0, columnspan=1)
        self.replacement1_button = Button(self.replacement_frame, text="FIFO", command=self.click_replacement1, width=11)
        self.replacement1_button.grid(row=2, column=1)
        self.replacement2_button = Button(self.replacement_frame, text="LRU", command=self.click_replacement2, width=10)
        self.replacement2_button.grid(row=2, column=2)
        self.replacement3_button = Button(self.replacement_frame, text="OPT", command=self.click_replacement3, width=11)
        self.replacement3_button.grid(row=2, column=3)
        self.replacement4_button = Button(self.replacement_frame, text="CLOCK", command=self.click_replacement4, width=11)
        self.replacement4_button.grid(row=2, column=4)

        self.pages_frame = Frame(master)
        self.pages_frame.pack()
        self.pages_tree = ttk.Treeview(
            self.pages_frame,
            height=10,
            show="headings"
        )
        self.pages_tree.grid(row=3, column=0, rowspan=1, sticky="NSEW", columnspan=3)
        self.pages_tree["columns"] = "pages_tree"
        self.pages_tree.column("pages_tree", width=180, anchor="center")
        # 表列设置
        self.pages_tree.heading("pages_tree", text="页面置换过程")  # 显示表头
        # 竖直滚动条
        vbar = ttk.Scrollbar(self.pages_frame, orient="horizontal", command=self.pages_tree.yview)
        self.pages_tree.configure(yscrollcommand=vbar.set)
        vbar.grid(row=4, column=0, sticky="NS", columnspan=3)

        self.terminal_frame = Frame(master)
        self.terminal_frame.pack()
        self.terminal_text = self.input_entry = Text(self.pages_frame, width=60, height=10)
        self.terminal_text.grid(row=5, column=0, columnspan=3)

        self.input_frame = Frame(master)
        self.input_frame.pack()
        self.input_label = self.timer_label = Label(self.input_frame, text="$", width=1)
        self.input_label.grid(row=6, column=0)
        self.init_input = StringVar()
        self.input_entry = Entry(self.input_frame, textvariable=self.init_input, width=58)
        self.input_entry.grid(row=6, column=1, columnspan=3)

    def click_timer1(self):
        self.timer1_button['state'] = tk.DISABLED
        self.timer2_button['state'] = tk.NORMAL
        self.timer = 1

    def click_timer2(self):
        self.timer2_button['state'] = tk.DISABLED
        self.timer1_button['state'] = tk.NORMAL
        self.timer = 2

    def click_replacement1(self):
        self.replacement1_button['state'] = tk.DISABLED
        self.replacement2_button['state'] = tk.NORMAL
        self.replacement3_button['state'] = tk.NORMAL
        self.replacement4_button['state'] = tk.NORMAL
        self.pages_replacement = 1

    def click_replacement2(self):
        self.replacement2_button['state'] = tk.DISABLED
        self.replacement1_button['state'] = tk.NORMAL
        self.replacement3_button['state'] = tk.NORMAL
        self.replacement4_button['state'] = tk.NORMAL
        self.pages_replacement = 2

    def click_replacement3(self):
        self.replacement3_button['state'] = tk.DISABLED
        self.replacement1_button['state'] = tk.NORMAL
        self.replacement2_button['state'] = tk.NORMAL
        self.replacement4_button['state'] = tk.NORMAL
        self.pages_replacement = 3

    def click_replacement4(self):
        self.replacement4_button['state'] = tk.DISABLED
        self.replacement1_button['state'] = tk.NORMAL
        self.replacement2_button['state'] = tk.NORMAL
        self.replacement3_button['state'] = tk.NORMAL
        self.pages_replacement = 4

    def init_all(self):
        self.timer = 0
        self.pages_replacement = 0
        self.timer1_button['state'] = tk.NORMAL
        self.timer2_button['state'] = tk.NORMAL
        self.replacement1_button['state'] = tk.NORMAL
        self.replacement2_button['state'] = tk.NORMAL
        self.replacement3_button['state'] = tk.NORMAL
        self.start_style = 0

    def open_file(self):
        init_all()
        self.start_style = 1

    def reply_file(self):
        init_all()
        self.start_style = 2
        
    def show_replacement(self):
        if timer == 1:
            pass
        elif timer == 2:
            pass
        else:
            messagebox.showwarning('时间流逝错误!!', '请选择一个时间流逝方法!!')
            print("[WARNING] TIMER ERROR!!")

    def start(self):
        if self.start_style == 1:
            pass
        elif self.start_style == 2:
            pass
        else:
            messagebox.showwarning('页面置换错误!!', '请选择一个页面置换方法!!')
            print("[WARNING] PAGES REPLACEMENT ERROR!!")
        show_replacement()

    @staticmethod
    def help():
        messagebox.showinfo('需要帮助?', '访问 https://github.com/DolorHunter/??????/issues 以得到帮助!!')
        print("NO, YOU DONT NEED HELP!!")


def main():
    root = Tk()
    root.resizable(False, False)
    root.title("页面置换算法演示")
    MainWindows(root)
    root.mainloop()


if __name__ == '__main__':
    main()
