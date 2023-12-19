#!/bin/bash

#实现文件备份功能,包含简单UI,包含以下选项
#1:备份->传入文件目录,并将目录下所有文件备份到指定目录
#2:恢复->传入备份文件目录,并将备份文件恢复到指定目录,可以不做这个功能
#3:退出,并返回到文件助手主界面

#可供参考的代码

# # 需求：对重要数据进行归档备份，输入一个目录的名称。末尾不带/，将目录下面所有文件按天归档保存，并将归档日期附加在归档文件名上面，放在/root/archive 下面
# #归档命令 tar -c 表示归档 -z 表示同时进行压缩，后缀为.tar.gz
# #参数：$1：目录名称 $2：归档目录位置，默认放在/root/archive 下面
# #判断函数是否可以使用
# #判断是否输入了目录名称，参数是否大于 2

# #test

# if [ $# -ge 2 ] || [ $# -eq 0 ]; then
#     echo "参数个数错误，应当输入第一个参数作为要归档的目录名，第二个参数作为归档文件存放目录"
#     exit #结束当前函数
# fi

# #从参数中获取目录名称
# if [ -d "$1" ]; then
#     dir="$1"
# else
#     echo "目录不存在"
#     exit
# fi
# DIR_NAME=$(basename "$dir")
# DIR_PATH=$(cd $(dirname $1); pwd)

# #判断归档目录第二个参数是否存在，不存在则默认为/root/archive,
# if [ -z "$2" ]; then
#     DEST_DIR="/root/archive"
#     if [ ! -d $DEST_DIR ]; then
#         mkdir $DEST_DIR
#     fi
#     echo "默认存放在了$DEST_DIR"
# elif [ -d "$2" ]; then
#     DEST_DIR="$2"
# else
#     echo "归档目录不存在"
#     exit
# fi
# #归档文件名字
# #获取当前日期
# DATE=$(date +%y%m%d)
# #定义生成的归档文件名称
# FILE_NAME="archive_${DIR_NAME}_${DATE}.tar.gz"
# #归档文件的完整路径
# DEST=$DEST_DIR/$FILE_NAME
# echo "开始归档"
# #用绝对路径归档
# echo
# tar -czf $DEST $DIR_PATH/$DIR_NAME
# if [ $? -eq 0 ]; then
#     echo
#     echo "归档成功"
#     echo "归档文件为 : $DEST"
#     echo
# else
#     echo "归档失败"
#     echo
# fi
# exit

function backup() {
    # 设置输入目录和目标备份目录
    echo 'please input the source backup directory'
    read -r input_directory
    #输入的是quit!则退出
    if [ "$input_directory" = "quit!" ]; then
        return
    fi
    while [ ! -d "$input_directory" ]; do
        echo 'please input the correct directory'
        read -r input_directory
    done

    echo 'please input the target backup directory'
    read -r backup_directory
    #输入quit!退出
    if [ "$backup_directory" = "quit!" ]; then
        return
    fi
    while [ ! -d "$backup_directory" ]; do
        echo 'please input the correct directory'
        read -r backup_directory
    done

    # 设置备份间隔
    echo 'please input the backup time interval (XXseconds)'
    read -r backup_interval
    #输入quit!退出
    if [ "$backup_interval" = "quit!" ]; then
        return
    fi
    while [ ! "$backup_interval" -gt 0 ]; do
        echo 'please input the correct time interval'
        read -r backup_interval
    done

    #上述操作合法之后另开一个线程进入nohup_back_up脚本持续进行备份,并且将该进程的输出放在nohup.out文件中
    nohup sh ./nohup_back_up.sh "$input_directory" "$backup_directory" "$backup_interval" >nohup.out 2>&1 &
    echo "备份进程已经启动对文件夹$input_directory进行备份,备份到$backup_directory,备份间隔为$backup_interval秒"
    echo "备份进程输出日志在FileHelperFishlulu/components/nohup.out中"
}
function process_modify() {
    echo "==========备份进程管理=========="
    echo -e "1.查看备份进程\n2.结束备份进程\n3.退出\n请输入您的选择："
    read -r option
    case $option in
    1)
        ps -ef | grep nohup_back_up.sh
        process_modify
        ;;
    2)
        #根据用户输入选项结束备份进程
        read -rp "请输入要结束的进程号(如果输入\"-a\"则全部结束,输入quit!退出)" option
        if [ "$option" = "-a" ]; then
            ps -ef | grep nohup_back_up.sh | grep -v grep | awk '{print $2}' | xargs kill
            echo "已结束全部备份进程"
        elif [ "$option" = "quit!" ]; then
            return
        else
            #如果进程号不属于备份进程则提示错误
            if [ -z "$(ps -ef | grep nohup_back_up.sh | grep -v grep | awk '{print $2}' | grep "$option")" ]; then
                echo "进程号$option不属于备份进程"
                process_modify
            else #否则结束该进程
                kill "$option"
                            
                if [ $? = 0 ]; then
                    echo "备份进程$option结束成功"
                else
                    echo "备份进程$option结束失败"
                fi
            fi

        fi
        

        process_modify
        ;;
    3)
        return
        ;;
    *)
        echo "输入错误，请重新输入"
        process_modify
        ;;
    esac
}
function mainUI() {
    # dialog --cancel-label 退出 --title Shell文件传输助手 --menu " \n " 20 50 8 1 "发送文件" 2 "接收文件" 3 "关于" 4 "退出" 2> temp
    # a1=$(cat temp)
    echo -e "==========文件备份助手==========\n1.持续备份文件\n2.操作备份进程\n3.退出\n请输入您的选择："
    read -r option
    # option="2"
    case $option in
    1)
        echo -e "在备份过程中任意地方输入\"quit!\"可以退出备份"
        backup
        if [ ! $? = 0 ]; then
            mainUI
        fi
        ;;
    2)
        process_modify
        if [ ! $? = 0 ]; then
            mainUI
        fi
        ;;
    3)
        return
        ;;
    *)
        echo "输入非法字符,请重新输入"
        mainUI
        ;;
    esac
}
#切换到该脚本执行位置
script_dir=$(dirname "$(realpath "$0")")
cd "$script_dir" || exit

mainUI
