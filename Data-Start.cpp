/******************************
*作者：Transparent-fish
*时间：2025.8.12
*******************************/
#include <bits/stdc++.h>
using namespace std;
#define int long long

namespace OI{
    struct ODT{
        struct node {
            int l, r;
            mutable int v;
            node(int _l, int _r = -1, int _v = 0) : l(_l), r(_r), v(_v) {}
            friend bool operator<(node a, node b) {
                return a.l < b.l;
            }
        };
        set<node>s;
        inline auto split(int pos){
            auto it=s.lower_bound(node(pos,0,0));
            if(it!=s.end()&&it->l==pos)return it;
            it--;
            int l=it->l,r=it->r,v=it->v;
            s.erase(it),s.insert(node(pos,r,v)).first;
        }
        inline void assign(int l,int r,int v){
            auto itr=split(r+1),itl=split(l);
            s.erase(itl,itr),s.insert(node(l,r,v));
        }
        /*初始化*/
        inline void init(int l,int r,int v){
            s.insert(node(l,r,v));
        }
        /*区间四则运算*/
        inline void update(int l,int r,int v,char op='+'){
            auto itr=split(r+1),itl=split(l);
            for(auto it=itl;it!=itr;it++){
                if(op=='+')it->v+=v;
                else if(op=='-')it->v-=v;
                else if(op=='*')it->v*=v;
                else if(op=='/')it->v/=v;
            }
        }
    };
};

signed main() {
     
    return 0;
}
