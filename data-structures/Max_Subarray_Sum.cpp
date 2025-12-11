#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 998244353;
const ll INF = 0;
const ld EPS = 1e-12;
 
#define endl "\n"
#define sp <<" "<<
#define REP(i, a, b) for(ll i = a; i < b; i++)
#define dbg(x) cout << #x << " = " << x << endl
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((ll)(x).size())
 
using arr = array<ll, 3>;

struct segtree {
    struct data {
        arr sum, pref, suff, best;
 
        data() {
            arr bad = {-INF, -INF, -INF};
            sum = pref = suff = best = bad;
        }

        data(ll val, ll ind) {
            arr ts = {val, ind, ind};
            sum = pref = suff = best = ts;
        }
    };
 
    int l, r;
    data d;
    segtree *left, *right;
 
    inline arr merge(const arr &a, const arr &b) {
        arr r;
        r[0] = a[0] + b[0];
        r[1] = min(a[1], b[1]);
        r[2] = max(a[2], b[2]);

        return r;
    }
 
    inline data combine(const data &a, const data &b) {
        data r;

        r.sum = merge(a.sum, b.sum);

        r.pref = max(a.pref, merge(a.sum, b.pref));

        r.suff = max(b.suff, merge(a.suff, b.sum));

        r.best = max({a.best, b.best, merge(a.suff, b.pref)});

        return r;
    }
 
    segtree(int l, int r, vector<ll> &a) : l(l), r(r) {
        d = data();
        left = right = nullptr;
 
        if (l == r) {
            d = data(a[l], l);
            return;
        }
 
        int m = (l+r)/2;
        left = new segtree(l, m, a);
        right = new segtree(m+1, r, a);
 
        d = combine(left->d, right->d);
    }
 
    void update(int ind, int upd) {
        if (l == r) {
            d = data(upd, l);
            return;
        }
 
        int m = (l+r)/2;
        if (ind <= m) left->update(ind, upd);
        else right->update(ind, upd);
 
        d = combine(left->d, right->d);
    }
 
    data query(int ql, int qr) {
        if (ql > r || qr < l) return data();
 
        if (ql <= l && r <= qr) return d;
 
        return combine(left->query(ql, qr), right->query(ql, qr));
    }
};
 
void solution() {
    ll n; cin >> n;
    vector<ll> a(n), c(n), p(n);
    REP(i, 0, n) cin >> a[i];
    REP(i, 0, n) cin >> c[i];
    REP(i, 0, n) cin >> p[i], p[i]--;

    ll mx = *max_element(all(a));
    ll best = INF;
    REP(i, 0, n) {
        if (a[i] == mx) {
            best = min(best, c[i]);
        }
    }


    vector<ll> base = c;
    vector<ll> st;
    for (ll i = n-1; i >= 0; i--) {
        while (!st.empty() and (a[st.back()] < a[i])) {
            st.pop_back();
        }
        if (!st.empty() and c[st.back()] > c[i]) {
            st.push_back(i);
        } else if (st.empty()) st.push_back(i);

        if (!st.empty()) base[i] = min(base[i], c[st.back()]);
    }

    st.clear();
    for (ll i = 0; i < n; i++) {
        while (!st.empty() and (a[st.back()] < a[i])) {
            st.pop_back();
        }
        if (!st.empty() and c[st.back()] > c[i]) {
            st.push_back(i);
        } else if (st.empty()) st.push_back(i);

        if (!st.empty()) base[i] = min(base[i], c[st.back()]);
    }

    vector<ll> left(n, -1), right(n, n);
    st.clear();
    REP(i, 0, n) {
        while (!st.empty() and (a[st.back()] <= a[i])) st.pop_back();
        if (!st.empty()) left[i] = st.back();
        st.push_back(i);
    }

    st.clear();
    for (ll i = n-1; i >= 0; i--) {
        while (!st.empty() and (a[st.back()] <= a[i])) st.pop_back();
        if (!st.empty()) right[i] = st.back();
        st.push_back(i);
    }

    segtree trr(0, n-1, base);
    cout << max(0LL, accumulate(all(base), 0LL) - best) << " ";

    REP(i, 0, n) {
        ll L = left[p[i]] + 1, R = right[p[i]] - 1;

        auto res = trr.query(L, R);
        while (res.best[0] > 0) {
            ll l = res.best[1], r = res.best[2];
            for (ll i = l; i <= r; i++) {
                trr.update(i, 0);
            }

            res = trr.query(L, R);
        }

        res = trr.query(0, n-1);
        cout << max(0LL, res.sum[0] - best) << " ";
    }

    cout << endl;

    return;
}
 
signed main() {
    fast_io();
 
    solution();
 
    // int tests; cin >> tests;
    // while (tests --> 0) {
    //     solution();
    // }
 
    return 0;
}
 
// Notes
// is it greedy?
// is it DP?
// if online round: search OEIS, similar topics
 
// put observations together
// check for edge cases
// try "dumb" solutions, you're fast enough to rewrite
// clean up the implementation
// keep it simple
 
// check for overflow
// check for small N
// check for array with same or monotonic a_i
 
// Extras
// struct custom_hash {
//     static uint64_t splitmix64(uint64_t x) {
//         // http://xorshift.di.unimi.it/splitmix64.c
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }
 
//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
//         return splitmix64(x + FIXED_RANDOM);
//     }
// };
// unordered_map<long long, int, custom_hash> safe_map;
 
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int>(a, b)(rng);
// shuffle(all(a), rng);
