#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using ll = long long;

int main() {    
    map<ll, int> first_index;  // first_index[v] := 値 v が出現する最小の index (1-indexed)
    vector<ll> vals;  // 数列を順次構成していく
    
    ll now = 2;  // 初期値
    first_index[now] = 1;
    vals.push_back(now);
    
    int i = 1;
    while (true) {
        ++i;
        now = now * now % 10;  // 値の更新
        vals.push_back(now);
        if (first_index[now]) break;
        first_index[now] = i;
    }
    
    int cycle_start = first_index[now] - 1, cycle_end = i - 1;
    int cycle = cycle_end - cycle_start;
    // たとえば 2 -> 3 -> 4 -> 5 -> 3 というサイクルの場合
    //    cycle_start = 1, cycle_end = 4, cycle = 3,
    //    vals = [2, 3, 4, 5, 3].
    // vals[cycle_start] と vals[cycle_end] は同じ値
    
    // K 番目(0-indexed)の値
    ll K = 3141592;
    ll ans;
    if (K < cycle_start) ans = vals[K];
    else ans = vals[cycle_start + (K - cycle_start) % cycle];
}