#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

template <class T>
bool chmin(T& l, const T& r) {
    if (l > r) {
        l = r;
        return true;
    }
    return false;
}

const int INF = numeric_limits<int>::max() / 2;
using ll = long long;

// エラトステネスの篩
// 計算量 O(N loglogN)
// 素数判定は if sieve[i] == i で可能
vector<int> make_sieve(int MAX_N) {
    vector<int> sieve(MAX_N + 1, INF);  // sieve[i] := i の素因数のうち最小のもの
    sieve[0] = sieve[1] = -1;
    for (int i = 0; i <= MAX_N; ++i) {
        if (sieve[i] == INF) {
            for (int j = 1; i * j < MAX_N + 1; ++j) chmin(sieve[i * j], i);
        }        
    }
    return sieve;
}

// 高速素因数分解
// 計算量 エラトステネスに O(N loglogN), 素因数走査に O(logN)
map<int, int> fast_prime_divisor(int x, vector<int>& sieve) {
    map<int, int> res;
    while (x > 1) {
        ++res[sieve[x]];
        x /= sieve[x];
    }
    return res;
}

int main() {
    int N;  cin >> N;
    const int MAX_N = 100005;
    // DUMP(make_sieve(MAX_N));
    // DUMP(fast_prime_divisor(N, make_sieve(MAX_N)));        
}