#!/bin/bash

# 检测操作系统类型
if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS_TYPE=$ID
    OS_FAMILY=$ID_LIKE
elif [ -f /etc/debian_version ]; then
    OS_TYPE="debian"
    OS_FAMILY="debian"
elif [ -f /etc/redhat-release ]; then
    OS_TYPE="rhel"
    OS_FAMILY="rhel"
else
    echo "无法确定系统类型，请手动安装依赖。"
    exit 1
fi

# 安装依赖
echo "正在安装依赖..."
if [[ $OS_TYPE == "debian" || $OS_TYPE == "ubuntu" || $OS_FAMILY == *"debian"* ]]; then
    apt-get update
    apt-get install -y gcc make libncursesw5-dev
elif [[ $OS_TYPE == "fedora" || $OS_TYPE == "rhel" || $OS_TYPE == "centos" || $OS_FAMILY == *"rhel"* ]]; then
    yum install -y gcc make ncurses-devel
else
    echo "未知的系统类型，请手动安装依赖：gcc、make和ncurses开发库"
    exit 1
fi

# 编译游戏
echo "正在编译游戏..."
mkdir -p build
make release

# 检查编译结果
if [ $? -eq 0 ]; then
    echo "编译成功！"
    echo "您可以通过执行 ./snake 来开始游戏"
else
    echo "编译失败，请检查错误信息"
    exit 1
fi

exit 0