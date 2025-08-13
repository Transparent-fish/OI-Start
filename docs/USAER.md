# 1. 珂朵莉树 (ODT)
操作：
```cpp
ODT odt;//定义
odt.init(1, 1e9, 0); // 初始化区间[1,1e9]值为0
odt.assign(3, 50000, 1); // [3,50000]赋值为1
// 操作符：+ - * /
odt.update(10, 10000, 2, '+'); // [10,10000]每个数+2
odt.update(50, 200, 3, '*');   // [50,200]每个数*3
int sum = odt.query(30, 700,'+'); // 返回[30,700]区间和 第三个参数可以替换为四则运算符(+ - * /)
```
# 线段树 (Seg)
```cpp
Seg<大小>seg
seg.build(建树的原数组，建的左区间, 建的右区间, 根节点);
seg.update(目标修改区间的左边界, 目标修改区间的右边界, 修改值, 操作类型(+ - * /), 当前节点区间左边界, 当前节点区间右边界, 当前节点存储下标);
// 当前节点区间左边界, 当前节点区间右边界, 当前节点存储下标 可不写
seg.query();// 同 update 相同
```
# FastIO
```cpp
int a, b;
in >> a >> b;
out << a + b;
```
注意：每次读入完成后，**Windows** 下请 `Ctrl + Z` **Linux** 下 `Ctrl + D` 手动读入 `EOF` 以结束读入！
# 并查集 (UF)
```cpp
UF<大小>uf;
uf.init();// 初始化
uf.merage(x, y); // 合并 x y 的集合
uf.query(x, y); // 检查是否连通
```
# 5. 实用函数库 (funct)
**快速幂**
```cpp
funct tools;
int a = tools.power(x,y);//a = x ^ y
int b = tools.power(x, y, mod);//b = x ^ y % mod
```
**进制转换**
```cpp
funct tools;
string s = conversion(x, n);//把十进制数n转换成x进制的数，返回字符串。
int k = conversion(x, s);//把x进制的数转换为10进制的数,s是字符串。
```
**lcm**
```cpp
funct tools;
int a = tools.lcm(x, y);//返回 x y 的 lcm 值
```
**判断质数**
```cpp
funct tools;
int a = tools.prime(x);//如果 x 为质数，返回1，否则返回0
```
