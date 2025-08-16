#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const ll BAD = 0;
const ll INF = 1e18;

struct segtree {
    struct data {
        ll size;
        ll p, s;
        ll pref, suff, best;

        ll sum, padd, pset;

        data(ll size = -1, ll pref = -BAD, ll suff = -BAD, ll best = -BAD, ll p = -INF, ll s = -INF, ll sum = -BAD)
            : size(size), pref(pref), suff(suff), best(best), p(p), s(s), sum(sum), padd(-INF), pset(-INF) {;;}
    };

    static const data INVALID;

    ll l, r;
    data d;
    segtree *left, *right;

    inline data combine(const data &a, const data &b) {
        if (a.p == -INF or a.s == -INF) return b;
        if (b.p == -INF or b.s == -INF) return a;
        
        return data({
            a.size + b.size,
            (a.size == a.pref and a.p == b.p ? a.pref + b.pref : a.pref),
            (b.size == b.pref and a.s == b.s ? a.suff + b.suff : b.suff),
            max({a.best, b.best, (a.s == b.p ? a.suff + b.pref : 0)}),
            a.p,
            b.s,
            a.sum + b.sum
        });
    }

    inline void merge() {
        d = combine(left->d, right->d);
    }

    segtree(int l, int r, vector<ll> &a) : l(l), r(r) {
        if (l == r) {
            d = data(1, 1, 1, 1, a[l], a[l], a[l]);
            left = right = nullptr;
            return;
        }

        int m = (l+r) / 2;
        left = new segtree(l, m, a);
        right = new segtree(m+1, r, a);
        merge();
    }

    void propagate() {
        if (d.pset != -INF) {
            d.p = d.pset;
            d.s = d.pset;
            d.pref = d.suff = d.best = d.size;
            d.sum = d.size * d.pset;

            if (left) left->d.pset = d.pset, left->d.padd = -INF;
            if (right) right->d.pset = d.pset, right->d.padd = -INF;

            d.pset = -INF;
        }

        if (d.padd != -INF) {
            d.p += d.padd;
            d.s += d.padd;
            d.sum += d.size * d.padd;

            if (left) {
                if (left->d.padd == -INF) left->d.padd = 0;
                left->d.padd += d.padd;
            }
            if (right) {
                if (right->d.padd == -INF) right->d.padd = 0;
                right->d.padd += d.padd;
            } 

            d.padd = -INF;
        }
    }

    void add(int ql, int qr, ll upd) {
        propagate();

        if (ql > r or qr < l) return;

        if (ql <= l and r <= qr) {
            if (d.padd == -INF) d.padd = 0;
            d.padd += upd;
            propagate();
            return;
        }

        left->add(ql, qr, upd);
        right->add(ql, qr, upd);
        merge();
    }

    void set(int ql, int qr, ll upd) {
        propagate();

        if (ql > r or qr < l) return;

        if (ql <= l and r <= qr) {
            d.pset = upd;
            propagate();
            return;
        }

        left->set(ql, qr, upd);
        right->set(ql, qr, upd);
        merge();
    }

    data query(int ql, int qr) {
        propagate();

        if (ql > r or qr < l) return INVALID;

        if (ql <= l and r <= qr) return d;

        return combine(left->query(ql, qr), right->query(ql, qr));
    }
};

const segtree::data segtree::INVALID = segtree::data();

void solve() {
    int n, q; cin >> n >> q;
    vector<ll> a(n), d1;
    for (int i = 0; i < n; i++) cin >> a[i];
    
    auto derive = [&](vector<ll> &a) -> vector<ll> {
        vector<ll> res(n);
        for (int i = 1; i < n; i++) {
            res[i] = a[i] - a[i-1];
        }
        return res;
    };

    d1 = derive(a);
    d1[0] = -INF;

    segtree st(0, n-1, d1);

    ll type, l, r, s, c;
    ll shift = a[0];

    while (q--) {
        cin >> type;

        if (type == 1) {
            cin >> l >> r >> s >> c; l--, r--;
            ll sz = (r - l + 1);

            if (l == 0) shift += s;
            else st.add(l, l, s);
            st.add(l+1, r, c);
            if (r+1 < n) st.add(r+1, r+1, -(s + (sz - 1) * c));
        } else

        if (type == 2) {
            cin >> l >> r >> s >> c; l--, r--;
            ll sz = (r - l + 1);
            ll left = st.query(1, l-1).sum + shift;
            ll right = left + (r+1 < n ? st.query(l, r+1).sum : 0);

            if (l == 0) shift = s;
            else st.set(l, l, s - left);
            st.set(l+1, r, c);
            if (r+1 < n) st.set(r+1, r+1, right - (s + (sz - 1) * c));
        } else 

        if (type == 3) {
            cin >> l >> r; l--, r--;
            ll sz = (r - l + 1);
            cout << min(sz, max(1LL, st.query(l+1, r).best) + 1) << endl;
        }
    }
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
