#include <bits/stdc++.h>
using namespace std;
#define int long long

namespace OI_Start {
    /*-------------------Transparent-fish Start-------------------*/
    class ODT {
    protected:
        struct node {
            int l, r; mutable int v; node(int _l, int _r = -1, int _v = 0) :l(_l), r(_r), v(_v) {}
            friend bool operator<(node a, node b) { return a.l < b.l; }
        };
        set<node>s;
    public:
        inline auto split(int pos) {
            auto it = s.lower_bound(node(pos));if (it != s.end() && it->l == pos)return it;--it;int l = it->l, r = it->r, v = it->v;s.erase(it);s.insert(node(l, pos - 1, v));return s.insert(node(pos, r, v)).first;
        }
        inline void assign(int l, int r, int v) { auto itr = split(r + 1), itl = split(l);s.erase(itl, itr), s.insert(node(l, r, v)); }
        inline void init(int l, int r, int v) { s.insert(node(l, r, v)); }
        inline void update(int l, int r, int v, char op = '+') {
            auto itr = split(r + 1), itl = split(l);
            for (auto it = itl;it != itr;it++) { if (op == '+')it->v += v;else if (op == '-')it->v -= v;else if (op == '*')it->v *= v;else if (op == '/')it->v /= v; }
        }
        inline int query(int l, int r, char op = '+') {
            auto itr = split(r + 1), itl = split(l);int sum = 0;
            for (auto it = itl;it != itr;++it)sum += it->v * (it->r - it->l + 1);return sum;
        }
    };
    template<int N>
    class Seg {
    protected:
        int tree[N << 2], laz[N << 2];char op[N << 2];
        inline void init_op(int& val, int v, char op_, int len = 1) {
            if (op_ == '+')val += v * len;else if (op_ == '-')val -= v * len;else if (op_ == '*')val *= v;else if (op_ == '/')val /= v;
        }
    public:
        inline void init(char op_ = '+') { fill(op, op + (N << 2), op_); }
        inline void pushup(int rt) {
            if (op[rt] == '+')tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
            else if (op[rt] == '-')tree[rt] = tree[rt << 1] - tree[rt << 1 | 1];
            else if (op[rt] == '*')tree[rt] = tree[rt << 1] * tree[rt << 1 | 1];
            else if (op[rt] == '/')tree[rt] = tree[rt << 1] / tree[rt << 1 | 1];
        }
        inline void pushdown(int rt, int l, int r) {
            if (laz[rt] == 0)return;int mid = (l + r) >> 1;int llen = mid - l + 1;int rlen = r - mid;
            init_op(tree[rt << 1], laz[rt], op[rt], llen);
            if (op[rt] == '+' || op[rt] == '-')laz[rt << 1] += laz[rt];else init_op(laz[rt << 1], laz[rt], op[rt]);
            init_op(tree[rt << 1 | 1], laz[rt], op[rt], rlen);
            if (op[rt] == '+' || op[rt] == '-')laz[rt << 1 | 1] += laz[rt];else init_op(laz[rt << 1 | 1], laz[rt], op[rt]);laz[rt] = 0;
        }
        inline void build(int a[], int l = 1, int r = N, int rt = 1) {
            if (l == r) { tree[rt] = a[l];laz[rt] = 0;return; }int mid = (l + r) >> 1;
            build(a, l, mid, rt << 1);build(a, mid + 1, r, rt << 1 | 1);pushup(rt);
        }
        inline void update(int L, int R, int v, char op_, int l = 1, int r = N, int rt = 1) {
            if (L <= l && r <= R) {
                op[rt] = op_;init_op(tree[rt], v, op_, r - l + 1);
                if (op_ == '+' || op_ == '-')laz[rt] += v;else init_op(laz[rt], v, op_);return;
            }
            pushdown(rt, l, r);int mid = (l + r) >> 1;
            if (L <= mid)update(L, R, v, op_, l, mid, rt << 1);if (R > mid)update(L, R, v, op_, mid + 1, r, rt << 1 | 1);pushup(rt);
        }
        inline int query(int L, int R, int l = 1, int r = N, int rt = 1) {
            if (L <= l && r <= R)return tree[rt];pushdown(rt, l, r);int mid = (l + r) >> 1;
            if (op[rt] == '+') { int res = 0;if (L <= mid)res += query(L, R, l, mid, rt << 1);if (R > mid)res += query(L, R, mid + 1, r, rt << 1 | 1);return res; }
            else if (op[rt] == '-') { int res = 0;if (L <= mid)res += query(L, R, l, mid, rt << 1);if (R > mid)res -= query(L, R, mid + 1, r, rt << 1 | 1);return res; }
            else if (op[rt] == '*') { int res = 1;if (L <= mid)res *= query(L, R, l, mid, rt << 1);if (R > mid)res *= query(L, R, mid + 1, r, rt << 1 | 1);return res; }
            else if (op[rt] == '/') { int res = 1;if (L <= mid)res = query(L, R, l, mid, rt << 1);if (R > mid) { int r_ = query(L, R, mid + 1, r, rt << 1 | 1);if (r_ != 0)res /= r_; }return res; }
            else return 0;
        }
    };
    /*-------------------Transparent-fish End-------------------*/
    /*-------------------zengyanbin1130 Start-------------------*/
    template<int N>
    class UF {
    protected:
        int f[N];inline int find(int x) { if (f[x] == x) { return x; }return f[x] = find(f[x]); }
    public:
        inline void init() { for (int i = 1;i <= N;i++) { f[i] = i; } }
        inline void merge(int x, int y) { int fx = find(x), fy = find(y);f[fx] = fy; }
        inline bool query(int x, int y) { int fx = find(x);int fy = find(y);return fx == fy; }
    };
    class funct {
    public:
        /*最小公倍数*/
        int lcm(int a, int b) { return a * b / __gcd(a, b); }
        /*快速幂*/
        int power(int a, int b, int Mod = -1) { int ans = 1;for (; b; b >>= 1) { if (b & 1) { ans = ans * a;if (Mod != -1) { ans %= Mod; } }a = a * a;if (Mod != -1) { a %= Mod; } }return ans; }
        /*进制转换*/int conversion(int x, string s) { reverse(s.begin(), s.end());int ans = 0;for (int i = 0; i < s.size(); i++) { int u;if (s[i] > '9') { u = s[i] - '7'; } else { u = s[i] - '0'; }ans += power(x, i) * u; }return ans; }
        string conversion(int x, int n) { string ans = "";for (;n;) { int u = n % x;if (u >= 10) { u += '7'; } else { u += '0'; }ans += (char)u;n /= x; }reverse(ans.begin(), ans.end());return ans; }
        /*判断质数*/int prime(int x) { if (x <= 1) { return 0; }for (int i = 2; i * i <= x; i++) { if (x % i == 0) { return 0; } }return 1; }
        /*两点距离公式*/double dis(double x_1, int y_1, int x_2, int y_2) { return sqrt((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2)); }
    };
    /*-------------------zengyanbin1130 End-------------------*/
}using namespace Data_Start;

signed main() {

    return 0;
}
