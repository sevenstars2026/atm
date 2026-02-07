# 🏧 ATM 模拟系统 (C++ & PostgreSQL)

![C++](https://img.shields.io/badge/Language-C++17-00599C.svg)
![PostgreSQL](https://img.shields.io/badge/Database-PostgreSQL-336791.svg)
![Platform](https://img.shields.io/badge/OS-Ubuntu-orange.svg)
![Build](https://img.shields.io/badge/Build-CMake-green.svg)

## 📖 项目简介
本项目是一个基于 C++ 开发的简易 ATM 银行模拟系统。后端采用 PostgreSQL 数据库进行持久化存储，通过 `libpqxx` 库实现高效的数据库交互。

项目模拟了真实银行系统的核心业务流程，并重点加强了数据安全性，修复了传统的 SQL 注入漏洞。

## ✨ 核心功能
本系统包含以下四大核心模块：

* **💰 余额查询 (Check Balance):** 实时获取当前账户可用余额。
* **💸 转账功能 (Transfer):** 支持账户间资金划转，利用数据库事务保证资金一致性。
* **🔐 修改密码 (Change Password):** 安全验证机制下的密码更新。
* **📜 流水记录 (Transaction Log):** 自动记录每一笔交易（转账、存取款）的时间、类型和金额。

## 🛡️ 安全特性：防 SQL 注入
> **⚠️ 重要安全更新**

本项目已废弃不安全的字符串拼接查询方式，全面采用 **参数化查询 (Prepared Statements)**。
通过 `libpqxx` 的 `exec_params` 机制，将 SQL 指令与数据物理分离，有效防御 SQL 注入攻击（如 `' OR '1'='1`）。

* ❌ **[已移除] 不安全写法:**
    ```cpp
    // 易受攻击：直接拼接字符串
    string sql = "SELECT balance FROM accounts WHERE card_num = '" + card_id + "'";
    ```

* ✅ **[当前] 安全实现:**
    ```cpp
    // 安全：使用占位符 $1，数据库引擎自动处理转义
    txn.exec_params("SELECT balance FROM accounts WHERE card_num = $1", card_id);
    ```

## 🛠️ 开发环境
* **操作系统:** Ubuntu Linux
* **IDE:** CLion (JetBrains)
* **构建系统:** CMake
* **依赖库:** `libpqxx` (PostgreSQL C++ API), `libpq`

## 🚀 快速开始

### 1. 环境准备 (Ubuntu)
在终端执行以下命令安装必要的编译器和依赖库：

```bash
sudo apt-get update
# 安装编译器和 CMake
sudo apt-get install build-essential cmake
# 安装 PostgreSQL 数据库
sudo apt-get install postgresql postgresql-contrib
# 安装 C++ 连接库
sudo apt-get install libpqxx-dev
