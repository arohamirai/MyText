# 零、 概述：
Valgrind是用于构建动态分析工具的**探测框架**。它包括一个工具集，每个工具执行某种类型的调试、分析或类似的任务，以帮助完善你的程序。Valgrind的架构是模块化的，所以可以容易地创建新的工具而又不会扰乱现有的结构。
# 一、 工具

## 1. Memcheck
Memcheck是一个内存错误检测器。它有助于使你的程序，尤其是那些用C和C++写的程序，更加准确。
```
valgrind --tool=memcheck --leak-check=full ./a.out
```
该工具可以检测下列与内存相关的问题 :
* 未释放内存的使用
* 对释放后内存的读/写
* 对已分配内存块尾部的读/写
* 内存泄露
* 不匹配的使用malloc/new/new[] 和 free/delete/delete[]
* 重复释放内存

## 2. Cachegrind
Cachegrind 是一个缓存和分支预测分析器。它有助于使你的程序运行更快。

## 3. Callgrind
Callgrind是一个调用图缓存生成分析器。它与Cachegrind的功能有重叠，但也收集Cachegrind不收集的一些信息。
## 4. Helgrind
Helgrind是一个线程错误检测器。它有助于使你的多线程程序更加准确。
## 5. DRD
DRD也是一个线程错误检测器。它和Helgrind相似，但使用不同的分析技术，所以可能找到不同的问题。
## 6. Massif
Massif是一个堆分析器。它有助于使你的程序使用更少的内存。
## 7. DHAT
DHAT是另一种不同的堆分析器。它有助于理解块的生命期、块的使用和布局的低效等问题。
## 8. SGcheck
SGcheck是一个实验工具，用来检测堆和全局数组的溢出。它的功能和Memcheck互补：SGcheck找到Memcheck无法找到的问题，反之亦然。


