'''
python的解释特性是将py编译为独有的二进制编码pyc文件，然后对pyc中的指令进行解释执行，但是pyc的反编译却非常简单，可直接反编译为源码，当需要将产品发布到外部环境的时候，源码的保护尤为重要.
'''
思路：思路是先将py转换为c代码，然后编译c为so文件
准备：pip install cython

1. 在testmode文件夹下分别创建test.py 和setup.py,填入相关内容
2. 打开终端
     $cd testmode
     $python setup.py build_ext    # --inplace
   生成test.c文件和build目录
   且build下生成目录：lib.linux-x86_64-3.6
			test.cpython-36m-x86_64-linux-gnu.so	
		　　　lib.linux-x86_64-3.6		　
		　　　　　　　　test.o


    or
      $cython test.py
      $gcc -c -fPIC -I/usr/include/python2.7/ test.c
      $gcc -shared test.o -o test.so
３. 现在so文件就可以像普通py文件一样导入了
     $cd build/lib.linux-x86_64-3.6
     $python
     >>import test
     >>test.aa   

