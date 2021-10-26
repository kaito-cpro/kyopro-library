#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

// N 頂点 M 辺のトポロジカルソート
// 計算量 O(N + M)
// 辞書順最小にするなら log が付く

int main() {
    int N, M;  cin >> N >> M;
    vector<int> indeg(N);  // 頂点の入次数
    vector<vector<int>> edges(N);
    for (int i = 0; i < M; ++i) {
        int u, v;  cin >> u >> v;
        --u;  --v;
        ++indeg[v];
        edges[u].push_back(v);
    }
    
    // 辞書順最小でなくていいなら単なる vector でもよい
    priority_queue<int, vector<int>, greater<int>> que;  // 入次数が 0 になった頂点の heap_que
    for (int u = 0; u < N; ++u) {
        if (indeg[u] == 0) que.push(u);
    }
    
    vector<int> ans;
    while (!que.empty()) {
        int u = que.top();  que.pop();
        ans.push_back(u);
        for (int v : edges[u]) {
            --indeg[v];
            if (indeg[v] == 0) que.push(v);
        }
    }
    
    if (ans.size() != N) cout << -1 << endl;
    else {
        for (int i = 0; i < N; ++i) cout << ans[i] + 1 << (i == N - 1 ? "\n" : " ");
    }
}