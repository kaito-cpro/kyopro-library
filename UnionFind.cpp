#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using ll = long long;

class UnionFind {
public:
    vector<int> par;  // 各頂点の親
    vector<int> rank;  // 各頂点の深さ
    vector<int> sz;  // 各頂点の属する頂点の個数
    int sum_sz;  // 独立集合の個数

    // コンストラクタ
    UnionFind(int n) {
        for (int i = 0; i < n; ++i) {
            par.push_back(i);
            rank.push_back(0);
            sz.push_back(1);
        }
        sum_sz = n;
    }

    // 木の根を求める
    int leader(int x) {
        if (par[x] == x) return x;
        else return par[x] = leader(par[x]);
    }

    // x と y の属する集合を併合
    void merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return;
        // 深さが小さいものから大きい方の根へ辺を張る
        if (rank[x] < rank[y]) par[x] = y;
        else if (rank[x] > rank[y]) par[y] = x;
        else {
            par[y] = x;
            ++rank[x];
        }
        --sum_sz;
        sz[x] = sz[y] = sz[x] + sz[y];
    }

    // x と y が同じ木に属するかの判定
    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    // 頂点 x が属する集合の頂点数
    int size(int x) {
        return sz[leader(x)];
    }

    // 独立した集合の個数(島の個数)
    int size() {
        return sum_sz;
    }
};

int main() {
    int N, Q, P, A, B;
    cin >> N >> Q;

    UnionFind uf(N);

    for (int i = 0; i < Q; ++i) {
        cin >> P >> A >> B;
        if (P == 0) {
            uf.merge(A, B);
        }
        else {
            cout << (uf.same(A, B) ? "Yes" : "No") << endl;
        }
    }
}
