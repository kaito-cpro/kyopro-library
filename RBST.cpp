#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

template <class S,
          S (*op)(S, S),
          S (*e)()>
class RBST {
public:
    class node {
    public:
        S val;
        node* ch[2];
        int sz;
        S seg;

        node(S x) : val(x) {
            ch[0] = ch[1] = nullptr;
            sz = 1;
            seg = val;
        }
    };

    node* root = nullptr;

    RBST() {}
    RBST(vector<S>& v) { build(v); }
    RBST(set<S>& s) { build(s); }
    RBST(multiset<S>& s) { build(s); }

    node* merge(node* l, node* r) {
        if (l == nullptr) {
            if (l == root) root = r;
            return r;
        }
        else if (r == nullptr) {
            if (r == root) root = l;
            return l;
        }
        else if (_xor128() % (l->sz + r->sz) < l->sz) {
            if (r == root) root = l;
            l->ch[1] = merge(l->ch[1], r);
            return _update(l);
        }
        else {
            if (root == l) root = r;
            r->ch[0] = merge(l, r->ch[0]);
            return _update(r);
        }
    }

    // split to [0, k), [k, n)
    pair<node*, node*> split(node* n, int k) {
        if (n == nullptr) return make_pair(nullptr, nullptr);
        assert(0 <= k && k <= n->sz);

        if (k <= _size(n->ch[0])) {
            pair<node*, node*> m = split(n->ch[0], k);
            n->ch[0] = m.second;
            m.second = _update(n);
            return m;
        }
        else {
            pair<node*, node*> m = split(n->ch[1], k - _size(n->ch[0]) - 1);
            n->ch[1] = m.first;
            m.first = _update(n);
            return m;
        }
    }

    node* insert(int k, S x) {
        if (root == nullptr) {
            assert(k == 0);
            return root = new node(x);
        }
        else {
            assert(0 <= k && k <= root->sz);
            pair<node*, node*> m = split(root, k);
            return merge(merge(m.first, new node(x)), m.second);
        }
    }

    node* erase(int k) {
        pair<node*, node*> l = split(root, k);
        pair<node*, node*> r = split(l.second, 1);
        if (r.first == root) root = r.second;
        delete r.first;
        node* n = merge(l.first, r.second);
        if (_size(n) == 0) root = nullptr;
        return n;
    }

    S operator[](int k) { return _access(root, k)->val; }
    int size() { return _size(root); }
    bool empty() { return _size(root) == 0; }

    node* build(vector<S>& v) { return build(v, 0, v.size()); }
    node* build(vector<S>& v, int l, int r) {
        if (l >= r) return nullptr;
        int k = _xor128() % (r - l) + l;
        node* n = new node(v[k]);
        n->ch[0] = build(v, l, k);
        n->ch[1] = build(v, k + 1, r);
        return root = _update(n);
    }
    node* build(set<S>& s) {
        vector<S> v;
        for (S val : s) v.push_back(val);
        return build(v, 0, v.size());
    }
    node* build(multiset<S>& s) {
        vector<S> v;
        for (S val : s) v.push_back(val);
        return build(v, 0, v.size());
    }

    void clear() {
        _clear(root);
        root = nullptr;
    }

    S prod(int l, int r) {
        assert(0 <= l && r <= _size(root) && l <= r);
        return _prod(root, l, r);
    }
    S all_prod() { return prod(0, _size(root)); }

    // sort されていることが前提
    node* lower_bound(node* n, S x) {
        if (n == nullptr) return nullptr;
        if (x <= n->val) {
            node* res = lower_bound(n->ch[0], x);
            return res != nullptr ? res : n;
        }
        else {
            return lower_bound(n->ch[1], x);
        }
    }
    int lower_bound_index(node* n, S x) {
        if (n == nullptr) return 0;
        if (x <= n->val) {
            return lower_bound_index(n->ch[0], x);
        }
        else {
            return lower_bound_index(n->ch[1], x) + _size(n->ch[0]) + 1;
        }
    }

