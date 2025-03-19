#!/bin/bash

# 检查是否为root用户
if [ "$(id -u)" != "0" ]; then
   echo "此脚本需要root权限运行" 1>&2
   exit 1
fi

# 检测系统类型
if [ -f /etc/debian_version ]; then
    # Debian/Ubuntu系统
    apt-get update
    apt-get install -y gcc make libncurses5-dev
elif [ -f /etc/redhat-release ]; then
    # RHEL/CentOS系统
    yum update
    yum install -y gcc make ncurses-devel
else
    echo "不支持的Linux发行版"
    exit 1
fi

# 编译游戏
make clean
make

echo "游戏编译完成，运行 ./snake 开始游戏"