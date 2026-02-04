#include "DBHelper.h"

// 1. 构造函数：连接数据库
DBHelper::DBHelper() {
    try {
        // 记得改密码！password=你的密码
        string conn_str = "dbname=postgres user=postgres password=123456 host=localhost port=5432";
        C = new pqxx::connection(conn_str);
        
        if (C->is_open()) {
            cout << "[DB] 数据库连接成功: " << C->dbname() << endl;
        } else {
            cout << "[DB] 连接失败！" << endl;
        }
    } catch (const exception &e) {
        cerr << "[DB] 连接发生错误: " << e.what() << endl;
    }
}

// 2. 析构函数：断开连接
// 修改后的析构函数
DBHelper::~DBHelper() {
    if (C) {
        // 不需要调用 disconnect()，delete 指针时连接会自动关闭
        delete C;
        cout << "[DB] 连接已断开" << endl;
    }
}

// 3. 登录功能实现
string DBHelper::handleLogin(string card, string pwd) {
    try {
        // 建立一个“非事务”的工作对象 (只读用这个)
        pqxx::nontransaction N(*C);

        // 拼凑 SQL：注意单引号！
        // 也就是：SELECT name FROM accounts WHERE card_number='...' AND password='...'
        string sql = "SELECT name FROM accounts WHERE card_number = '" + card + 
                     "' AND password = '" + pwd + "'";

        // 执行查询
        pqxx::result R = N.exec(sql);

        // 如果结果集是空的，说明没查到
        if (R.empty()) {
            return ""; // 返回空字符串表示失败
        }

        // 查到了，提取第一行(R[0])的"name"列，转成 string
        return R[0]["name"].as<string>();

    } catch (const exception &e) {
        cerr << "[Login] 查询出错: " << e.what() << endl;
        return "";
    }
}

// 4. 查询余额实现
double DBHelper::getBalance(string card) {
    try {
        pqxx::nontransaction N(*C);
        
        string sql = "SELECT balance FROM accounts WHERE card_number = '" + card + "'";
        
        pqxx::result R = N.exec(sql);
        
        if (R.empty()) {
            return 0.0;
        }
        
        // 把结果转成 double (小数)
        return R[0]["balance"].as<double>();
        
    } catch (const exception &e) {
        cerr << "[Balance] 查询出错: " << e.what() << endl;
        return 0.0;
    }
}