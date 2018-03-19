#1. set -e
	就是当命令以非零状态退出时，则退出shell。主要作用是，当脚本执行出现意料之外的情况时，立即退出，避免错误被忽略，导致最终结果不正确。
#2. if [ $# -eq 0 ]; then
	$#表示位置参数的数目（对脚本来说，是运行脚本时所带的参数；对函数来说，是函数调用时传入的参数）。
	数值的比较用 -eq ，字符串的比较才用 =
	$1，$2等等分别表示第一个、第二个参数
	$@, $*表示所有的参数
	$#则表示参数的个数
#3. readlink
	获取文件或文件夹的绝对路径，包括文件或文件夹名（readlink -f [file/folder]）
#4. dirname
	获取文件或文件夹的父目录路径(dirname [file/path])
#5. readlink和dirname经常一起组合使用，用于获取文件或文件夹名的绝对路径（不包括文件或文件夹名）(script_path=$(dirname $(readlink -f "$0")))

##6. 脚本中开新终端
	gnome-terminal -x bash -c "roscore;exec bash"  ，双引号中为要执行的命令，多个命令用分号(";")分隔，exec bash表示执行完不关闭终端
