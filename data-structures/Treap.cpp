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

struct node {
    ll key, prior, val, mn, sz;
    node *l, *r, *p;
    node(ll k, ll v, ll prior) :
        key(k), prior(prior), l(nullptr), r(nullptr), p(nullptr),
        sz(1), val(v), mn(v)
    {;;}
};

ll getsz(node *t) { return t ? t->sz : 0; }
ll getval(node *t) { return t ? t->mn : INT_MAX; }

void pull(node *t) {
    if (!t) return;
    t->sz = 1 + getsz(t->l) + getsz(t->r);
    t->mn = min({t->val, getval(t->l), getval(t->r)});
}

inline bool cmp(ll key1, ll val1, ll key2, ll val2) {
    if (key1 == key2) return val1 < val2;
    return key1 < key2;
}

void split(node *t, ll k, ll v, node *&a, node *&b) {
    if (!t) { a = b = nullptr; return; }
    if (cmp(t->key, t->val, k, v)) {
        split(t->r, k, v, t->r, b);
        a = t; pull(a);
    } else {
        split(t->l, k, v, a, t->l);
        b = t; pull(b);
    }
}

node* merge(node *a, node *b) {
    if (!a or !b) return a ? a : b;
    if (a->prior < b->prior) {
        a->r = merge(a->r, b); pull(a); return a;
    } else {
        b->l = merge(a, b->l); pull(b); return b;
    }
}

node* insert(node *t, node *it) {
    if (!t) return it;
    if (it->prior < t->prior) {
        split(t, it->key, it->val, it->l, it->r);
        pull(it); return it;
    }
    if (cmp(it->key, it->val, t->key, t->val)) t->l = insert(t->l, it);
    else t->r = insert(t->r, it);
    pull(t); return t;
}

node* erase(node *t, ll k, ll v) {
    if (!t) return nullptr;
    if (t->key == k and t->val == v) {
        node *res = merge(t->l, t->r);
        delete t; return res;
    }
    if (cmp(k, v, t->key, t->val)) t->l = erase(t->l, k, v);
    else t->r = erase(t->r, k, v);
    pull(t); return t;
}

const int MX = 4e6;
const int N = MX + 21;
int at = 0;
node* root;
// map<pair<int, int>, int> fin;
set<pair<int, int>> st; // [L, R]
 
void update(pair<int, int> &seg, bool on) {
    int w = seg.second - seg.first;
    pair<int, int> temp{w, seg.first};

    if (on) {
        root = insert(root, new node(w, seg.first, rng()));
    } else {
        root = erase(root, w, seg.first);
    }
}
 
void reset() {
    st.clear();
    root = nullptr;
    pair<int, int> temp{0, MX};
    st.insert(temp);
    update(temp, true);
}
 
void solution() {
    reset();
 
    auto add = [&](int x) -> void {
        pair<int, int> temp{x, N};
        auto it = st.upper_bound(temp);
        it--;
 
        pair<int, int> loc = *it;
        if (loc.first == x) return;
        pair<int, int> fir{loc.first, x-1}, sec{x, loc.second};
 
        update(loc, false);
        update(fir, true), update(sec, true);

        st.erase(it);
        st.insert(fir), st.insert(sec);
    };
 
    auto rem = [&](int x) -> void {
        pair<int, int> temp{x, N};
        auto it = st.upper_bound(temp);
        it--;
        
        pair<int, int> sec = *it;
        assert(sec.first == x);
 
        pair<int, int> fir = *prev(it);
 
        pair<int, int> loc = {fir.first, sec.second};
 
        update(fir, false), update(sec, false);
        update(loc, true);
 
        st.erase(it);
        it = st.find(fir);
        st.erase(it);
        st.insert(loc);
    };
 
    auto que = [&](int k) -> int {
        node *a = nullptr, *b = nullptr;
        split(root, k, INT_MIN, a, b);
        int res = getval(b);
        root = merge(a, b);
        return res + 1;
    };
 
    int n; cin >> n;
    while (n--) {
        int x; cin >> x;
        add(x);
    }
 
    int q; cin >> q;
    while (q--) {
        char type; cin >> type;
        int x; cin >> x;
 
        if (type == '+') add(x);
        else if (type == '-') rem(x);
        else cout << que(x) << " ";
    }
    cout << endl;
 
    // cerr << endl;
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
