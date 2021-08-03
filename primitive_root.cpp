#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using ll = long long;

ll pow_mod(ll x, ll n, ll mod) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

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

unsigned long _xor128(){
    static unsigned long x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    unsigned long t = x ^ (x << 11);
    x = y;  y = z;  z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

// [l, r) の範囲で疑似乱数を生成
ll rand(ll l, ll r) {
    return _xor128() % (r - l) + l;
}

// mod p の原始根を 1 つ返す(p が素数ならば存在が保証される)
// 計算量 O(sqrt(p))
ll find_primitive_root(ll p) {
    vector<ll> primes = prime_factors(p - 1);
    // 原始根を [2, p) で乱択
    while (true) {
        ll r = rand(2, p);
        if (pow_mod(r, p - 1, p) != 1) continue;
        bool ok = true;
        for (ll d : primes) {
            if (pow_mod(r, (p - 1) / d, p) == 1) ok = false;
        }
        if (ok) return r;
    }
}

// 離散対数問題 a^x = b (mod p) の解 x を求める
// 計算量 O(sqrt(p))
ll log_mod(ll a, ll b, ll p) {
    // sqrt(p) の計算
    ll lb = -1, ub = p;
    while (ub - lb > 1) {
        ll mid = (lb + ub) / 2;
        if (mid * mid >= p) ub = mid;
        else lb = mid;
    }
    ll sqrt_p = ub;
    
    unordered_map<ll, ll> mp;
    ll now = a % p;
    for (ll i = 1; i < sqrt_p; ++i) {
        mp[now] = i;
        now = now * a % p;
    }
    
    now = b % p;
    ll A = pow_mod(a, -sqrt_p, p);
    for (ll i = 0; i <= sqrt_p; ++i) {
        if (mp[now] > 0) return i * sqrt_p + mp[now];
        now = now * A % p;
    }
    
    return -1;  // 解が存在しない
}

int main() {
    ll p = 998244353;
    ll r = find_primitive_root(p);  // mod p の原始根の 1 つ
    ll x = log_mod(r, 2, p);  // r^x = 2 (mod p) の解,
                              // すなわち, 2 の離散対数 log_{r}(2),
                              // すなわち, 2 と対応する加法群 Z/(p - 1)Z の元,
                              // すなわち, 2 の位数は (p - 1) / gcd(x, p - 1)
}