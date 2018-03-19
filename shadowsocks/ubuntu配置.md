1. 安装gui客户端
sudo add-apt-repository ppa:hzwhuang/ss-qt5
sudo apt-get update
sudo apt-get install shadowsocks-qt5

2. 配置客户端
[connection]-[connnect]中填入参数，链接

3. 配置chrome浏览器自动代理切换
模仿XX-Net,导入本文件夹下的两个配置文件，然后选择myss模式就行


4. ubuntu 配置终端代理http和https:
sudo gedit /etc/profile
加入：
#set socket proxy
http_proxy=socks5://127.0.0.1:1080
https_proxy=socks5://127.0.0.1:1080
no_proxy=*.abc.com,10.*.*.*,192.168.*.*,*.local,localhost,127.0.0.1
export http_proxy https_proxy no_proxy

让配置文件生效：
source /etc/profile
