
#include <iostream>
#include <string>
#include "DBHelper.h"

using namespace std;

int main() {
    DBHelper db;
    string input_card, input_pwd;

    cout << "\n=== ATM 测试模式 ===" << endl;
    cout << "请输入卡号: "; cin >> input_card;
    cout << "请输入密码: "; cin >> input_pwd;

    string userName = db.handleLogin(input_card, input_pwd);

    if (userName != "") {
        cout << ">>> 登录成功！欢迎用户: " << userName << endl;

        // --- 新增：功能循环菜单 ---
        while (true) {
            cout << "\n------- 功能菜单 -------" << endl;
            cout << "1. 查询余额  2. 取款  3. 转账  4. 修改密码  0. 退出" << endl;
            cout << "请选择操作: ";
            int choice;
            cin >> choice;

            if (choice == 0) break; // 退出循环，程序结束

            if (choice == 1) {
                double money = db.getBalance(input_card);
                cout << ">>> 您的余额是: " << money << " 元" << endl;
            }
            else if (choice == 3) {
                string to_card;
                double amount;
                cout << "请输入目标卡号: "; cin >> to_card;
                cout << "请输入转账金额: "; cin >> amount;

                if (db.transfer(input_card, to_card, amount)) {
                    cout << ">>> 转账成功！" << endl;
                } else {
                    cout << ">>> 转账失败（余额不足或账号不存在）。" << endl;
                }
            }
        }
    } else {
        cout << ">>> 登录失败！账号或密码错误。" << endl;
    }

    cout << "感谢使用，再见！" << endl;
    return 0;
}