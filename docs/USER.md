# OI-Start 使用说明

本文件基于仓库内 `OI-Start.cpp` 中实现的类与函数，给出简洁的使用说明和示例。请结合源码阅读以保证语义一致。

> 注意：本库禁止在任何正式竞赛或模拟赛中使用（见 README）。

---

## 目录
- ODT（珂朵莉树）
- Seg（线段树：支持区间乘与区间加）
- PST（主席树 / 持久化线段树）
- FastIO（快速输入输出）
- UF（并查集）
- funct（函数工具集）
- BIT（树状数组）
- Trie（字典树）
- Adj_list（图的邻接表 + 常用算法）

---

## ODT（珂朵莉树 / 颜色段均摊）
- 初始化：
  - `odt.init(l, r, v)`：将区间 [l,r] 初始化为值 v。建议先用 init 覆盖全部操作区间以避免间隙导致的未定义行为。
- 常用操作：
  - `assign(l, r, v)`：将 [l,r] 赋值为 v。
  - `update(l, r, v, op)`：对区间应用四则运算（op 为 '+','-','*','/'）。
  - `query(l, r)`：返回区间和（内部按段长度乘值累计）。
- 注意：ODT 在存在区间“间隙”时的 split 行为依赖于已插入区间，强烈建议先 init 覆盖完整区间。

示例：
```cpp
ODT odt;
odt.init(1, 100, 0);
odt.assign(3, 5, 10);
odt.update(2, 4, 2, '+'); // [2,4] 每个元素 +2
int s = odt.query(1, 10); // 返回区间和
```

---

## Seg（线段树 — 支持区间乘与区间加）
- 语义：聚合为区间和（sum）。支持两类懒标记：乘法（mul）和加法（add）。
- 模板类 `Seg<N>`，N 为元素数量：
  - `init()`：初始化内部数组（mul 初始为 1，add 初始为 0）。
  - `build(a)`：用数组 a[1..N] 建树。
  - `update(L,R,v,op)`：对区间 [L,R] 应用 op（支持 '*' 或 '+'）。
  - `query(L,R)`：返回区间和（long long）。
- 注意：
  - 仅支持 '+' 与 '*' 两类区间更新（'-' 可替换为加负数；'/' 未支持）。
  - 查询返回 long long，避免溢出风险；如需模运算需自行在实现中加入 Mod。
  - 乘法会影响先前挂起的加法（内部设计为先乘后加）。

示例：
```cpp
const int SZ = 1000;
Seg<SZ> seg;
int a[SZ+1] = {0}; // 1..SZ 初始化
seg.init();
seg.build(a);
// 区间乘以 3
seg.update(1, 10, 3, '*');
// 区间加 5
seg.update(2, 8, 5, '+');
long long sum = seg.query(1, 10);
```

---

## PST（持久化线段树 / 主席树）
- 模板类 `PST<N>`：
  - `build(l, r, rt, a)`：构建版本树（通常初始版本 rt=1）。
  - `update(l, r, rt, las, p, v)`：在 las 版本基础上修改位置 p 为 v，生成新版本 rt（需合理管理 cnt/根索引）。
  - `query(l, r, rt, p)`：在版本 rt 上查询位置 p 的值。
- 注意：PST 实现要求调用端管理根索引与版本号。

---

## FastIO（快速输入输出）
- 用法示例：
```cpp
int x, y;
in >> x >> y;
out << (x + y);
```
- 读字符串/字符/整型均支持。程序结束前可依赖输出对象析构（自动 flush）。

---

## UF（并查集）
- 用法：
```cpp
UF<100> uf;
uf.init();
uf.merge(x, y);
bool same = uf.query(x, y);
```

---

## funct（工具函数）
- 常用函数：
  - `gcd`, `lcm`
  - `power(a,b)` / `power(a,b,Mod)`
  - `conversion(x, s)` / `conversion(x, n)`（进制转换）
  - `prime(x)`（素数检测）
  - `dis(x1,y1,x2,y2)`（欧几里得距离）
