# -*- coding:utf-8 -*-
 
import sys
import socket
import argparse
import json

class MyStruct: # 要传输的结构
    def __init__(self, id, message, opt):
        self.id = id
        self.message = message
        self.opt = opt

def dict2MyStruct(d): # 反序列化函数
    return MyStruct(d['id'], d['message'], d['opt'])
 
def my_client(host, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # 创建TCP套接字
    srv_addr = (host, port) 
    sock.connect(srv_addr) # 连接服务器
    try: # 发送并接收数据
        while True: # 发送消息   
            p = MyStruct(1,"hello server.","default")  
            print("Send to server: ")
            print(p.__dict__)
            msg = json.dumps(p, default=lambda obj: obj.__dict__, ensure_ascii=False, indent=2, sort_keys=True)
            sock.sendall(str.encode(msg))    
            if hasattr(msg,'opt'):
                if msg.opt=="quit" or msg.opt=="exit":
                    break 
            data = sock.recv(1024) # 接收消息
            rec_msg = json.loads(bytes.decode(data), object_hook=dict2MyStruct) #反序列化
            print("Message from server: ")
            print(rec_msg.__dict__)
            if hasattr(rec_msg,'opt'):
                if rec_msg.opt=="quit" or rec_msg.opt=="exit":
                    break
        sock.close()
    except Exception as e:
        e.with_traceback()
    finally:
        sock.close()
        
if __name__ == "__main__":
    my_client("127.0.0.1", 8888) 