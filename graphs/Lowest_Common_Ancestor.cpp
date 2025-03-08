#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<long long> vll;
typedef vector<vector<long long>> vvll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef set<int> si;
typedef set<long long> sll;

const ll MOD = 998244353;
const ld EPS = 1e-12;

#define endl "\n"
#define sp <<" "<<
#define forn(i, n) for(ll i = 0; i < n; i++)
#define rforn(i, n) for(ll i = n; i >= 0; i--)
#define dbg(x) cout << #x << " = " << x << endl
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF 1e18
#define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((ll)(x).size())

struct LCA {
    int timer, size, LOGN;
    vector<int> tin, tout;
    vector<vector<int>> up;

    LCA(int size, vector<vector<int>> &adj, int root = 0) {
        this->size = size, timer = 0, LOGN = ceil(__lg(size));
        tin.resize(size);
        tout.resize(size);
        up.assign(size, vector<int>(LOGN+1));

        ETT(root, root, adj);
    }

    void ETT(int node, int parent, vector<vector<int>> &adj) {
        tin[node] = timer++;

        up[node][0] = parent;
        for (int i = 1; i <= LOGN; i++) {
            up[node][i] = up[up[node][i-1]][i-1];
        }

        for (auto neighbor : adj[node]) {
            if (neighbor == parent) continue;
            ETT(neighbor, node, adj);
        }
        tout[node] = timer-1;
    }

    // faster
    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int getLCA(int u, int v) {
        if (isAncestor(u, v)) return u;
        if (isAncestor(v, u)) return v;

        for (int i = LOGN; i >= 0; i--) {
            if (!isAncestor(up[u][i], v))
                u = up[u][i];
        }

        return up[u][0];
    }
};

void solution() {
    
    return;
}

signed main() {
    fast_io();

    // solution();

    int tests; cin >> tests;
    while (tests--) {
        solution();
    }

    return 0;
}