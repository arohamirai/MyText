 # [matlab程序转换成c/c++可调用的库](https://ww2.mathworks.cn/help/compiler_sdk/gs/create-a-cc-mwarray-application.html#mw_ea0236b3-41e4-4f47-9a18-f989969c3834)

1. [VS调试时报访问内存错误解决方法](https://blog.csdn.net/andy_5826_liu/article/details/84985766)

   c++中调用matlab初始化时，出现异常：0xc0000005:读取位0x0000000000000008 时发生访问冲突,针对这一问题，因为我们是64位，只需要在异常设置中取消勾选Win32 Exceptions即可。ps: Win32 Exceptions项在vs调试-->窗口-->异常设置中（快捷键Ctrl + Alt + E）

2. 推荐使用MATLAB Data API，这个api支持c++11，而mwArray API 只支持c++03;

3. [MATLAB Data API的使用方法](https://ww2.mathworks.cn/help/compiler_sdk/cxx/writing-c-driver-code-using-the-generic-interface.html)

   

