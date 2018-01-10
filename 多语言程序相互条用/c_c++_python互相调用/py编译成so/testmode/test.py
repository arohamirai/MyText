import threading,time
'''
def haha(start_env):
    print("start envent")
    start_env.wait()
    print("envent is started!")
    
start_env=threading.Event()
t=threading.Thread(target=haha,args=(start_env,))
t.start()
print("haha")
time.sleep(3)
start_env.set()

print("haha2")
#start_env.clear()

#####################################
def haha(start_env):
    print("start envent") 
    time.sleep(3)
    print("envent is started!")
    start_env.set()
start_env=threading.Event()
print("haha0")
t=threading.Thread(target=haha,args=(start_env,))
t.start()
print("haha1")
start_env.wait()
print("haha2")
######################
'''
aa='abcdefg'
bb=[1,2,3,4]
cc=dict({'a':1,'b':2})
class dd(object):
    def __init__(self,arg):
        self.arg=arg
    def print_arg(self):
        print("arg:",self.arg)
def ee():
    print("ee")
    return 5

