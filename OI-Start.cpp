#include <bits/stdc++.h>
using namespace std;
#define int long long
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
        auto split(int pos) {
            auto it = s.lower_bound(node(pos));if (it != s.end() && it->l == pos)return it;--it;int l = it->l, r = it->r, v = it->v;s.erase(it);s.insert(node(l, pos - 1, v));return s.insert(node(pos, r, v)).first;
        }
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
        int tree[N << 2], laz[N << 2];char op[N << 2];
        void init_op(int& val, int v, char op_, int len = 1) {
            if (op_ == '+')val += v * len;else if (op_ == '-')val -= v * len;else if (op_ == '*')val *= v;else if (op_ == '/')val /= v;
        }
    public:
        void init(char op_ = '+') { fill(op, op + (N << 2), op_); }
        void pushup(int rt) {
            if (op[rt] == '+')tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
            else if (op[rt] == '-')tree[rt] = tree[rt << 1] - tree[rt << 1 | 1];
            else if (op[rt] == '*')tree[rt] = tree[rt << 1] * tree[rt << 1 | 1];
            else if (op[rt] == '/')tree[rt] = tree[rt << 1] / tree[rt << 1 | 1];
        }
        void pushdown(int rt, int l, int r) {
            if (laz[rt] == 0)return;int mid = (l + r) >> 1;int llen = mid - l + 1;int rlen = r - mid;
            init_op(tree[rt << 1], laz[rt], op[rt], llen);
            if (op[rt] == '+' || op[rt] == '-')laz[rt << 1] += laz[rt];else init_op(laz[rt << 1], laz[rt], op[rt]);
            init_op(tree[rt << 1 | 1], laz[rt], op[rt], rlen);
            if (op[rt] == '+' || op[rt] == '-')laz[rt << 1 | 1] += laz[rt];else init_op(laz[rt << 1 | 1], laz[rt], op[rt]);laz[rt] = 0;
        }
        void build(int a[], int l = 1, int r = N, int rt = 1) {
            if (l == r) { tree[rt] = a[l];laz[rt] = 0;return; }int mid = (l + r) >> 1;
            build(a, l, mid, rt << 1);build(a, mid + 1, r, rt << 1 | 1);pushup(rt);
        }
        void update(int L, int R, int v, char op_, int l = 1, int r = N, int rt = 1) {
            if (L <= l && r <= R) {
                op[rt] = op_;init_op(tree[rt], v, op_, r - l + 1);
                if (op_ == '+' || op_ == '-')laz[rt] += v;else init_op(laz[rt], v, op_);return;
            }
            pushdown(rt, l, r);int mid = (l + r) >> 1;
            if (L <= mid)update(L, R, v, op_, l, mid, rt << 1);if (R > mid)update(L, R, v, op_, mid + 1, r, rt << 1 | 1);pushup(rt);
        }
        int query(int L, int R, int l = 1, int r = N, int rt = 1) {
            if (L <= l && r <= R)return tree[rt];pushdown(rt, l, r);int mid = (l + r) >> 1;
            if (op[rt] == '+') { int res = 0;if (L <= mid)res += query(L, R, l, mid, rt << 1);if (R > mid)res += query(L, R, mid + 1, r, rt << 1 | 1);return res; }
            else if (op[rt] == '-') { int res = 0;if (L <= mid)res += query(L, R, l, mid, rt << 1);if (R > mid)res -= query(L, R, mid + 1, r, rt << 1 | 1);return res; }
            else if (op[rt] == '*') { int res = 1;if (L <= mid)res *= query(L, R, l, mid, rt << 1);if (R > mid)res *= query(L, R, mid + 1, r, rt << 1 | 1);return res; }
            else if (op[rt] == '/') { int res = 1;if (L <= mid)res = query(L, R, l, mid, rt << 1);if (R > mid) { int r_ = query(L, R, mid + 1, r, rt << 1 | 1);if (r_ != 0)res /= r_; }return res; }
            else return 0;
        }
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
        void build(int l, int r, int rt, int a[]) { if (l == r) { tree[rt].v = a[l];return; }int mid = l + r >> 1;tree[rt].l = ++cnt;build(l, mid, tree[rt].l, a);tree[rt].r = ++cnt;build(mid + 1, r, tree[rt].r, a); }
        void update(int l, int r, int rt, int las, int p, int v) { if (l == r) { tree[rt].v = v;return; }int mid = l + r >> 1;if (p <= mid) { tree[rt].r = tree[las].r, tree[rt].l = ++cnt;update(l, mid, tree[rt].l, tree[las].l, p, v); } else { tree[rt].l = tree[las].l, tree[rt].r = ++cnt;update(mid + 1, r, tree[rt].r, tree[las].r, p, v); } }
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
        int lcm(int a, int b) { return a * b / __gcd(a, b); }
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
        void init() { for (int i = 0; i <= tot; i++) { cnt[i] = 0;for (int j = 0; j < 128; j++) { tree[i][j] = 0; } }tot = 0; }
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
    /*-------------------zengyanbin1130 End-------------------*/
}using namespace OI_Start;

signed main() {

    return 0;
}
