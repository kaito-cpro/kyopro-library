#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll LINF = 1LL << 60;

int main() {
    int N = 12;
    vector<vector<ll>> dist(N, vector<ll>(N));  // 各 N 頂点間の最短距離

    // Travelling Salesman Problem: 計算量 O(2^N * N^2)
    // dp[S][v] = 現在 v の頂点にいて, 集合 S を既に訪れているときの, 残り全ての頂点を訪れるための最小コスト
    // ただし, 集合 S は右から i 番目に 1 が立っているとき, 頂点 i を訪れたことを表す
    vector<vector<ll>> dp(1 << N, vector<ll>(N, LINF));
    dp[(1 << N) - 1][0] = 0;  // 現在 0 の頂点(スタート)に戻っていて, S=11...11 だからすべての頂点を既に訪れているので, もうコストを支払う必要はない
    // for (int v = 0; v < N; ++v) dp[(1 << N) - 1][v] = 0;  // スタートに戻る必要がないときは, すべての頂点 v について初期化
    for (int S = (1 << N) - 2; S >= 0; --S) {
        for (int v = 0; v < N; ++v) {
            for (int u = 0; u < N; ++u) {
                if (!((S >> u) & 1)) {
                    dp[S][v] = min(dp[S][v], dp[S | (1 << u)][u] + dist[v][u]);
                }
            }
        }
    }

    cout << dp[0][0] << endl;  // 0 の頂点からスタートしてすべての頂点を訪れてスタートに戻るための最小コスト
}
