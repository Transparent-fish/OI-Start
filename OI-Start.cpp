/*
* 我错了喵 我再也不不写注释了喵
* 我实在是懒得压行了，这个是我早期的一个东西马蜂，实在是一言难尽，现在的代码一堆屎山，我实在是懒得重构了，等一位有缘人来重构吧。。。
* 你看 Git 历史记录就知道有多屎了。。。。。
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pan(x) isdigit(x)

namespace OI_Start {
    class ODT {
    protected:
        struct node {
            int l, r; mutable int v; node(int _l, int _r = -1, int _v = 0) :l(_l), r(_r), v(_v) {}
            friend bool operator<(node a, node b) { return a.l < b.l; }
        };
        set<node>s;
    public:
        auto split(int pos) { auto it = s.lower_bound(node(pos));if (it != s.end() && it->l == pos)return it;--it;int l = it->l, r = it->r, v = it->v;s.erase(it);s.insert(node(l, pos - 1, v));return s.insert(node(pos, r, v)).first; }
        void assign(int l, int r, int v) { auto itr = split(r + 1), itl = split(l);s.erase(itl, itr), s.insert(node(l, r, v)); }
        void init(int l, int r, int v) { s.insert(node(l, r, v)); }
        void update(int l, int r, int v, char op = '+') {
            auto itr = split(r + 1), itl = split(l);
            for (auto it = itl;it != itr;it++) { if (op == '+')it->v += v;else if (op == '-')it->v -= v;else if (op == '*')it->v *= v;else if (op == '/')it->v /= v; }
        }
        int query(int l, int r, char op = '+') {
            auto itr = split(r + 1), itl = split(l);int sum = 0;
            for (auto it = itl;it != itr;++it)sum += it->v * (it->r - it->l + 1);return sum;
        }
    };
    template<int N>
    class Seg {
    protected:
        ll tree[N << 2], add_[N << 2], mul_[N << 2];
        void Amul(int rt, ll v, int len) { tree[rt] *= v, mul_[rt] *= v, add_[rt] *= v; }
        void Aadd(int rt, ll v, int len) { tree[rt] += v * len, add_[rt] += v; }
    public:
        void init(char op_ = '+') { (void)op_;fill(tree, tree + (N << 2), 0), fill(add_, add_ + (N << 2), 0);for (int i = 0; i < (N << 2); ++i) { mul_[i] = 1; } }
        void pushup(int rt) { tree[rt] = tree[rt << 1] + tree[rt << 1 | 1]; }
        void pushdown(int rt, int l, int r) {
            int mid = (l + r) >> 1, llen = mid - l + 1, rlen = r - mid;
            if (mul_[rt] != 1) { Amul(rt << 1, mul_[rt], llen);Amul(rt << 1 | 1, mul_[rt], rlen);mul_[rt] = 1; }
            if (add_[rt] != 0) { Aadd(rt << 1, add_[rt], llen);Aadd(rt << 1 | 1, add_[rt], rlen);add_[rt] = 0; }
        }
        void build(int a[], int l = 1, int r = N, int rt = 1) {
            mul_[rt] = 1; add_[rt] = 0;
            if (l == r) { tree[rt] = a[l]; return; }
            int mid = (l + r) >> 1;
            build(a, l, mid, rt << 1), build(a, mid + 1, r, rt << 1 | 1), pushup(rt);
        }
        // 支持 '+' 和 '*' 两种操作（其它符号忽略）
        void update(int L, int R, int v, char op_, int l = 1, int r = N, int rt = 1) {
            if (L <= l && r <= R) {
                if (op_ == '*') { Amul(rt, v, r - l + 1); }
                else if (op_ == '+') { Aadd(rt, v, r - l + 1); }
                // 对于 '-' 和 '/' 暂不支持复合懒标记（可按需求扩展）
                return;
            }
            pushdown(rt, l, r);int mid = (l + r) >> 1;if (L <= mid) update(L, R, v, op_, l, mid, rt << 1);if (R > mid) update(L, R, v, op_, mid + 1, r, rt << 1 | 1);pushup(rt);
        }
        ll query(int L, int R, int l = 1, int r = N, int rt = 1) { if (L <= l && r <= R) return tree[rt];pushdown(rt, l, r);int mid = (l + r) >> 1;ll res = 0;if (L <= mid) res += query(L, R, l, mid, rt << 1);if (R > mid) res += query(L, R, mid + 1, r, rt << 1 | 1);return res; }
    };
    namespace FastIO {
        const int MAXX = 1 << 20;
        struct r {
            unsigned char buf[MAXX], * head, * till;
            r() : head(buf), till(buf) {}
            char gc() { if (head == till) { till = (head = buf) + fread(buf, 1, MAXX, stdin); if (head == till) return EOF; } return *head++; }
            template<typename T>  void re(T& x) { bool neg = 0; x = 0; char now = gc(); while (now != '-' && !pan(now)) now = gc(); if (now == '-') neg = 1, now = gc(); while (pan(now)) { x = x * 10 + (now - '0'); now = gc(); } if (neg) x = -x; }
            void re(char& ch) { ch = gc(); while (ch == '\r' || ch == '\n' || ch == ' ') ch = gc(); }
            void re(char* s) { char ch = gc(); while (ch == '\r' || ch == '\n' || ch == ' ') ch = gc(); while (ch != '\r' && ch != '\n' && ch != ' ' && ch != EOF) *s++ = ch, ch = gc(); *s = 0; }
            void re(string& s) { s.clear(); char ch = gc(); while (ch == '\r' || ch == '\n' || ch == ' ') ch = gc(); while (ch != '\r' && ch != '\n' && ch != ' ' && ch != EOF) s.push_back(ch), ch = gc(); }
            template<typename T> r& operator>>(T& x) { re(x); return *this; }
        };
        struct w {
            unsigned char buf[MAXX], * head;
            w() :head(buf) {}
            ~w() { flush(); }
            void flush() { if (head != buf) { fwrite(buf, 1, head - buf, stdout); head = buf; } }
            void pc(char ch) { if (head - buf == MAXX) { fwrite(buf, 1, MAXX, stdout); head = buf; } *head++ = ch; }
            void wr(int x) { if (x < 0) { pc('-'); x = -x; } static char buuf[40]; int len = 0; do { buuf[len++] = x % 10 + '0'; x /= 10; } while (x); while (len--) pc(buuf[len]); }
            void wr(char ch) { pc(ch); }
            void wr(const char* s) { while (*s) pc(*s++); }
            void wr(const string& s) { for (char ch : s) pc(ch); }
            template<typename T> w& operator<<(T x) { wr(x); return *this; }
        };
        r in;
        w out;
    }using FastIO::in;
    using FastIO::out;
#undef pan
    template<int N>//主席树
    class PST {
    protected:
        int cnt;
        struct node {
            int l, r, v;
        }tree[N * 4 + 25 * N];
    public:
        void build(int l, int r, int rt, int a[]) {
            if (rt == 1) cnt = 1;
            if (l == r) { tree[rt].v = a[l]; return; }
            int mid = (l + r) >> 1;tree[rt].l = ++cnt; build(l, mid, tree[rt].l, a);tree[rt].r = ++cnt; build(mid + 1, r, tree[rt].r, a);
        }
        void update(int l, int r, int rt, int las, int p, int v) {
            tree[rt] = tree[las];
            if (l == r) { tree[rt].v = v; return; }
            int mid = (l + r) >> 1;
            if (p <= mid) { tree[rt].l = ++cnt;update(l, mid, tree[rt].l, tree[las].l, p, v); }
            else { tree[rt].r = ++cnt;update(mid + 1, r, tree[rt].r, tree[las].r, p, v); }
        }
        int query(int l, int r, int rt, int v) { if (l == r) { return tree[rt].v; }int mid = l + r >> 1;if (v <= mid) { return query(l, mid, tree[rt].l, v); } else { return query(mid + 1, r, tree[rt].r, v); } }
    };
    template<int N>
    class UF {
    protected:
        int f[N]; int find(int x) { if (f[x] == x) { return x; }return f[x] = find(f[x]); }
    public:
        void init() { for (int i = 1;i <= N;i++) { f[i] = i; } }
        void merge(int x, int y) { int fx = find(x), fy = find(y);f[fx] = fy; }
        bool query(int x, int y) { int fx = find(x);int fy = find(y);return fx == fy; }
    };
    class funct {
    public:
        int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
        int lcm(int a, int b) { return a * b / gcd(a, b); }
        int power(int a, int b, int Mod = -1) { int ans = 1;for (; b; b >>= 1) { if (b & 1) { ans = ans * a;if (Mod != -1) { ans %= Mod; } }a = a * a;if (Mod != -1) { a %= Mod; } }return ans; }
        int conversion(int x, string s) { reverse(s.begin(), s.end());int ans = 0;for (int i = 0; i < s.size(); i++) { int u;if (s[i] > '9') { u = s[i] - '7'; } else { u = s[i] - '0'; }ans += power(x, i) * u; }return ans; }
        string conversion(int x, int n) { string ans = "";for (;n;) { int u = n % x;if (u >= 10) { u += '7'; } else { u += '0'; }ans += (char)u;n /= x; }reverse(ans.begin(), ans.end());return ans; }
        int prime(int x) { if (x <= 1) { return 0; }for (int i = 2; i * i <= x; i++) { if (x % i == 0) { return 0; } }return 1; }
        double dis(double x_1, int y_1, int x_2, int y_2) { return sqrt((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2)); }
    };
    template<int N>
    class BIT {
    protected:
        int tree[N + 5];int lowbit(int x) { return x & -x; }
    public:
        void update(int x, int k) { for (int i = x; i <= N; i += lowbit(i)) { tree[i] += k; } }
        int query(int x) { int ans = 0;for (int i = x; i >= 1; i -= lowbit(i)) { ans += tree[i]; }return ans; }
    };
    template<int N>
    class Trie {
    protected:
        int tree[N][128], cnt[N], tot;int Get(char ch) { return ch - ' '; }
    public:
        void init() {
            tot = 0, cnt[0] = 0;
            for (int j = 0; j < 128; j++) tree[0][j] = 0;
        }
        void insert(string s) { int u = 0;for (int i = 0; i < s.size(); i++) { int v = Get(s[i]);if (tree[u][v] == 0) { tree[u][v] = ++tot; }u = tree[u][v];cnt[u]++; } }
        int find(string s) { int u = 0;for (int i = 0; i < s.size(); i++) { int v = Get(s[i]);if (tree[u][v] == 0) { return 0; }u = tree[u][v]; }return cnt[u]; }
    };
    template<int LEN>
    class Adj_list {
    protected:
        int n;struct Node { int v, w; };vector<Node>e[LEN + 2];
        //Kurskal Function
        int f[LEN + 1];
        int find(int x) {
            if (f[x] == x)return x;
            return f[x] = find(f[x]);
        }
        struct Side {
            int u, v, w;
            friend bool operator <(Side a0, Side a1) { return a0.w < a1.w; }
        };
    public:
        void Set(int _n) { n = _n; }
        const int Inf = INT_MAX;
        void clear() { for (int i = 1; i <= LEN; i++) { e[i].clear(); } }
        void add(int u, int v, int w, bool undirected = false) { e[u].push_back({ v, w });if (undirected) { e[v].push_back({ u, w }); } }
        vector<int> dijkstra(int s) { vector<int>dist(n + 1, Inf);dist[s] = 0;vector<bool>vis(n + 1, false);priority_queue<pair<int, int> >pq;pq.push({ 0, s });while (!pq.empty()) { int tmp = pq.top().second;pq.pop();if (vis[tmp]) { continue; }vis[tmp] = true;for (auto [v, w] : e[tmp]) { if (dist[v] > dist[tmp] + w) { dist[v] = dist[tmp] + w;pq.push({ -dist[v], v }); } } }return dist; }
        bool SPFA(int s) { queue<int>q;q.push(s);vector<int>dist(n + 1, Inf);dist[s] = 0;vector<int>cnt(n + 1, 0);cnt[s] = 1;while (!q.empty()) { int u = q.front();q.pop();for (auto [v, w] : e[u]) { if (dist[v] > dist[u] + w) { dist[v] = dist[u] + w;q.push(v);cnt[v]++;if (cnt[v] > n) { return true; } } } }return false; }
        int Kurskal() { for (int i = 1; i <= n; i++) { f[i] = i; }vector<Side>side;for (int i = 1; i <= n; i++) { for (auto [v, w] : e[i]) { side.push_back({ i, v, w }); } }sort(side.begin(), side.end());int ans = 0, cnt = 0;for (Side i : side) { int x = i.u, y = i.v;int fx = find(x), fy = find(y);if (fx != fy) { f[fx] = fy;cnt++;ans += i.w; } }if (cnt == n - 1) { return ans; }return -1; }
        vector<int> topsort() { vector<int>res;vector<int>in_(n + 1, 0);for (int i = 1; i <= n; i++) { for (auto j : e[i]) { in_[j.v]++; } }queue<int>q;for (int i = 1; i <= n; i++) { if (in_[i] == 0)q.push(i); }while (!q.empty()) { int u = q.front();q.pop();res.push_back(u);for (auto i : e[u]) { in_[i.v]--;if (in_[i.v] == 0)q.push(i.v); } }return res; }
    };
    template<int N>
    class PBST { // 基于 Splay 伸展树实现的普通平衡树
    public:
        int INF, cnt, rt; // INF: 无穷大边界, cnt: 当前节点总数, rt: 根节点编号
        struct node {
            int ch[2], fa, val, cnt, siz;
            // ch[0/1]: 左右儿子, fa: 父亲, val: 节点权值, cnt: 同值个数, siz: 子树大小
        } tree[N];

        // 初始化：清空树并设置无穷大边界值
        void init(int __inf__) { INF = __inf__; rt = cnt = 0; }

        // 更新节点信息：子树大小 = 左子树大小 + 右子树大小 + 自身重复个数
        void pushup(int x) {
            if (!x) return;
            tree[x].siz = tree[tree[x].ch[0]].siz + tree[tree[x].ch[1]].siz + tree[x].cnt;
        }

        // 判断身份：判断节点 x 是父亲的左儿子(0)还是右儿子(1)
        int Get(int x) { return x == tree[tree[x].fa].ch[1]; }

        // 基础旋转 (Rotate)：平衡树的核心，将 x 向上旋转一层，同时保持 BST 性质
        void r(int x) {
            int y = tree[x].fa, z = tree[y].fa, sk = Get(x);
            tree[y].ch[sk] = tree[x].ch[sk ^ 1]; // x 的内侧儿子过继给 y
            if (tree[x].ch[sk ^ 1]) tree[tree[x].ch[sk ^ 1]].fa = y;
            tree[x].ch[sk ^ 1] = y, tree[y].fa = x; // x 变成 y 的父亲
            tree[x].fa = z; // x 接上原先祖父 z
            if (z) tree[z].ch[y == tree[z].ch[1]] = x;
            pushup(y), pushup(x); // 旋转后由下至上更新 siz
        }

        // 伸展操作 (Splay)：通过旋转将 x 提升到目标 k 的下方。k=0 时 x 成为新根
        void splay(int x, int k) {
            for (; tree[x].fa != k; ) {
                int y = tree[x].fa, z = tree[y].fa;
                if (z != k) { // 双旋判定：如果祖父不是目标，根据形状选择先转谁
                    (Get(x) == Get(y)) ? r(y) : r(x); // 一字形先转父，之字形转自身
                }
                r(x); // 最后都要转自身
            }
            if (k == 0) rt = x; // 如果 k 为 0，更新全局根节点
        }

        // 插入操作：存在则 cnt++, 不存在则新建，最后均需 splay 到根部维护复杂度
        void insert(int x) {
            int root = rt, fa = 0;
            while (root && tree[root].val != x) fa = root, root = tree[root].ch[x > tree[root].val];
            if (root) tree[root].cnt++; // 权值已存在，直接增加计数
            else { // 新建节点
                root = ++cnt; tree[root].val = x; tree[root].fa = fa; tree[root].cnt = 1;
                if (fa) tree[fa].ch[x > tree[fa].val] = root;
            }
            pushup(root); pushup(fa); splay(root, 0);
        }

        // 查询排名：查询权值 x 在集合中的排名（比其小的个数 + 1）
        int rak(int x) {
            int root = rt, res = 0;
            while (root) {
                if (x < tree[root].val) root = tree[root].ch[0];
                else {
                    res += tree[tree[root].ch[0]].siz; // 累加左子树大小
                    if (x == tree[root].val) { splay(root, 0); return res + 1; }
                    res += tree[root].cnt; // 累加当前节点个数
                    root = tree[root].ch[1];
                }
            }
            return res + 1;
        }

        // 查询数值：找到排名为 x 的节点并返回其编号
        int kth(int x) {
            int root = rt;
            while (root) {
                if (x <= tree[tree[root].ch[0]].siz) root = tree[root].ch[0];
                else {
                    x -= tree[tree[root].ch[0]].siz + tree[root].cnt;
                    if (x <= 0) { splay(root, 0); return root; }
                    root = tree[root].ch[1];
                }
            }
            return -1;
        }

        // 前驱：小于 x 且最大的数
        int pre(int x) {
            int root = rt, res = -INF;
            while (root) {
                if (x <= tree[root].val) root = tree[root].ch[0];
                else res = max(res, tree[root].val), root = tree[root].ch[1];
            }
            return res;
        }

        // 后继：大于 x 且最小的数
        int nex(int x) {
            int root = rt, res = INF;
            while (root) {
                if (x >= tree[root].val) root = tree[root].ch[1];
                else res = min(res, tree[root].val), root = tree[root].ch[0];
            }
            return res;
        }

        // 定位：找到权值为 x 的节点并将其旋转到根部
        void find(int x) {
            int root = rt;
            while (root && tree[root].val != x) root = tree[root].ch[x > tree[root].val];
            if (root) splay(root, 0);
        }

        // 删除操作：利用前驱后继将目标隔离，然后通过 Splay 特性安全删除
        void del(int x) {
            find(x); // 先把 x 旋到根
            if (tree[rt].cnt > 1) { tree[rt].cnt--; pushup(rt); return; } // 重复值只减计数
            // 下面利用 splay 隔离目标：找到左子树最右节点和右子树最左节点
            int l = tree[rt].ch[0], r = tree[rt].ch[1];
            while (tree[l].ch[1]) l = tree[l].ch[1];
            while (tree[r].ch[0]) r = tree[r].ch[0];
            splay(l, 0); splay(r, l); // 将 x 挤到 r 的左儿子位置，此时 x 必为叶子
            tree[r].ch[0] = 0; // 直接抹除 x 节点
            pushup(r), pushup(l);
        }
    };
}using namespace OI_Start;

int main() {

    return 0;
}