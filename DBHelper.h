#ifndef ATM_DBHELPER_H
#define ATM_DBHELPER_H

#include <iostream>
#include <string>
#include <pqxx/pqxx> // 引入数据库库

using namespace std;

class DBHelper {
public:
    // 构造函数和析构函数
    DBHelper();
    ~DBHelper();

    // 1. 登录
    string handleLogin(string card_id, string pwd);

    // 2. 查余额
    double getBalance(string card_id);

    // 3. 取款 (你之前缺的就是这一行声明！)
    bool withdraw(string card_id, double amount);

private:
    pqxx::connection *C; // 数据库连接对象
};

#endif //ATM_DBHELPER_H