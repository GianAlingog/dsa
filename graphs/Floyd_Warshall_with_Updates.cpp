#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const ll INF = 1e18;
const int MAXN = 505;

ll iu[MAXN], iv[MAXN];
ll feli[MAXN];
ll dist[MAXN][MAXN];

// unblackbox FW as a DP alg
void solve() {
    ll n, m, k, t, q;
    cin >> n >> m;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dist[i][j] = (i == j ? 0 : INF);
        }
    }

    for (int i = 0; i < m; i++) {
        ll u, v, w; cin >> u >> v >> w; u--, v--;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = dist[u][v];
    }

    cin >> k >> t;
    for (int i = 0; i < k; i++) {
        ll x; cin >> x; x--;
        dist[x][n] = t;
        dist[n][x] = 0LL;
    }

    for (int h = 0; h <= n; h++) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][h] + dist[h][j]);
            }
        }
    }

    // for (int i = 0; i <= n; i++) {
    //     for (int j = 0; j <= n; j++) {
    //         cerr << (dist[i][j] == INF ? -1 : dist[i][j]) << " ";
    //     }   cerr << endl;
    // }

    cin >> q;
    while (q--) {
        int type; cin >> type; // something used to be here
        if (type == 1) {
            ll u, v, w; cin >> u >> v >> w; u--, v--;
            dist[v][u] = dist[u][v] = min(dist[u][v], w);
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= n; j++) {
                    dist[i][j] = min({dist[i][j], dist[i][u] + dist[u][v] + dist[v][j], dist[i][v] + dist[v][u] + dist[u][j]});
                }
            }
        } else if (type == 2) {
            ll x; cin >> x; x--;
            dist[x][n] = t, dist[n][x] = 0LL;
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= n; j++) {
                    dist[i][j] = min({dist[i][j], dist[i][x] + dist[x][n] + dist[n][j], dist[i][n] + dist[n][x] + dist[x][j]});
                }
            }
        } else {
            ll ans = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][j] == INF) continue;
                    ans += dist[i][j];
                }
            }

            cout << ans << endl;
        }
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
