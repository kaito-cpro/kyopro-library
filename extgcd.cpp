#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// gcd(a, b) を返す
// ax + by = gcd(a, b) の特殊解 x, y を参照で操作して求める
ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    else {
        ll d = extgcd(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }
}

int main() {
    ll a, b;  cin >> a >> b;
    ll x, y;
    ll d = extgcd(a, b, x, y);
    cout << d << " " << x << " " << y << endl;
}
