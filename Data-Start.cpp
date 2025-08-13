/******************************
作者：Transparent-fish & zengyanbin1130
*******************************/
#include <bits/stdc++.h>
using namespace std;
#define int long long
namespace Data_Start {
	struct ODT {
		struct node {
			int l, r;
			mutable int v;
			node(int _l, int _r = -1, int _v = 0) : l(_l), r(_r), v(_v) {}
			friend bool operator<(node a, node b) {
				return a.l < b.l;
			}
		};
		set<node>s;
		inline auto split(int pos) {
			auto it = s.lower_bound(node(pos, 0, 0));
			if (it != s.end() && it->l == pos)return it;
			it--;
			int l = it->l, r = it->r, v = it->v;
			s.erase(it), s.insert(node(pos, r, v)).first;
		}
		inline void assign(int l, int r, int v) {
			auto itr = split(r + 1), itl = split(l);
			s.erase(itl, itr), s.insert(node(l, r, v));
		}
		/*初始化*/
		inline void init(int l, int r, int v) {
			s.insert(node(l, r, v));
		}
		/*区间四则运算*/
		inline void update(int l, int r, int v, char op = '+') {
			auto itr = split(r + 1), itl = split(l);
			for (auto it = itl;it != itr;it++) {
				if (op == '+')it->v += v;
				else if (op == '-')it->v -= v;
				else if (op == '*')it->v *= v;
				else if (op == '/')it->v /= v;
			}
		}
	};
	template<int N>
	struct Seg {
		int tree[N << 2], laz[N << 2];
		char op[N << 2];
		/*pushup*/
		void pushup(int rt, char op = '+') {
			if (op == '+')tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
			else if (op == '-')tree[rt] = tree[rt << 1] - tree[rt << 1 | 1];
			else if (op == '*')tree[rt] = tree[rt << 1] * tree[rt << 1 | 1];
			else if (op == '/')tree[rt] = tree[rt << 1] / tree[rt << 1 | 1];
		}
		/*pushdown*/
		void pushdown(int rt, int l, int r) {
			if (laz[rt] == 0) return;
			int mid = (l + r) >> 1;
			char op_ = op[rt];
			if (op_ == '+') {
				tree[rt << 1] += laz[rt] * (mid - l + 1);
				laz[rt << 1] += laz[rt];
			}
			else if (op_ == '-') {
				tree[rt << 1] -= laz[rt] * (mid - l + 1);
				laz[rt << 1] -= laz[rt];
			}
			else if (op_ == '*') {
				tree[rt << 1] *= laz[rt];
				laz[rt << 1] *= laz[rt];
			}
			else if (op_ == '/') {
				tree[rt << 1] /= laz[rt];
				laz[rt << 1] /= laz[rt];
			}
			if (op_ == '+') {
				tree[rt << 1 | 1] += laz[rt] * (r - mid);
				laz[rt << 1 | 1] += laz[rt];
			}
			else if (op_ == '-') {
				tree[rt << 1 | 1] -= laz[rt] * (r - mid);
				laz[rt << 1 | 1] -= laz[rt];
			}
			else if (op_ == '*') {
				tree[rt << 1 | 1] *= laz[rt];
				laz[rt << 1 | 1] *= laz[rt];
			}
			else if (op_ == '/') {
				tree[rt << 1 | 1] /= laz[rt];
				laz[rt << 1 | 1] /= laz[rt];
			}
			laz[rt] = 0;
		}
		/*build*/
		void build(int a[], int l = 1, int r = N, int rt = 1) {
			if (l == r) {
				tree[rt] = a[l];
				return;
			}
			int mid = (l + r) >> 1;
			build(a, l, mid, rt << 1);
			build(a, mid + 1, r, rt << 1 | 1);
			pushup(rt, op[rt]);
		}
		/*update*/
		void update(int l, int r, int L, int R, int rt, int v, char op_) {
			if (L <= l && R <= r) {
				op[rt] = op_;
				if (op_ == '+') {
					tree[rt] += v * (r - l + 1);
					laz[rt] += v;
				}
				else if (op_ == '-') {
					tree[rt] -= v * (r - l + 1);
					laz[rt] -= v;
				}
				else if (op_ == '*') {
					tree[rt] *= v * (r - l + 1);
					laz[rt] *= v;
				}
				else if (op_ == '/') {
					tree[rt] /= v * (r - l + 1);
				}
			}
			pushdown(rt, l, r);
			int mid = l + r >> 1;
			if (L <= mid) update(l, mid, L, R, rt << 1, v, op_);
			if (R > mid) update(l, mid, L, R, rt << 1 | 1, v, op_);
			pushup(rt, op[rt]);
		}
		/*query*/
		int query(int l, int r, int L, int R, int rt) {

		}
	};
};

signed main() {

	return 0;
}
