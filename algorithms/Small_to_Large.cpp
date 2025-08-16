#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<set<int>> col(n);
    vector<int> ans(n);
    auto dfs = [&](auto &&dfs, int u, int p) -> void {
        for (auto &v : adj[u]) {
            if (v != p) {
                dfs(dfs, v, u);

                if (col[u].size() < col[v].size()) swap(col[u], col[v]);
                for (auto &x : col[v]) col[u].insert(x);
            }
        }

        col[u].insert(a[u]);
        ans[u] = col[u].size();
    };

    dfs(dfs, 0, -1);

    for (auto &x : ans) cout << x << " ";
    cout << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
