window在session里，可以有N个window，并且window可以在不同的session里移动
c			创建window
&			删除window
n			下一个window
p			上一个window
,			重命名window 
f			在多个window里搜索关键字
l			在相邻的两个window里切换(L)

pane在window里，可以有N个pane，并且pane可以在不同的window里移动、合并、拆分

”			创建横切split pane
%			创建竖切split pane
o			按顺序在pane之间移动
{			在同一个window里左右移动pane：往左边，往上面
} 			在同一个window里左右移动pane：往右边，往下面

方向键		上下左右选择pane
x			删除pane
“空格”		更换pane排版
!			移动pane至window
q			显示pane编号
Ctrl+o		按顺序移动pane位置
[			空格标记复制开始，回车结束复制。
]			粘贴最后一个缓冲区内容
=			选择性粘贴缓冲区
t			显示时间
?			快捷键帮助

:resize-pane -U	[num]	调整pane的大小	#向上移动[num]
:resize-pane -D [num]					#向下移动[num]
:resize-pane -L [num]					#向左移动[num]
:resize-pane -R [num]					#向右移动[num]


:list-buffer						列出缓冲区目标
:show-buffer						查看缓冲区内容
:join-pane -t $window_name			移动pane合并至某个window
:list-commands						tmux内置命令帮助

session是会话，会话下面会开window，window下面开pane，session可以断开连接，但session创建的window/pane都会保留，下次再次连上这个会话就可以继续作业
tmux new -s backupsession			创建名为backupsession的session
d									与session断开（但session任然在客户机上运行）
tmux list-sessions					列出存在的session
tmux attach -t session_name			重新与现有session连接

