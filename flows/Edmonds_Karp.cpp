#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<vector<ll>> cap(n, vector<ll>(n));
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w; u--, v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        cap[u][v] += w;
    }

    vector<int> par;
    auto find = [&]() -> bool {
        par.assign(n, -1);

        queue<int> q;
        q.emplace(0);
        
        while (!q.empty()) {
            auto u = q.front(); q.pop();

            for (auto &v : adj[u]) {
                if (cap[u][v] > 0 and par[v] == -1) {
                    par[v] = u;
                    q.emplace(v);
                }
            }
        }

        return par[n-1] != -1;
    };

    ll ans = 0;
    while (find()) {
        int at = n-1;
        vector<int> path;
        while (at != 0) {
            path.push_back(at);
            at = par[at];
        }
        path.push_back(0);

        reverse(path.begin(), path.end());

        int k = path.size();
        ll mn = LLONG_MAX;
        for (int i = 1; i < k; i++) {
            int u = path[i-1], v = path[i];
            mn = min(mn, cap[u][v]);
        }

        for (int i = 1; i < k; i++) {
            int u = path[i-1], v = path[i];
            cap[u][v] -= mn;
            cap[v][u] += mn;
        }

        ans += mn;
    }

    cout << ans << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
