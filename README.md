# OS_DR-PR

[![LICENSE](https://img.shields.io/badge/License-EPL--2.0-green.svg?style=flat-square)](LICENSE)
[![Python](https://img.shields.io/badge/C-99-%23373737.svg?style=flat-square)](https://github.com/DolorHunter/OS_DR-PR/releases)
[![Python](https://img.shields.io/badge/Python-v3.8.3-blue.svg?style=flat-square)](https://github.com/DolorHunter/OS_DR-PR/releases)
[![Tkinter](https://img.shields.io/badge/GUI-Tkinter-yellow.svg?style=flat-square)](https://github.com/DolorHunter/OS_DR-PR/releases)
[![Ctypes](https://img.shields.io/badge/Glue-Ctypes-lightgrey.svg?style=flat-square)](https://github.com/DolorHunter/OS_DR-PR/releases)

__[DeadlockRecovery](#DeadlockRecovery)__ | __[PagesReplacement](#PagesReplacement)__
-|-
__[DR IO](#DR-IO)__ | __[PR 输入](#PR-IO)__
__[DR 演示](#DR-demo)__ | __[PR 演示](#PR-demo)__
__[DR 日志](#DR-log)__ | __[PR 日志](#PR-log)__

## DeadlockRecovery

>14.进程死锁的解除：使用最小生成树算法找到解除死锁的最佳进程序列。（1 人，
难度：3）
>
>- 建立所需数据结构；
>
>- 设计一个复杂的死锁情况，用前述资源分配图文件表示，并进行展示。
>
>- 使用最小生成树算法找到应该逐步撤销的 n 个进程，显示搜索和比较过程
>
>- 给出最后结论，设计 2-3 个复杂的死锁情况用于测试算法的正确性。

### DR IO

输入

```plain
7
1111111
2,3,4,4,4,4,3
0100000,0011100,0111000,1000000,0000021,0000011,0002000
1000000,0110000,0000000,0000100,0000200,0000000,0010001
```

输出

```plain
Resource Allocation Diagram File
proNum:7
process:11111110
resource:23444430
resApply:01000000       00111000        01110000        10000000        00000210        00000110        00020000        00000000
resAllocate:10000000    01100000        00000000        00001000        00002000        00000000        00100010        00000000
ANS = 0365142
Deadlock Recovery Process
0       1       1       0
1       3       2       0
2       3       0       0
3       1       1       0
4       3       2       0
5       2       0       0
6       2       2       0
1       3       2       1
2       3       0       1
3       1       1       3
4       3       2       3
5       2       0       3
6       2       2       3
1       3       2       1
2       3       0       1
4       3       2       1
5       2       0       5
6       2       2       6
1       3       2       1
2       3       0       1
4       3       2       1
5       2       0       5
1       3       2       1
2       3       0       1
4       3       2       1
2       3       0       2
4       3       2       4
2       3       0       2
```

### DR demo

![DR demo](https://res.cloudinary.com/dfb5w2ccj/image/upload/v1593051413/temp/2020-06-25_101554_arxvhe.png)

### DR log

DR历时两天半左右完成. 通过C99制作核心算法, Tkinter(Py)制作GUI. Ctypes(Py)作为胶水, 粘合C99编译后的.so文件与Py3.8. DR在PR后编写, 为第二次的Hybrid Language实践, 因此耗时较短.

时刻表:

- 6.19, 6.22:构思算法框架;
- 6.23~6.24: C主体, 算法, 文件, 部分GUI
- 6.24~6.25: GUI细节处理, Ctypes连接语言, 简单测试

## PagesReplacement

>19.页面置换算法演示。（1 人，难度：3）
>
>- 建立相应的数据结构；
>
>- 在屏幕上显示页面的状况；
>
>- 时间的流逝可用下面几种方法模拟：
>
>   - (a) 按键盘，每按一次可认为过一个时间单位；
>   - (b) 响应 WM_TIMER；
>
>- 将一批页的置换情况存入磁盘文件，以后可以读出并重放；
>
>- 计算页面的缺页次数、缺页后的页面置换次数；
>
>- 支持算法：FIFO、LRU、最佳置换算法、CLOCK。

### PR IO

输入

```plain
5
30968091451014306475316828874031150549644657844764343671234941806341996542150141256154321702935239773127509063703008805198591923823128357738964351070854541596#
```

输出

```plain
3000030000309003096030968309683096810968149681456814568145081450814508145031450364503645036750367503675036710367103671836718267182671826718247182401824038240312403124031540315403154031590315963159641596415964159641596475964789647896478964789647896478364783647836478364783647831478312783127831248312493124931249812498024980649806398063410634196341963419634195341953419524195241952419520195204952041520415204152041620416204165041650416532165321653276532705327053270932709327095270953709537095370953709537095310953129531275312753127091270912709627096370963709637096370963709637096380963809638096385163851938519385193851938519385193851928519235192381923819238192381923819238192385923857238572385723857238579385796857964379643596435164351043510735107851078510784107845078450784517845178451964519
5
790
76
```

### PR demo

![PR demo](https://res.cloudinary.com/dfb5w2ccj/image/upload/v1592041040/temp/2020-06-13_172205_wzm6lj.png)

![PR demo2](https://res.cloudinary.com/dfb5w2ccj/image/upload/v1592041214/temp/2020-06-13_173948_mz7vsv.png)

### PR 日志

PR历时五天完成. 通过C99制作核心算法, Tkinter(Py)制作GUI. Ctypes(Py)作为胶水, 粘合C99编译后的.so文件与Py3.8. PR为第一次混合语言编程, 借助StackOverflow和Py docs的帮助, 编程过程基本还算顺利, 以至于目前甚至产生了C真好用的错觉.

时刻表:

- 6.8~6.11: C主体, 算法, 文件, 部分GUI
- 6.12~6.13: GUI细节处理, Ctypes连接语言, 简单测试
