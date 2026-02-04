#include <iostream>
#include "DBHelper.h" // 引用刚才写的头文件

using namespace std;

int main() {
    // 1. 创建管理员 (这时候会自动连接数据库)
    cout << "正在启动系统..." << endl;
    DBHelper db;

    // 2. 模拟用户输入
    string input_card, input_pwd;
    cout << "\n=== ATM 测试模式 ===" << endl;
    cout << "请输入卡号: ";
    cin >> input_card;
    cout << "请输入密码: ";
    cin >> input_pwd;

    // 3. 调用 db 的功能
    string userName = db.handleLogin(input_card, input_pwd);

    if (userName != "") {
        cout << ">>> 登录成功！欢迎用户: " << userName << endl;

        // 顺便测一下查余额
        double money = db.getBalance(input_card);
        cout << ">>> 您的余额是: " << money << " 元" << endl;
    } else {
        cout << ">>> 登录失败！账号或密码错误。" << endl;
    }

    return 0;
}