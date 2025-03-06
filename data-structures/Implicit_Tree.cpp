#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<long long> vll;
typedef vector<vector<long long>> vvll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef set<int> si;
typedef set<long long> sll;

const ll MOD = 998244353;
const ld EPS = 1e-12;

#define endl "\n"
#define sp <<" "<<
#define forn(i, n) for(ll i = 0; i < n; i++)
#define rforn(i, n) for(ll i = n; i >= 0; i--)
#define dbg(x) cout << #x << " = " << x << endl
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF 1e18
#define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((ll)(x).size())

struct segtree {
    int l, r;
    ll val, lazy;
    segtree *left, *right;

    void merge() {
        val = left->val + right->val;
    }

    segtree(int l, int r) {
        this->l = l;
        this->r = r;
        this->val = this->lazy = 0;
        this->left = this->right = nullptr;
    }

    void extend() {
        if (!left && l != r) {
            int mid = (l + r) / 2;
            left = new segtree(l, mid);
            right = new segtree(mid+1, r);
        }
    }

    void propagate() {
        if (lazy) {
            val += lazy * (r - l + 1);

            if (left) left->lazy += lazy;
            if (right) right->lazy += lazy;
        }

        lazy = 0;
    }

    void update(int ul, int ur, int upd) {
        extend();
        propagate();

        if (ul > r || ur < l) return;

        if (ul <= l && r <= ur) {
            lazy += upd;
            propagate();
            return;
        }

        left->update(ul, ur, upd);
        right->update(ul, ur, upd);

        merge();
    }

    ll query(int ql, int qr) {
        extend();
        propagate();

        if (ql > r || qr < l) return 0;

        if (ql <= l && r <= qr) return val;

        return left->query(ql, qr) + right->query(ql, qr);
    }
};

void solution() {
    
    return;
}

signed main() {
    fast_io();

    // solution();

    int tests; cin >> tests;
    while (tests--) {
        solution();
    }

    return 0;
}
