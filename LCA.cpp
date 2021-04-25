#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

class LCA {
public:
    LCA(int n) : LCA(vector<vector<int>>(n)) {}
    LCA(vector<vector<int>> _edges) : edges(_edges) {
        N = _edges.size();
        LOG_N = ceil(log2(N)) + 1;
        parent.resize(LOG_N, vector<int>(N));
        depth.resize(N, -1);
    }
    
    void add_edge(int u, int v) {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    
    int lca(int u, int v) {
        if (!initialized) _init();
        
        // u と v を同じ高さにする
        if (depth[u] > depth[v]) swap(u, v);
        int d = depth[v] - depth[u], k = 0;
        while (d) {
            if (d & 1) v = parent[k][v];
            ++k;
            d >>= 1;
        }
        if (u == v) return u;
        
        // 最小共通祖先の頂点を越えないように u と v を二分探索で上げていく
        for (int k = LOG_N - 1; k >= 0; --k) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
    
private:
    int N, LOG_N;
    vector<vector<int>> edges;
    vector<vector<int>> parent;  // parent[k][v] := 頂点 v から 2^k 個上にたどった頂点(root より上の頂点は -1 とみなす)
    vector<int> depth;  // depth[v] := 頂点 v の深さ(depth[root] := 0)
    bool initialized = false;
    
    // root から潜って depth[v] と parent[0][v] を初期化
    void _dfs(int v = 0, int p = -1, int d = 0) {
        parent[0][v] = p;
        depth[v] = d;
        for (int nv : edges[v]) {
            if (depth[nv] != -1) continue;
            _dfs(nv, v, d + 1);
        }
    }
    
    void _init() {
        _dfs();
        // parent[k][v] の初期化
        for (int k = 0; k < LOG_N - 1; ++k) {
            for (int v = 0; v < N; ++v) {
                if (parent[k][v] == -1) parent[k + 1][v] = -1;
                else parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
        initialized = true;
    }
};

int main() {
    // 根付き木について最小共通祖先を求める
    // 計算量: 初期化に O(NlogN), lca(u, v) に O(logN)
    int N = 5;
    LCA graph(N);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(1, 4);
    cout << graph.lca(2, 4) << endl;
}