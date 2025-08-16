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

void solution() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    REP(i, 0, m) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
    }

    vector<bool> vis(n), proc(n);
    vector<int> st;
    bool ok = true;
    auto dfs = [&](auto &&dfs, int u) -> void {
        vis[u] = true;
        proc[u] = true;
 
        for (auto &v : adj[u]) {
            if (vis[v] and proc[v]) {
                ok = false;
            }
 
            if (!vis[v]) {
                dfs(dfs, v);
            }
        }
 
        st.push_back(u);
        proc[u] = false;
    };

    dfs(dfs, 0);

    if (!ok or !vis[n-1]) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }


    vector<int> par(n, -1);
    vector<int> dist(n, -1);
    dist[0] = 1;
    reverse(all(st));
    for (auto &u : st) {
        for (auto &v : adj[u]) {
            if (dist[u] + 1 > dist[v]) {
                dist[v] = dist[u] + 1;
                par[v] = u;
            }
        }
    }

    cout << dist[n-1] << endl;
    int at = n-1;
    vector<int> path;
    while (at != -1) {
        path.push_back(at);
        at = par[at];
    }

    reverse(all(path));
    assert(path.size() == dist[n-1]);
    for (auto &x : path) {
        cout << x + 1 << " ";
    }   cout << endl;
    return;
}

signed main() {
    fast_io();

    solution();

    return 0;
}
