#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll MOD = 998244353;
const ll INF = 1e18;
const ld EPS = 1e-12;

#define endl "\n"
#define sp <<" "<<
#define REP(i, a, b) for(ll i = a; i < b; i++)
#define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template <typename Key, typename Value>
using hash_map = unordered_map<Key, Value, custom_hash>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int>(a, b)(rng);
// shuffle(all(a), rng);

// const int MAXN = 1e4+21;

struct fwicku {
    int n;
    vector<ll> tree;

    fwicku(int _n) : n(_n) { tree.assign(n+1, 0); }

    void update(int x, ll v) {
        for (; x <= n; x += x & -x) tree[x] += v;
        return;
    }

    ll query(int x) {
        ll res = 0;
        for (; x > 0; x -= x & -x) res += tree[x];
        return res;
    }

    ll query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l-1);
    }
};

void solution() {
    int n; cin >> n;
    vector<int> a(n);
    REP(i, 0, n) cin >> a[i];

    fwicku st(n+5);
    vector<ll> left(n), right(n);
    ll sum = 0;

    REP(i, 0, n) {
        left[i] = st.query(a[i]+1, n);
        sum += left[i];
        st.update(a[i], +1);
    }

    fwicku ts(n+5);
    for (int i = n-1; i >= 0; i--) {
        right[i] = ts.query(a[i]+1, n);
        ts.update(a[i], +1);
    }

    ll ans = sum;
    REP(i, 0, n) {
        ll delta = right[i] - left[i];
        if (delta < 0) ans += delta;
    }

    cout << ans << endl;

    return;
}

signed main() {
    fast_io();

    // solution();

    int tests; cin >> tests;
    while (tests --> 0) {
        solution();
    }

    return 0;
}
