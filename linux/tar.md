基本格式：tar [Options] file_archive　　//注意tar的第一参数必须为命令选项，即不能直接接待处理文件
常用命令参数：
	//指定tar进行的操作，以下三个选项不能出现在同一条命令中
	-c　　　　　　　　//创建一个新的打包文件(archive)
	-x　　　　　　　　//对打包文件(archive)进行解压操作
	-t　　　　　　　　//查看打包文件(archive)的内容,主要是构成打包文件(archive)的文件名

//指定支持的压缩/解压方式，操作取决于前面的参数，若为创建(-c),则进行压缩，若为解压(-x),则进行解压，不加下列参数时，则为单纯的打包操作
	-z　　　　　　　　//使用gzip进行压缩/解压，一般使用.tar.gz后缀
	-j　　　　　　　　//使用bzip2进行压缩/解压，一般使用.tar.bz2后缀

//指定tar指令使用的文件，若没有压缩操作，则以.tar作为后缀
	-f filename　　 //-f后面接操作使用的文件，用空格隔开，且中间不能有其他参数，推荐放在参数集最后或单独作为参数
　　　　　　　　　//文件作用取决于前面的参数，若为创建(-c),则-f后为创建的文件的名字(路径)，若为(-x/t),则-f后为待解压/查看的打包压缩文件名

//其他辅助选项
	-v　　　　　　　　//详细显示正在处理的文件名
	-C Dir　　　　　 //将解压文件放置在 -C 指定的目录下
	-p(小写)　　　　 //保留文件的权限和属性，在备份文件时较有用
	-P(大写)　　　　 //保留原文件的绝对路径，即不会拿掉文件路径开始的根目录
	--exclude=file 	//排除不进行打包的文件