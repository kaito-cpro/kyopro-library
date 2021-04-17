#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using ll = long long;

// x の素因数全体の vector を返す
vector<ll> prime_factors(ll x) {
    vector<ll> res;
    for (ll i = 2; i * i <= x; ++i) {
        int deg = 0;
        while (x % i == 0) {
            ++deg;
            x /= i;
        }
        if (deg) res.push_back(i);
    }
    if (x != 1) res.push_back(x);
    return res;
}

// x の素因数とその次数全体の map を返す
map<ll, int> prime_divisor(ll x) {
    map<ll, int> res;
    for (ll i = 2; i * i <= x; ++i) {
        int deg = 0;
        while (x % i == 0) {
            ++deg;
            x /= i;
        }
        if (deg) res[i] = deg;
    }
    if (x != 1) res[x] = 1;
    return res;
}

// x の約数全体の vector を返す
vector<ll> factors(ll x) {
    vector<ll> res;
    for (ll i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            res.push_back(i);
            if (x / i != i) res.push_back(x / i);
        }
    }
    return res;
}

int main() {
    while (true) {
        int x;  cin >> x;
        // DUMP(prime_factors(x));
        // DUMP(prime_divisor(x));
        // DUMP(factors(x));
    }
}