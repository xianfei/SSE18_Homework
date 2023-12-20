#!/bin/bash
    

input_directory=$1
backup_directory=$2
backup_interval=$3
while true; do
    # 创建备份目录，以当前时间戳命名
    backup_folder="$backup_directory/backup_$(date +%Y%m%d%H%M%S)"
    mkdir -p "$backup_folder"

    # 使用rsync命令备份输入目录到备份目录
    rsync -av "$input_directory/" "$backup_folder/"

    echo "已将文件目录 $input_directory下的文件定时备份到 $backup_folder"
    echo "备份完成于 $(date)"

    # 等待备份间隔时间
    sleep "$backup_interval"
done