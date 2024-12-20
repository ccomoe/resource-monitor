# 系统资源监视器

## 项目介绍

该项目是一个基于 C 语言实现的 Linux 系统资源监视器，能够实时监控系统的 CPU 使用率、内存使用情况以及磁盘空间使用情况。通过读取系统文件（如 `/proc/stat`、`/proc/meminfo` 和 `df` 命令），该监视器能够定期刷新并输出资源的使用信息。适用于 Linux 系统环境，帮助用户实时查看系统资源的占用情况，方便进行性能调优和故障排查。

## 功能特点

- 实时显示系统的 CPU 使用率、内存使用情况和磁盘使用情况。
- 每秒刷新一次监控数据。
- 支持多核心 CPU 的使用情况显示。
- 支持显示内存和磁盘的详细使用数据。
- 通过命令行显示资源使用信息，便于用户快速查看。

## 安装与使用

### 1. 环境要求

- Linux 操作系统（任何支持 `/proc` 文件系统的发行版）
- GCC 编译器

### 2. 安装步骤

1. 克隆本项目：

   ```bash
   git clone https://github.com/ccomoe/resource-monitor.git
   cd resource-monitor
