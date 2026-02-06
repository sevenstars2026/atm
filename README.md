ATM 模拟系统 (C++ & PostgreSQL)
本项目是一个基于 C++ 开发的简易 ATM 银行系统，通过 libpqxx 库连接 PostgreSQL 数据库实现持久化存储。

🛠 最近更新：安全漏洞修复
在开发过程中，我们发现并修复了一个严重的安全漏洞：SQL 注入 (SQL Injection)。

1. 发现问题
在原始版本中，数据库查询采用的是字符串拼接的方式：

C++
// ❌ 不安全的代码示例
string sql = "SELECT balance FROM accounts WHERE card_num = '" + card_id + "'";
W.exec(sql);
风险： 恶意用户可以通过输入特殊的卡号（例如 '; DROP TABLE accounts; --）直接破坏数据库结构，导致数据被窃取或全库被删。

2. 解决方案：参数化查询 (Prepared Statements)
参考业界标准做法，我引入了 exec_params 函数来重构所有的数据库交互逻辑。

修复后的代码：

C++
// ✅ 安全的代码示例
string sql = "SELECT balance FROM accounts WHERE card_num = $1";
pqxx::result R = W.exec_params(sql, card_id);
3. 原理解析
指令与数据分离：我们不再手动拼凑完整的 SQL 语句，而是先发送一个带有占位符（如 $1）的指令模板给数据库。

物理隔离：数据库会先“理解”这条查询指令的意图。随后传入的变量内容无论多么诡异，数据库都只会将其视为普通的文本字符串，而不会当作命令去执行。
