#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const int SHIFT = 1e6;
const int MAXN = 2e6;

struct segtree {
    int l, r;
    ll val;
    segtree *left, *right;

    void merge() {
        val = left->val + right->val;
    }

    segtree(int l, int r) : l(l), r(r), val(0) {
        if (l == r) {
            left = right = nullptr;
            return;
        }

        int m = (l+r) / 2;
        left = new segtree(l, m);
        right = new segtree(m+1, r);
    }

    void update(int ind, int upd) {
        if (l == r) {
            val += upd;
            return;
        }

        int m = (l+r) / 2;
        if (ind <= m) left->update(ind, upd);
        else right->update(ind, upd);
        merge();
    }

    ll query(int ql, int qr) {
        if (ql > r or qr < l) return 0;

        if (ql <= l and r <= qr) return val;

        return left->query(ql, qr) + right->query(ql, qr);
    }
};

void solve() {
    int n; cin >> n;

    vector<array<int, 4>> sweep;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        x1 += SHIFT, y1 += SHIFT, x2 += SHIFT, y2 += SHIFT;

        if (y1 == y2) {
            sweep.push_back({x1, 0, y1, -1});
            sweep.push_back({x2, 2, y2, -1});
        } else {
            sweep.push_back({x1, 1, y1, y2});
        }
    }

    sort(sweep.begin(), sweep.end());
    segtree st(0, MAXN);

    ll ans = 0;
    for (const auto &[x, t, y1, y2] : sweep) {
        if (t == 0) {
            st.update(y1, +1);
        } else if (t == 1) {
            ans += st.query(y1, y2);
        } else {
            st.update(y1, -1);
        }
    }

    cout << ans << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
