#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

template <class mint>
class Combination {
public:
    Combination() {}

    // 各クエリ O(1) (extend_fact() を除いて)
    // クエリ数 Q とすると全体で最大 O(max_n + Q logMOD)
    mint C(int n, int r) {
        if (n < 0 || r < 0 || r > n) return 0;
        if (_n < n) extend_fact(n);
        return _fact[n] * _fact_inv[r] * _fact_inv[n - r];
    }

    mint P(int n, int r) {
        if (n < 0 || r < 0 || r > n) return 0;
        if (_n < n) extend_fact(n);
        return _fact[n] * _fact_inv[n - r];
    }

    mint H(int n, int r) {
        return C(n + r - 1, r);
    }

    mint fact(int n) {
        if (n < 0) return 0;
        if (_n < n) extend_fact(n);
        return _fact[n];
    }

    mint fact_inv(int n) {
        if (n < 0) return 0;
        if (_n < n) extend_fact(n);
        return _fact_inv[n];
    }
    
private:
    vector<mint> _fact, _fact_inv;
    int _n = -1;
    
    // max_n までの前処理に O(max_n + logMOD)
    void extend_fact(int max_n) {
        _fact.resize(max_n + 1);
        for (int i = 1; i <= max_n - _n; ++i) {
            int j = i + _n;
            if (j == 0) _fact[j] = 1;
            else _fact[j] = _fact[j - 1] * j;
        }
        _fact_inv.resize(max_n + 1);
        for (int i = max_n - _n; i >= 1; --i) {
            int j = i + _n;
            if (j == max_n) _fact_inv[j] = _fact[max_n].inv();
            else _fact_inv[j] = _fact_inv[j + 1] * (j + 1);
        }
        _n = max_n;
    }
};

using mint = modint1000000007;

istream& operator>>(istream& is, mint& e) {
    int tmp;  is >> tmp;
    e = tmp;
    return is;
}

int main() {
    Combination<mint> cmb;
    cout << cmb.C(4, 2).val() << endl;
}
