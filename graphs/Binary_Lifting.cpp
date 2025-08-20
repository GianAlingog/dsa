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
    REP(i, 1, n) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const int l = log2(n) + 2;
    int t = 0;
    vector<int> tin(n), tout(n);
    vector<vector<int>> up(l, vector<int>(n));

    auto dfs = [&](auto &&dfs, int u, int p) -> void {
        tin[u] = t++;
        up[0][u] = p;
        for (auto &v : adj[u]) {
            if (v != p) {
                dfs(dfs, v, u);
            }
        }
        tout[u] = t;
    };

    dfs(dfs, 0, 0);

    REP(j, 1, l) {
        REP(i, 0, n) {
            up[j][i] = up[j-1][ up[j-1][i] ];
        }
    }

    auto anc = [&](int u, int v) -> bool {
        return tin[u] <= tin[v] and tout[v] <= tout[u];
    };

    auto lca = [&](int u, int v) -> int {
        if (anc(u, v)) return u;
        if (anc(v, u)) return v;

        for (int j = l-1; j >= 0; j--) {
            if (!anc(up[j][u], v)) {
                u = up[j][u];
            }
        }

        return up[0][u];
    };

    vector<int> diff(n), ans(n);
    REP(i, 0, m) {
        int u, v; cin >> u >> v; u--, v--;
        diff[u]++, diff[v]++;
        int w = lca(u, v);
        ans[w]++;
        diff[w] -= 2;
    }

    auto proc = [&](auto &&proc, int u) -> void {
        for (auto &v : adj[u]) {
            if (v != up[0][u]) {
                proc(proc, v);
                diff[u] += diff[v];
            }
        }

        ans[u] += diff[u];
    };

    proc(proc, 0);

    for (auto &x : ans) cout << x << " ";
    cout << endl;
    return;
}

signed main() {
    fast_io();

    solution();

    return 0;
}


// #include <bits/stdc++.h>
// using namespace std;

// typedef long long ll;
// typedef long double ld;

// const ll MOD = 998244353;
// const ll INF = 1e18;
// const ld EPS = 1e-12;

// #define endl "\n"
// #define sp <<" "<<
// #define F0R(i, b) for(ll i = 0; i < (b); i++)
// #define FOR(i, a, b) for(ll i = (a); i < (b); i++)
// #define mp make_pair
// #define pb push_back
// #define fi first
// #define se second
// #define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)
// #define all(x) (x).begin(), (x).end()
// #define rall(x) (x).rbegin(), (x).rend()
// #define sz(x) ((ll)(x).size())

// // https://cses.fi/problemset/task/1687
// void solution() {
//     int n, q; cin >> n >> q;
//     int LOGN = ceil(__lg(n))+1; // Remember this padding
//     vector<vector<int>> up(n, vector<int>(LOGN+1, -2));
//     FOR(i, 1, n) {
//         int x; cin >> x; x--;
//         up[i][0] = x;
//     }

//     FOR(l, 1, LOGN) {
//         FOR(i, 0, n) {
//             if (up[i][l-1] == -2) continue;
//             up[i][l] = up[ up[i][l-1] ][l-1];
//         }
//     }

//     F0R(i, q) {
//         int x, k; cin >> x >> k; x--;
//         F0R(l, LOGN) {
//             if (x == -2) break;
//             if (k & 1 << l)
//                 x = up[x][l];
//         }

//         cout << x+1 << endl;
//     }

//     return;
// }

// signed main() {
//     fast_io();

//     solution();

//     // int tests; cin >> tests;
//     // while (tests --> 0) {
//     //     solution();
//     // }

//     return 0;
// }

// // Extras
// // struct custom_hash {
// //     static uint64_t splitmix64(uint64_t x) {
// //         // http://xorshift.di.unimi.it/splitmix64.c
// //         x += 0x9e3779b97f4a7c15;
// //         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
// //         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
// //         return x ^ (x >> 31);
// //     }

// //     size_t operator()(uint64_t x) const {
// //         static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
// //         return splitmix64(x + FIXED_RANDOM);
// //     }
// // };
// // unordered_map<long long, int, custom_hash> safe_map;

// // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// // uniform_int_distribution<int>(a, b)(rng);
// // shuffle(all(a), rng);
