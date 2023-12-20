#!/bin/bash
version="0.1.1"
#文件助手主界面,通过该界面来调用其他的脚本,目前打算支持实现文件传输和备份和功能
#脚本可直接通过命令 fhelper 来调用

function mainUI() {

    echo -e "==========欢迎使用文件助手==========\n1.文件传输助手\n2.文件备份助手\n3.文件转移助手\n4.关于\n5.退出\n请输入您的选择："
    read -r option
    case $option in
    1)
        source ./components/FileTransfer.sh
        if [ $? != 0 ]; then
            ehco "进入失败"
            mainUI
        fi
        ;;
    2)

        source ./components/FileBackup.sh
        if [ $? != 0 ]; then
            ehco "进入失败"
            mainUI
        fi
        ;;
    3)
        source ./components/FileMove.sh
        if [ $? != 0 ]; then
            ehco "进入失败"
            mainUI
        fi
        ;;
    4)
        echo -e "\n\n*********Shell文件助手********* \n\nV${version} 2023.10.7\n\n开发人员：\n禄禄鱼  艾俊波  涂珉铢  孙明睿  文思捷\n\n"
        mainUI
        ;;

    5)  
        echo "感谢使用~"
        return 
        ;;
    *)
        echo "输入非法字符,请重新输入"
        mainUI
        ;;
    esac
}

#转移到脚本所在目录
script_dir=$(dirname "$(realpath "$0")")
cd "$script_dir" || exit
mainUI
