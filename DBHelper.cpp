#include "DBHelper.h"

// 构造函数：负责连接数据库
DBHelper::DBHelper() {
    try {
        string conn_str = "dbname=postgres user=postgres password=123456 host=localhost port=5432";
        C = new pqxx::connection(conn_str);

        if (C->is_open()) {
            cout << "[DB] 连接成功: " << C->dbname() << endl;
        } else {
            cout << "[DB] 连接失败!" << endl;
        }
    } catch (const exception &e) {
        cerr << "[DB] 连接发生错误: " << e.what() << endl;
    }
}

// 析构函数
DBHelper::~DBHelper() {
    if (C) {
        delete C;
    }
}

// 1. 登录功能
string DBHelper::handleLogin(string card_id, string pwd) {
    if (!C || !C->is_open()) return "";
    try {
        pqxx::work W(*C);

        // 【统一使用 card_num】
        string sql = "SELECT card_num FROM accounts WHERE card_num = $1 AND password = $2";

        pqxx::result R = W.exec_params(sql,card_id,pwd);

        if (!R.empty()) {
            return R[0][0].as<string>();
        }
    } catch (const exception &e) {
        cerr << "[Login Error] " << e.what() << endl;
    }
    return "";
}

// 2. 查余额功能
double DBHelper::getBalance(string card_id) {
    if (!C || !C->is_open()) return 0.0;
    try {
        pqxx::nontransaction N(*C);

        // 【统一使用 card_num】(你刚才报错就是因为这里写了 card_number)
        string sql = "SELECT balance FROM accounts WHERE card_num = $1";
        pqxx::result R = N.exec_params(sql,card_id);

        if (!R.empty()) {
            return R[0][0].as<double>();
        }
    } catch (const exception &e) {
        cerr << "[Balance Error] " << e.what() << endl;
    }
    return 0.0;
}

// 3. 取款功能
bool DBHelper::withdraw(string card_id, double amount) {
    if (!C || !C->is_open()) return false;
    try {
        pqxx::work W(*C);

        // 【统一使用 card_num】
        string check_sql = "SELECT balance FROM accounts WHERE card_num = $1";
        pqxx::result R = W.exec_params(check_sql,card_id,amount);

        if (R.empty()) return false;

        double current_balance = R[0][0].as<double>();

        if (current_balance < amount) {
            cout << ">>> 余额不足！当前余额: " << current_balance << endl;
            return false;
        }

        // 【统一使用 card_num】
        string update_sql = "UPDATE accounts SET balance = balance - " + to_string(amount) +
                            " WHERE card_num = '" + card_id + "'";

        W.exec(update_sql);
        W.commit();
        return true;

    } catch (const exception &e) {
        cerr << "[Withdraw Error] " << e.what() << endl;
        return false;
    }
}