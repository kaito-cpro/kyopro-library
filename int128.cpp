#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

istream& operator>>(istream& is, __int128& n) {
    string tmp;  is >> tmp;
    int sign = pow(-1, tmp[0] == '-');
    n = 0;
    for (int i = (1 - sign) / 2; i < (int)tmp.size(); ++i) {
        n = n * 10 + tmp[i] - '0';
    }
    n *= sign;
    return is;
}

ostream& operator<<(ostream& os, __int128 n) {
    if (n == 0) return os << "0";
    bool minus = n < 0;
    if (minus) n *= -1;
    string s = "";
    while (n) {
        s += (int)(n % 10) + '0';
        n /= 10;
    }
    reverse(s.begin(), s.end());
    if (minus) s = "-" + s;
    return os << s;
}

int main() {
    __int128 x;  cin >> x;
    cout << x << endl;
}