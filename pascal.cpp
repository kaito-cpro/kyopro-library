#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using ll = long long;

int main() {
    // MOD をとらない生の値(パスカルの三角形)
    // テーブル列挙 O(n^2)
    // 各クエリ O(1)
    const int MAX_N = 50;  // 50 ~ 60 ぐらいでないと ll に収まらない
    vector<vector<ll>> cmb(MAX_N + 1, vector<ll>(MAX_N + 1));
    for (int n = 0; n <= MAX_N; ++n) {
        for (int r = 0; r <= n; ++r) {
            if (r == 0 || n == r) cmb[n][r] = 1;
            else cmb[n][r] = cmb[n - 1][r - 1] + cmb[n - 1][r];
        }
    }
}