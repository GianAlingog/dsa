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

struct jiayou {
    int mx, children[2];
    jiayou(int left = -1, int right = -1, int mx = -1) : mx(mx) {
        children[0] = left;
        children[1] = right;
    }
};

int query(vector<jiayou> &trie, int x, int k) {
    int res = -1;
    int at = 0;
    bool ok = true;
    // cerr << x << endl;
    for (int i = 30; i >= 0; i--) {
        // cerr << at sp trie[at].children[0] sp trie[at].children[1] << endl;
        int bit = (x & (1 << i)) != 0;
        int che = (k & (1 << i)) != 0;
        // cerr << bit sp che << endl;

        if (che == 0) {
            if (trie[at].children[bit ^ 1] != -1) {
                res = max(res, trie[trie[at].children[bit ^ 1]].mx);
                // cerr << "here" sp res << endl;
            }

            if (trie[at].children[bit] != -1) {
                at = trie[at].children[bit];
            } else {
                ok = false;
                break;
            }
        } else {
            if (trie[at].children[bit ^ 1] != -1) {
                at = trie[at].children[bit ^ 1];
            } else {
                ok = false;
                break;
            }
        }
    }
    // cerr << endl;

    // cerr << ok << endl;
    // cerr << x sp res << " ";
    if (ok) res = max(res, trie[at].mx);
    // cerr << res sp at << endl;
    return res;
}

void add(vector<jiayou> &trie, int x, int q) {
    int at = 0;
    trie[at].mx = q;

    for (int i = 30; i >= 0; i--) {
        int bit = (x & (1 << i)) != 0;
        if (trie[at].children[bit] == -1) {
            trie[at].children[bit] = trie.size();
            trie.push_back(jiayou());
        }
        at = trie[at].children[bit];
        trie[at].mx = q;
    }
}

void solution() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    vector<jiayou> trie = {jiayou()};
    REP(i, 0, n) cin >> a[i];

    int ans = INT_MAX;
    REP(i, 0, n) {
        add(trie, a[i], i);
        int res = query(trie, a[i], k);
        // cerr << trie[0].mx sp i sp query(trie, a[i], k) << endl;
        if (res != -1) ans = min(ans, int(i) - query(trie, a[i], k) + 1);
    }

    cout << (ans >= INT_MAX / 4 ? -1 : ans) << endl;
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
