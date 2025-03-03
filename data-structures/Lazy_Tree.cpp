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

struct LazyTree {
    ll l, r;
    LazyTree *left, *right;
    ll value, lazy;

    void merge() {
        value = min(left->value, right->value);
    }

    LazyTree(ll l, ll r, vector<ll> &data) {
        this->l = l;
        this->r = r;
        this->left = nullptr;
        this->right = nullptr;
        this->lazy = 0;

        if (l == r) {
            value = data[l];
            return;
        }

        ll mid = (l + r) / 2;
        left = new LazyTree(l, mid, data);
        right = new LazyTree(mid + 1, r, data);

        merge();
    }

    void propagate() {
        if (lazy) {
            value += lazy;

            if (left) left->lazy += lazy;
            if (right) right->lazy += lazy;
        }

        lazy = 0;
    }

    void update(ll ul, ll ur, ll upd) {
        propagate();

        if (ul > r || ur < l) {
            return;
        }

        if (ul <= l && r <= ur) {
            lazy += upd;
            propagate();
            return;
        }

        left->update(ul, ur, upd);
        right->update(ul, ur, upd);

        merge();
    }

    ll query(ll ql, ll qr) {
        propagate();
        
        if (ql > r || qr < l) {
            return INF;
        }

        if (ql <= l && r <= qr) {
            return value;
        }

        return min(left->query(ql, qr), right->query(ql, qr));
    }
};

// RMQ & range updates with lazy propagation in a segment tree
// 
void solution() {
    return;
}

signed main() {
    fast_io();

    int tests; cin >> tests;
    while (tests--) {
        solution();
    }

    return 0;
}