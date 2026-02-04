#ifndef DBHELPER_H
#define DBHELPER_H

#include <string>
#include <pqxx/pqxx> // 引入数据库库
#include <iostream>

using namespace std;

class DBHelper {
private:
    pqxx::connection* C; // 这是一个指针，指向与数据库的连接线

public:
    // 构造函数：一出生就自动连接数据库
    DBHelper();
    // 析构函数：任务结束自动断开
    ~DBHelper();

    // ----------------------------------------------------
    // 功能 1：登录验证
    // 输入：卡号，密码
    // 返回：如果成功返回用户名(比如"张三")，失败返回空字符串 ""
    string handleLogin(string card, string pwd);

    // 功能 2：查询余额
    // 输入：卡号
    // 返回：余额数字
    double getBalance(string card);

    // ----------------------------------------------------
    // 这里的“转账、取款”我们下一轮再写，先把上面两个跑通！
};

#endif //DBHELPER_H