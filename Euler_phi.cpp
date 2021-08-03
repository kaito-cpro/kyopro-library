#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using ll = long long;

// 計算量 O(sqrt(N))
ll phi(ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n != 1) res = res / n * (n - 1);
    return res;
}

// 計算量 O(N loglogN)
vector<int> make_phi_table(int MAX_N) {
    vector<int> phi(MAX_N + 1);
    for (int i = 0; i <= MAX_N; ++i) phi[i] = i;
    for (int i = 2; i <= MAX_N; ++i) {
        if (phi[i] == i) {
            for (int j = 1; i * j <= MAX_N; ++j) {
                phi[i * j] = phi[i * j] / i * (i - 1);
            }
        }
    }
    return phi;
}