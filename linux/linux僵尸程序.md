# 一、为什么会产生僵尸程序？
In UNIX System terminology, a process that has terminated,but whose parent has not yet waited for it, is called a zombie.
如果子进程先于父进程退出， 同时父进程又没有调用wait/waitpid，则该子进程将成为僵尸进程。
在fork()/execve()过程中，假设子进程结束时父进程仍存在，而父进程fork()之前既没安装SIGCHLD信号处理函数调用waitpid()等待子进程结束，又没有显式忽略该信号，则子进程成为僵尸进程。