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

// https://cp-algorithms.com/graph/bridge-searching.html
ll binpow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solution() {
    ll n, m, v; cin >> n >> m >> v;
    vector<ll> a(n);
    REP(i, 0, n) cin >> a[i];

    vector<pair<int, int>> edges(m);
    vector<vector<pair<int, int>>> adj(n);
    REP(i, 0, m) {
        int u, v; cin >> u >> v; u--, v--;
        edges[i] = {u, v};
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }

    vector<int> tin(n), low(n);
    vector<bool> vis(n), bridge(m);
    int timer = 0;
    
    auto dfs = [&](this auto &&dfs, int u, int p) -> void {
        vis[u] = true;
        tin[u] = low[u] = timer++;

        for (auto &[v, id] : adj[u]) {
            if (id == p) continue;
            if (vis[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u]) {
                    bridge[id] = true;
                }
            }
        }
    };

    dfs(0, -1);

    vector<vector<int>> comp(n);
    REP(i, 0, m) {
        if (!bridge[i]) {
            auto &[u, v] = edges[i];
            comp[u].emplace_back(v);
            comp[v].emplace_back(u);
        }
    }

    vector<bool> proc(n), dead(n);
    vector<int> par(n), color(n), sz(n, 1);
    vector<ll> val(n, -2);
    iota(all(par), 0);

    auto find = [&](this auto &&find, int u) -> int {
        if (u == par[u]) return u;
        return par[u] = find(par[u]);
    };

    auto unite = [&](int u, int v) -> void {
        u = find(u), v = find(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];

        dead[u] = dead[u] or dead[v];
        if (val[u] == -2) val[u] = val[v];
        else if (val[v] != -2 and val[u] != val[v]) val[u] = -3;
    };

    REP(i, 0, n) {
        if (proc[i]) continue;
        if (comp[i].empty()) {
            proc[i] = true;
            continue;
        }

        vector<int> st;
        queue<int> q;
        q.emplace(i);
        color[i] = 1;
        proc[i] = true;
        st.push_back(i);

        bool ok = true;
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            for (auto &v : comp[u]) {
                if (!proc[v]) {
                    proc[v] = true;
                    color[v] = -color[u];
                    st.push_back(v);
                    q.emplace(v);
                } else {
                    if (color[u] == color[v]) {
                        ok = false;
                    }
                }
            }
        }

        if (!ok) {
            for (auto &v : st) {
                dead[find(v)] = true;
            }
        } else {
            REP(i, 1, st.size()) {
                unite(st[0], st[i]);
            }
        }
    }

    bool ok = true;
    REP(i, 0, n) {
        int u = find(i);

        if (dead[u]) {
            if (a[i] > 0) {
                ok = false;
                break;
            }
        } else {
            if (a[i] >= 0) {
                if (val[u] == -2) val[u] = a[i];
                else if (val[u] != a[i]) {
                    ok = false;
                    break;
                }
            }
        }

        if (val[u] == -3) {
            ok = false;
            break;
        }
    }

    if (!ok) {
        cout << 0 << endl;
        return;
    }

    vector<bool> vis2(n);
    ll free = 0;
    REP(i, 0, n) {
        int u = find(i);

        if (vis2[u]) continue;
        vis2[u] = true;

        if (!dead[u]) {
            if (val[u] == -2) free++;
        }
    }

    cout << binpow(v, free) << endl;
    
    // any cycle should then have xor value of 0
    // maybe we can decompose the graph
    // if we remove bridges then we have a graph of cycles
    
    // we only care about 2-length edges rlly
    // if graph is non-bipartite then all 0
    // else all same value
    // or impossible
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
