#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
        deg[u]++;
        deg[v]++;
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] % 2) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }

    vector<int> path;
    vector<bool> vis(m);
    auto dfs = [&](auto &&dfs, int u) -> void {
        while (!adj[u].empty()) {
            auto [v, i] = adj[u].back(); adj[u].pop_back();
            if (vis[i]) continue;
            vis[i] = true;
            dfs(dfs, v);
        }
        path.push_back(u);
    };

    dfs(dfs, 0);

    if (path.size() != m + 1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (auto &p : path) cout << p+1 << " ";
        cout << endl;
    }
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
