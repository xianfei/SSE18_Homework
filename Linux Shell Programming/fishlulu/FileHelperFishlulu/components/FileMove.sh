#!/bin/bash
# 文件移动助手，支持批量转移文件/文件夹

# 转移目录下所有文件夹 到指定文件夹
function moveFolder(){
    echo "Please input source Folder(type 0 to quit)"
    read input1
    if [ -d $input1 ];then
        source_folder=$input1
    elif [ $input1 -eq 0 ];then
	return 6
    else
	echo "invalid folder!"
	moveFolder
    fi

    echo "Please input target Folder"
    read input2
    if [ -d $input2 ];then
        target_folder=$input2
    else
	echo "invalid folder!"
	moveFolder
    fi
    
    for dirmv in ${source_folder}/*;do
	if [ -d $dirmv ];then
	    mv ${dirmv} ${target_folder}
	fi
    done
    echo "Please check!"
    return 6

}
# 批量转移文件 到指定文件夹
function moveFile(){
    echo "Please input source Folder(type 0 to quit)"
    read input1
    if [ -d $input1 ];then
        source_folder=$input1
    elif [ $input1 -eq 0 ];then
	return 6
    else
	echo "invalid folder!"
	moveFile
    fi

    echo "Please input target Folder"
    read input2
    if [ -d $input2 ];then
        target_folder=$input2
    else
	echo "invalid folder!"
	moveFile
    fi
    for file in ${source_folder}/*;do
	if [ -f $file ];then
	    mv $file ${target_folder}
	fi
    done
    echo "Please check!"
    return 6
}
function mainUI() {
    echo -e "==========文件移动助手==========\n1.移动文件\n2.移动文件夹\n3.退出\n请输入您的选择："
    read -r option
    case $option in
    1)
        moveFile
        if [ $? = 6 ]; then
            mainUI
        fi
        ;;
    2)
        moveFolder
        if [ $? = 6 ]; then
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

mainUI
