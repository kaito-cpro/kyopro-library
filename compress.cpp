#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using ll = long long;

// 1 個の vector を座圧
template <class T>
void compress(vector<T>& v) {
    vector<T> vals;
    for (int i = 0; i < v.size(); ++i) vals.push_back(v[i]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < v.size(); ++i) {
        v[i] = lower_bound(vals.begin(), vals.end(), v[i]) - vals.begin();
    }
}

// 2 個の vector を座圧(区間 [s, t] の始点 s と終点 t の配列 S, T の座圧を想定)
template <class T>
void compress(vector<T>& v1, vector<T>& v2) {
    vector<T> vals;
    for (int i = 0; i < v1.size(); ++i) vals.push_back(v1[i]);
    for (int i = 0; i < v2.size(); ++i) vals.push_back(v2[i]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < v1.size(); ++i) {
        v1[i] = lower_bound(vals.begin(), vals.end(), v1[i]) - vals.begin();
    }
    for (int i = 0; i < v2.size(); ++i) {
        v2[i] = lower_bound(vals.begin(), vals.end(), v2[i]) - vals.begin();
    }
}

int main() {
    vector<int> s{4, 1, 10}, t{2, 4, 7};
    compress(s);
    compress(s, t);
}