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

struct DSU {
    vector<int> parents;
    vector<int> sizes;

    DSU(int size) {
        parents.resize(size);
        sizes.resize(size);

        for (int i = 0; i < size; i++) {
            parents[i] = i;
        }
    }

    int find_(int u) {
        if (u == parents[u]) return u;
        return parents[u] = find_(parents[u]);
    }

    void union_(int u, int v) {
        u = find_(u);
        v = find_(v);

        if (u == v) return;

        if (sizes[u] < sizes[v]) swap(u, v);
        sizes[u] += sizes[v];
        parents[v] = u;
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
