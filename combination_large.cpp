#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

template <class mint>
class Combination {
public:
    Combination() {}

    // 各クエリ O(logMOD) (extend_fact() を除いて)
    // クエリ数 Q とすると全体で最大 O(max_n logMOD + Q logMOD)
    mint C(int n, int r) {
        if (n < 0 || r < 0 || r > n) return 0;
        if (_n < n) extend_fact(n);
        if (_degree[n] > _degree[r] + _degree[n - r]) return 0;
        else return _residue[n] * (_residue[r] * _residue[n - r]).inv();
    }

    mint P(int n, int r) {
        if (n < 0 || r < 0 || r > n) return 0;
        if (_n < n) extend_fact(n);
        if (_degree[n] > _degree[n - r]) return 0;
        else return _residue[n] * _residue[n - r].inv();
    }

    mint H(int n, int r) {
        return C(n + r - 1, r);
    }

    mint fact(int n) {
        if (n < 0) return 0;
        if (_n < n) extend_fact(n);
        if (_degree[n] > 0) return 0;
        else return _residue[n];
    }

    mint fact_inv(int n) {
        if (n < 0) return 0;
        if (_n < n) extend_fact(n);
        if (_degree[n] > 0) return 0;  // 1 * inv(0) なので定義されない
        else return _residue[n].inv();
    }
    
private:
    vector<int> _degree;    // _degree[n] := n! の素因数 mod の個数
    vector<mint> _residue;  // _residue[n] := n! を素因数 mod で割り尽くした残りの部分の mod での値
    int mod = mint::mod();
    int _n = -1;
    
    // max_n までの前処理に O(max_n logMOD)
    void extend_fact(int max_n) {
        _degree.resize(max_n + 1);
        _residue.resize(max_n + 1);
        for (int i = 1; i <= max_n - _n; ++i) {
            int j = i + _n;
            if (j == 0) {
                _residue[j] = 1;
                continue;
            }
            int n = j;
            while (n % mod == 0) {
                ++_degree[j];
                n /= mod;
            }
            _residue[j] = n % mod;
        }
        for (int i = 1; i <= max_n -_n; ++i) {
            int j = i + _n;
            if (j == 0) continue;
            _degree[j] += _degree[j - 1];
            _residue[j] *= _residue[j - 1];
        }
        _n = max_n;
    }
};

using mint = modint;

istream& operator>>(istream& is, mint& e) {
    int tmp;  is >> tmp;
    e = tmp;
    return is;
}

int main() {
    // MOD が素数のときに正常に動作する
    // n >= MOD の呼び出しでも正常にで動作する(つまり、MOD が小さい素数の場合でも利用できる)
    mint::set_mod(3);  // MOD の値は, 一度 Combination のメソッドを呼び出した後には変更しないこと
    Combination<mint> cmb;
    cout << cmb.C(4, 2).val() << endl;
}