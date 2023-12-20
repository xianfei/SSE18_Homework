#!/bin/bash
# function is_absolute_path() {
#     if [[ $1 =~ ^[/\\] ]]; then
#         return 0
#     else
#         return 1
#     fi
# }
function send() {
    read -rp "请输入您想发送的文件的绝对路径" fileAddr
    # fileAddr="/root/scripts/debug.sh"
    # echo "$fileAddr"

    if [ ! -f "$fileAddr" ]; then
        echo "文件不存在"
        return 6
    fi

    # if(is_absolute_path $fileAddr); then
    #     echo "绝对路径"
    # else
    #     echo "相对路径"
    # fi
    #获取脚本相对路径
    # relative_path=$(dirname "$(pwd)")
    # echo relative_path
    # fileAddr=$(cat temp)

    #提取fileAddr文件名,即最后一个/后的内容
    fileName=$(basename "$fileAddr")

    # fileName=echo $(${fileAddr##*/})
    # dialog --inputbox "请输入您想使用的端口号" 20 50 2> temp

    read -rp "请输入您想使用的端口号" sendPort
    # sendPort="80"
    if [ $? != 0 ]; then
        echo "未输入端口号"
        return 6
    fi
    # sendPort=$(cat temp)
    # dialog --inputbox "请输入接收方的ip地址" 20 50 2> temp

    read -rp "请输入接收方的ip地址" recvIP
    # recvIP="192.168.181.100"
    if [ $? != 0 ]; then
        echo "未输入接收方的ip地址"
        return 6
    fi
    # recvIP=$(cat temp)
    # dialog --title 正在发送 --infobox "正在发送文件$fileName " 20 50
    echo "正在发送文件$fileName到$recvIP:$sendPort"
    #第一次将文件名发送过去,确认可以正常连接
    echo "$fileName" | nc "$recvIP" "$sendPort"
    if [ $? != 0 ]; then
        # dialog --colors --msgbox "\Z1 发送错误！请检查端口号及IP地址！" 0 0
        echo "发送错误！请检查端口号及IP地址！"
        return 6
    fi
    sleep 1
    #将文件本身发送过去
    echo "正在发送文件本体"
    nc "$recvIP" "$sendPort" <"$fileAddr"
    if [ $? != 0 ]; then
        # dialog --colors --msgbox "\Z1 发送错误！" 0 0
        echo "文件发送错误！"
        return 6
    fi
    fileSize=$(ls -lh $fileAddr | awk '{print $5}')
    # dialog --msgbox "发送完成。\n文件名：$fileName \n大小：${fileSize}" 20 50
    echo -e "发送完成。\n文件名：$fileName \n大小：${fileSize}"
}
function recv() {
    # dialog --inputbox "请输入您想使用的端口号" 20 50 2> temp

    read -rp "请输入您想使用的端口号" recvPort
    # recvPort="80"
    if [ $? != 0 ]; then
        echo "未输入接收用的端口号"
        return 6
    fi
    # recvPort=$(cat temp)
    # dialog --title "请选择接收路径" --fselect "${HOME}/" 8 50 2> temp

    read -rp "请选择接收路径(必须是一个目录)" recvAddr
    # recvAddr="/root/archive"
    #如果不是目录直接返回
    if [ ! -d "$recvAddr" ]; then
        echo "未填写接受路径或路径不是目录"
        return 6
    fi
    # recvAddr=$(cat temp)
    localIP=$(ifconfig | grep "inet" | awk '{ print $2}' | grep -v "127.0.0.1" | grep -v ":")
    # dialog --title 等待接受 --infobox "本机IP：$localIP \n端口号：$recvPort" 20 50
    echo "==================等待接受=================="
    echo -e "本机IP：$localIP \n端口号：$recvPort"

    #接受发来的第一条确认信息,即文件名
    nc -l "$recvPort" >temp
    # echo "接受名字"
    if [ $? != 0 ]; then
        # dialog --colors --msgbox "\Z1 接收错误！" 0 0
        echo "接收错误！"
        return 6
    fi
    echo "接受文件名"
    recvFile=$(cat temp)
    # dialog --infobox "正在接收文件 $recvFile ……" 20 50
    echo "==================收到文件=================="
    echo "正在接收文件 $recvFile ……"
    # #清空temp文件内容
    # echo "清空temp"
    # echo "" > temp
    #文件本体暂存到temp中
    nc -l "$recvPort" >filetemp
    if [ $? != 0 ]; then
        # dialog --colors --msgbox "\Z1 接收错误！" 0 0
        echo "文件接收错误！"
        return 6
    fi
    mv filetemp "${recvAddr}/${recvFile}"
    fileSize=$(ls -lh ${recvAddr}/${recvFile} | awk '{print $5}')
    # dialog --msgbox "接收完成。\n文件名：$recvFile \n大小：${fileSize}" 20 50
    echo -e "接收完成。\n文件名：$recvFile \n大小：${fileSize}"
}
function mainUI() {
    # dialog --cancel-label 退出 --title Shell文件传输助手 --menu " \n " 20 50 8 1 "发送文件" 2 "接收文件" 3 "关于" 4 "退出" 2> temp
    # a1=$(cat temp)
    echo -e "==========文件传输助手==========\n1.发送文件\n2.接收文件\n3.退出\n请输入您的选择："
    read -r option
    # option="2"
    case $option in
    1)
        send
        if [ $? = 6 ]; then
            mainUI
        fi
        ;;
    2)
        recv
        if [ $? = 6 ]; then
            mainUI
        fi
        ;;
    # 3)
    #     #测试版本号0.1.0

    #     mainUI
    #     ;;
    3)
        return
        ;;
    *)
        echo "输入非法字符,请重新输入"
        mainUI
        ;;
    esac
}

mainUI
# clear

#结束后清除temp文件
rm -f temp
rm -f filetemp