- 注意：power/conversion 返回类型为 int，注意溢出与负数情况。

---

## BIT（树状数组）
- 单点修改，前缀和查询：
```cpp
BIT<100> bit;
bit.update(i, delta);
int pref = bit.query(i); // [1..i] 的和
```

---

## Trie（字典树）
- 用法：
```cpp
Trie<10000> trie;
trie.init();
trie.insert("hello");
int cnt = trie.find("hell"); // 返回匹配节点计数（依实现）
```
- 注意：实现用 ASCII 偏移 ' '（空格）为基准，字符范围假设在可打印 ASCII。

---

## Adj_list（图结构与常用算法）
- 用法：
```cpp
Adj_list<100> G;
G.Set(n);
G.add(u,v,w,true); // 无向图
auto dist = G.dijkstra(s);
bool hasNegCycle = G.SPFA(s); // true 表示检测到负环
int mst = G.Kurskal(); // 返回最小生成树权重或 -1（不连通）
auto topo = G.topsort();
```
- 注意：Kruskal 实现会遍历邻接表生成边列表，若输入为无向图会出现双边；调用端应按需控制。

---

## PBST（普通平衡树 — Splay 实现）

注意：这部分是我用 Gemini 3 写的。

* **语义**：动态维护一个有序多重集。基于 Splay 伸展树实现，所有操作均摊时间复杂度为 。
* **模板类 `PBST<N>**`，N 为最大节点数量：
* `init(INF)`：初始化树结构。`INF` 应设为大于题目给定数值范围的常数（如 `1e9`）。
* `insert(x)`：向集合中插入一个数 。若  已存在，则增加该值的计数（cnt）。
* `del(x)`：从集合中删除一个数 。若存在多个 ，仅删除一个。
* `rak(x)`：查询数值  在当前集合中的排名（定义为：小于  的数有多少个，结果加 1）。
* `kth(k)`：查询排名为  的数。**注意**：返回的是节点编号，获取数值需访问 `.tree[id].val`。
* `pre(x)`：查询  的前驱（定义为：小于  且最大的数）。
* `nex(x)`：查询  的后继（定义为：大于  且最小的数）。


* **注意**：
* **哨兵节点**：为了防止查询前驱、后继或排名时指针越向空节点（0），在 `init` 后**必须**手动插入两个极值：`insert(-INF)` 和 `insert(INF)`。
* **偏移量**：由于插入了两个哨兵，实际业务中的排名需进行修正。例如：真实排名等于 `rak(x) - 1`；查询第  小应查询 `kth(k + 1)`。
* **空间开销**：每个节点存储 5 个 `int` 指针/属性。 时空间占用约为 2MB 左右。



示例：

```cpp
const int MAXN = 100005;
PBST<MAXN> bst;
bst.init(1e9 + 7);

// 1. 必做：插入哨兵
bst.insert(-1e9); 
bst.insert(1e9);

// 2. 基础操作
bst.insert(10);
bst.insert(20);
bst.insert(10); // 支持重复值

// 3. 查询排名（需考虑左哨兵带来的 +1 偏移）
int r = bst.rak(10) - 1; // 结果为 1（比10小的只有-1e9）

// 4. 查询第 K 小
int node_id = bst.kth(2); // 找第2小（含哨兵则为-1e9, 10...）
int val = bst.tree[node_id].val; // 结果为 10

// 5. 前驱后继
int p = bst.pre(15); // 结果为 10
int n = bst.nex(15); // 结果为 20

// 6. 删除
bst.del(10);

```

---

## 最后说明
- 文档为简明使用说明，更多细节请阅读 `OI-Start.cpp` 源码。
- 若需将 Seg 扩展支持除法或其他组合操作，建议谨慎设计懒标记组合规则或限制为单一操作类别。