    // for debug
    void inorder(node* n) {
        cout << "[";
        _inorder(n);
        cout << "\b]" << endl;
    }

private:
    unsigned long _xor128(){
        static unsigned long x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        unsigned long t = x ^ (x << 11);
        x = y;  y = z;  z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
    
    int _size(node* n) { return n == nullptr ? 0 : n->sz;}
    S _seg(node* n) { return n == nullptr ? e() : n->seg; }

    node* _update(node* n) {
        n->sz = _size(n->ch[0]) + _size(n->ch[1]) + 1;
        n->seg = op(op(_seg(n->ch[0]), _seg(n->ch[1])), n->val);
        return n;
    }

    node* _access(node* n, int i) {
        assert(n != nullptr);
        if (_size(n->ch[0]) > i) return _access(n->ch[0], i);
        else if (_size(n->ch[0]) < i) return _access(n->ch[1], i - _size(n->ch[0]) - 1);
        else return n;
    }

    S _prod(node* n, int l, int r) {
        l = max(l, 0);
        r = min(r, _size(n));
        if (l >= r) return e();
        if (l == 0 && r == _size(n)) return _seg(n);

        S res = e();
        res = op(res, _prod(n->ch[0], l, r));
        res = op(res, _prod(n->ch[1], l - _size(n->ch[0]) - 1, r - _size(n->ch[0]) - 1));
        if (l <= _size(n->ch[0]) && _size(n->ch[0]) < r) res = op(res, n->val);
        return res;
    }

    void _clear(node* n) {
        if (n == nullptr) return;
        _clear(n->ch[0]);
        _clear(n->ch[1]);
        delete n;
    }

    void _inorder(node* n) {
        if (n == nullptr) return;
        if (n->ch[0] != nullptr) _inorder(n->ch[0]);
        cout << n->val << " ";
        if (n->ch[1] != nullptr) _inorder(n->ch[1]);
    }
};

using ll = long long;
const ll INF = numeric_limits<ll>::max() / 2;

using S = ll;  // tree に持たせるデータ
S op(S l, S r) { return min(l, r); }  // prod() の演算
S e() { return INF; }

int main() {
    // RBST の仕様
    //  * 初期化: vector, set, multiset または引数なしで初期化可能
    //  * データ操作: merge, split, insert, erase が可能
    //  * アクセス: tree[i]
    //  * その他: tree.root, tree.size(), tree.empty(), tree.clear()
    // このように tree に数値データを持たせて tree の形を操作できる.
    // また, tree に対して prod, lower_bound で計算ができる.
    //  * prod(l, r): op(tree[l], ..., tree[r - 1]) を求める
    //  * all_prod(): op(tree[0], ..., tree[tree.size() - 1]) を求める
    //  * lower_bound(root, x): root から二分探索で x 以上の最小の要素の "ポインタ" を求める
    //  * lower_bound_index(root, x): ポインタではなく "インデックス" を int で求める
    // ただし, lower_bound をするときはデータが sort されていることが前提で動く.
    // よって, tree を改変するときは lower_bound_index で挿入位置を求めて insert すること.
    // 「k 番目に小さい値」を管理させたいときは, build 時や挿入時に lower_bound_index で大小順を崩さないように気にする必要がある
    
    vector<ll> v{3, 1, 4, 1, 5, 9, 2};
    RBST<S, op, e> tree(v);  // vector で初期化

    for (int i = 0; i < tree.size(); ++i) cout << tree[i] << " ";
    cout << endl;
    // 出力: 3 1 4 1 5 9 2

    cout << tree.prod(1, 4) << endl;
    // 出力: min(tree[1], tree[2], tree[3]) = min(1, 4, 1) = 1

    tree.clear();

    set<ll> s;
    for (int el : v) s.insert(el);
    tree.build(s);  // set でビルド
    
    tree.inorder(tree.root);
    // 出力: [1 2 3 4 5 9]

    cout << tree.lower_bound_index(tree.root, 3) << endl;
    // 出力: 3 以上の最小 index なので 2
}