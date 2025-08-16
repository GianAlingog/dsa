#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

void solve() {
    int n, m, x, y; cin >> n >> m >> x >> y;
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    vector<bool> vis(n+1);
    vector<int> path;

    int at = x;
    vis[at] = true;
    path.push_back(at);

    auto check = [&](int st, int en) -> bool {
        vector<bool> vis2(n+1);
        queue<int> q;
        vis2[st] = true;
        q.emplace(st);

        while (!q.empty()) {
            auto u = q.front(); q.pop();
            if (u == en) return true;
            for (auto &v : adj[u]) {
                if (!vis[v] and !vis2[v]) {
                    vis2[v] = true;
                    q.emplace(v);
                }
            }
        }

        return false;
    };

    while (at != y) {
        for (auto &v : adj[at]) {
            if (!vis[v] and check(v, y)) {
                vis[v] = true;
                path.push_back(v);
                at = v;
                break;
            }
        }
    }

    for (auto &x : path) cout << x << " ";
    cout << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
