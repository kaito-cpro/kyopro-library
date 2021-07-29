#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

template <class S,
          S (*op)(S, S),
          S (*e)()>
class segtree2D {
public:
    segtree2D(int h, int w) : H(h), W(w) { _init(h, w); }
    
    void set(int i, int j, S val) {
        seg[i + SEG_LEN].set(j, val);
        _update(i, j);
    }
    
    S get(int i, int j) {
        return seg[i + SEG_LEN].get(j);
    }
    
    S prod(int lx, int rx, int ly, int ry) {
        S sum_l = e(), sum_r = e();
        lx += SEG_LEN;
        rx += SEG_LEN;
        while (lx < rx) {
            if (lx & 1) sum_l = op(sum_l, seg[lx++].prod(ly, ry));
            if (rx & 1) sum_r = op(seg[--rx].prod(ly, ry), sum_r);
            lx >>= 1;
            rx >>= 1;
        }
        return op(sum_l, sum_r);
    }
    
    S all_prod() {
        return prod(0, H, 0, W);
    }
        
private:
    vector<segtree<S, op, e>> seg;
    int H, W, SEG_LEN;
    
    void _init(int H, int W) {
        SEG_LEN = 1 << (int)ceil(log2(H));
        seg.resize(2 * SEG_LEN, segtree<S, op, e>(W));
    }
    
    void _update(int i, int j) {
        i = (i + SEG_LEN) >> 1;
        while (i) {
            seg[i].set(j, op(seg[2 * i].get(j), seg[2 * i + 1].get(j)));
            i >>= 1;
        }
    }
};

using S = int;
S op(S l, S r) { return l + r; }
S e() { return 0; }

int main() {
    int H = 3, W = 2;
    segtree2D<S, op, e> seg(H, W);
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            seg.set(i, j, 10 * i + j);
        }
    }
    cout << seg.prod(0, 3, 1, 2) << endl;  // 長方形 [0, 3) * [1, 2) 内の要素の op の値
}