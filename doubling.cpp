#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll N, X, M;  cin >> N >> X >> M;
    const int MAX_D = 62;  // log(max(N))

    vector<vector<ll>> next(MAX_D + 1, vector<ll>(M, -1)), sum(MAX_D + 1, vector<ll>(M));
    // next[k][v] := 値 v の 2^k ステップ後の値
    // sum[k][v]  := 値 v から 2^k 項分の総和(つまり 1 ステップ後の値から 2^k - 1 ステップ後の値までの総和)
    for (ll v = 0; v < M; ++v) {
        next[0][v] = v * v % M;  // 写像の定義
        sum[0][v] = v;
    }
    for (int k = 0; k < MAX_D; ++k) {
        for (int v = 0; v < M; ++v) {
            next[k + 1][v] = next[k][next[k][v]];
            sum[k + 1][v] = sum[k][v] + sum[k][next[k][v]];
        }
    }

    ll ans = 0;
    ll now = X;
    for (int k = 0; k < MAX_D; ++k) {
        if (N & (1LL << k)) {
            ans += sum[k][now];
            now = next[k][now];
        }
    }
    cout << ans << endl;
}