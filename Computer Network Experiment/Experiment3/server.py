# -*- coding:utf-8 -*-
 
import sys
import socket
import threading
import json

class MyStruct: # 要传输的结构
    def __init__(self, id, message, opt):
        self.id = id
        self.message = message
        self.opt = opt

def dict2MyStruct(d): # 反序列化函数
    return MyStruct(d['id'], d['message'], d['opt'])
 
def threadfun(sock, addr):
    try:
        while True:
            data = sock.recv(1024) # 接收消息
            if data:
                rec_msg = json.loads(bytes.decode(data), object_hook=dict2MyStruct) #反序列化
                if hasattr(rec_msg,'opt'):
                    if rec_msg.opt=="quit" or rec_msg.opt=="exit":
                        break 
                print("Message from %s: " % addr[0])
                print(rec_msg.__dict__)
                p = MyStruct(0,"you will exit.","exit")
                msg = json.dumps(p, default=lambda obj: obj.__dict__, ensure_ascii=False, indent=2, sort_keys=True)
                print("Send back to %s: " % addr[0])
                print(p.__dict__)
                sock.send(str.encode(msg)) # 送回消息
        sock.close()
    except Exception as e:
        e.with_traceback()
    finally:
        sock.close()
 
def my_server(port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # 创建TCP套接字
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # 启用地址重用
    srv_addr = ("0.0.0.0", port)
    sock.bind(srv_addr) # 绑定地址和端口号
    sock.listen(5) # 侦听客户端
    while True:
        # 接受客户端连接
        conn, addr = sock.accept()
        t = threading.Thread(target=threadfun, args=(conn, addr))
        t.start()
    
if __name__ == "__main__":
    my_server(8888) # 传入端口号
    