#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

template <typename T>
vector<T> make_vector(int n) {
// vector<T> make_vector(int n, T x) {
    return vector<T>(n);
    // return vector<T>(n, x);
}
template <typename T, typename... Tail>
auto make_vector(int n, Tail... tail) {
    return vector<decltype(make_vector<T>(tail...))>(n, make_vector<T>(tail...));
}

int main() {
    int H, W;  cin >> H >> W;
    auto grid = make_vector<string>(H);
    for (int i = 0; i < H; ++i) cin >> grid[i];

    // 4 方向累積和
    // u[i][j] := (i, j) から上に突き当たるまで進んで, '.' の個数
    //    (ただし, (i, j) の '.' の個数も含む)
    //    ((i, j) が '#' の場合は u[i][j] = 0)
    auto u = make_vector<int>(H, W);
    auto d = make_vector<int>(H, W);
    auto l = make_vector<int>(H, W);
    auto r = make_vector<int>(H, W);
    for (int j = 0; j < W; ++j) {
        for (int i = 0; i < H; ++i) {
            if (i == 0) u[i][j] = (grid[i][j] == '.');
            else u[i][j] = (grid[i][j] == '.' ? u[i - 1][j] + 1 : 0);
        }
        for (int i = H - 1; i >= 0; --i) {
            if (i == H - 1) d[i][j] = (grid[i][j] == '.');
            else d[i][j] = (grid[i][j] == '.' ? d[i + 1][j] + 1 : 0);
        }
    }
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (j == 0) l[i][j] = (grid[i][j] == '.');
            else l[i][j] = (grid[i][j] == '.' ? l[i][j - 1] + 1 : 0);
        }
        for (int j = W - 1; j >= 0; --j) {
            if (j == W - 1) r[i][j] = (grid[i][j] == '.');
            else r[i][j] = (grid[i][j] == '.' ? r[i][j + 1] + 1 : 0);
        }
    }
}
