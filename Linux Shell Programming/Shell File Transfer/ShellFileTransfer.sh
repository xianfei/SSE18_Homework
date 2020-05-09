#!/bin/bash
send()
{
dialog --inputbox "请将文件拖到这里，或者输入绝对路径" 20 50 2> temp
if [ $? != 0 ]
then
return 6
fi
fileAddr=`cat temp`
fileName=`echo ${fileAddr##*/}`
dialog --inputbox "请输入您想使用的端口号" 20 50 2> temp
if [ $? != 0 ]
then
return 6
fi
sendPort=`cat temp`
dialog --inputbox "请输入接收方的ip地址" 20 50 2> temp
if [ $? != 0 ]
then
return 6
fi
recvIP=`cat temp`
dialog --title 正在发送 --infobox "正在发送文件$fileName " 20 50
echo $fileName | nc $recvIP $sendPort
if [ $? != 0 ]
then
dialog --colors --msgbox "\Z1 发送错误！请检查端口号及IP地址！" 0 0
return 6
fi
sleep 1
nc $recvIP $sendPort < $fileAddr
if [ $? != 0 ]
then
dialog --colors --msgbox "\Z1 发送错误！" 0 0
return 6
fi
fileSize=`ls -lh $fileAddr | awk '{print $5}'`
dialog --msgbox "发送完成。\n文件名：$fileName \n大小：${fileSize}" 20 50
}
recv()
{
dialog --inputbox "请输入您想使用的端口号" 20 50 2> temp
if [ $? != 0 ]
then
return 6
fi
recvPort=`cat temp`
dialog --title "请选择接收路径" --fselect "${HOME}/" 8 50 2> temp
if [ $? != 0 ]
then
return 6
fi
recvAddr=`cat temp`
localIP=`ifconfig | grep "inet" | awk '{ print $2}' | grep -v "127.0.0.1" | grep -v ":"`
dialog --title 等待接受 --infobox "本机IP：$localIP \n端口号：$recvPort" 20 50
nc -l $recvPort > temp
if [ $? != 0 ]
then
dialog --colors --msgbox "\Z1 接收错误！" 0 0
return 6
fi
recvFile=`cat temp`
dialog --infobox "正在接收文件 $recvFile ……" 20 50
nc -l $recvPort > filetemp
if [ $? != 0 ]
then
dialog --colors --msgbox "\Z1 接收错误！" 0 0
return 6
fi
mv filetemp ${recvAddr}/${recvFile}
fileSize=`ls -lh ${recvAddr}/${recvFile} | awk '{print $5}'`
dialog --msgbox "接收完成。\n文件名：$recvFile \n大小：${fileSize}" 20 50
}
mainUI()
{
dialog --cancel-label 退出 --title Shell文件传输助手 --menu " \n " 20 50 8 1 "发送文件" 2 "接收文件" 3 "关于" 4 "退出" 2> temp
a1=`cat temp`
case $a1 in
1)
send
if [ $? = 6 ]
then 
mainUI
fi
;;
2)
recv
if [ $? = 6 ]
then 
mainUI
fi
;;
3)
dialog --colors --msgbox "Shell文件传输助手 \n\nBeta Version 2019.3.5\n\n\Z6开发人员：\n王衔飞  李思涵  胡嘉慧  丁玲" 20 50
mainUI
;;
4)
return
;;
esac
}
mainUI
clear
rm -f temp
rm -f filetemp