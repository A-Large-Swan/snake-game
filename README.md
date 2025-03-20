# Snake Game

这是一个跨平台的终端贪吃蛇游戏，支持Windows（通过MSYS2或Cygwin）和Linux系统。

## 项目介绍

这是一个使用C语言编写的经典贪吃蛇游戏，支持在终端中运行。游戏具有以下特点：

- 跨平台支持：支持Windows（MSYS2/Cygwin）和Linux系统
- 多种游戏模式：经典模式和关卡模式
- 简单直观的界面
- 实时分数显示
- 障碍物系统
- 难度递增

## 安装说明

### Windows系统

1. 安装MSYS2或Cygwin
2. 安装必要的依赖：
   - gcc
   - make
   - ncurses-devel（MSYS2）或libncurses-devel（Cygwin）

### Linux系统

#### 环境要求
- GCC编译器
- Make工具
- ncursesw开发库

#### 自动安装（Ubuntu/Debian或RHEL/CentOS）

1. 克隆项目：
```bash
git clone https://github.com/A-Large-Swan/snake-game.git
```

2. 进入项目目录：
```bash
cd snake-game
```

3. 执行安装脚本：
```bash
sudo sh install.sh
```

#### 手动安装（其他Linux发行版）

1. 安装必要的依赖（以下是一般名称，具体包名可能因发行版而异）：
   - gcc
   - make
   - ncurses开发库

2. 编译游戏：
```bash
make
```

## 游戏玩法

### 启动游戏
```bash
./snake
```

### 控制方式
- ↑：向上移动
- ↓：向下移动
- ←：向左移动
- →：向右移动
- Q：退出游戏
- P：暂停游戏

### 游戏规则
1. 控制蛇吃掉随机出现的食物
2. 每吃掉一个食物，蛇的长度增加，分数增加
3. 撞到墙壁、障碍物或自己的身体游戏结束
4. 随着分数增加，游戏难度会逐渐提高

### 游戏模式
- 经典模式：无障碍物，专注于基础玩法
- 关卡模式：包含不同布局的障碍物，增加游戏难度

## 开发相关

### 构建选项
- 构建发布版本：`make release`
- 构建调试版本：`make debug`
- 清理构建文件：`make clean`

### 项目结构
- `snake.h/c`：蛇的基本数据结构和移动逻辑
- `game.h/c`：游戏核心逻辑
- `level.h/c`：关卡系统实现
- `ui.h/c`：用户界面绘制
- `main.c`：程序入口

## 贡献指南

欢迎为项目做出贡献！您可以：
1. 提交Bug报告
2. 提出新功能建议
3. 提交代码改进
4. 完善文档

在提交代码前，请确保：
1. 代码符合项目的编码规范
2. 通过所有测试
3. 更新相关文档

## 许可证

本项目采用MIT许可证。详见LICENSE文件。
