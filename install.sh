#!/bin/bash

# 检查操作系统类型
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo "检测到Windows系统，请确保已安装MSYS2或Cygwin"
    echo "请手动安装以下依赖："
    echo "1. gcc"
    echo "2. make"
    echo "3. ncurses-devel (MSYS2) 或 libncurses-devel (Cygwin)"
    exit 0
fi

# Linux系统安装依赖
if [ "$(id -u)" != "0" ]; then
   echo "在Linux系统上需要root权限安装依赖" 1>&2
   exit 1
fi

# 检测Linux发行版类型
if [ -f /etc/debian_version ]; then
    # Debian/Ubuntu系统
    apt-get update
    apt-get install -y gcc make libncursesw5-dev
elif [ -f /etc/redhat-release ]; then
    # RHEL/CentOS系统
    yum update
    yum install -y gcc make ncurses-devel
else
    echo "不支持的Linux发行版，请手动安装以下依赖："
    echo "1. gcc"
    echo "2. make"
    echo "3. ncurses开发库"
    exit 1
fi

# 编译游戏
make clean
make

echo "游戏编译完成，运行 ./snake 开始游戏"