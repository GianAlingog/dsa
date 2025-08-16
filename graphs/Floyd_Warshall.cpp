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
#define dbg(x) cout << #x << " = " << x << endl
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((ll)(x).size())

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

// Told myself I wouldn't add algorithms I'll never forget, but I might as well
void solution() {
    ll n, m, q; cin >> n >> m >> q;
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    REP(i, 0, m) {
        ll u, v, w; cin >> u >> v >> w; u--, v--;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    REP(i, 0, n) dist[i][i] = 0;

    REP(k, 0, n) {
        REP(i, 0, n) {
            REP(j, 0, n) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    REP(i, 0, q) {
        ll a, b; cin >> a >> b; a--, b--;
        cout << (dist[a][b] == INF ? -1 : dist[a][b]) << endl;
    }
    return;
}

signed main() {
    fast_io();

    solution();

    return 0;
}

// Notes
// is it binsearchable? (min max smth)
// is it greedy?
// is it DP?
// if online round: search OEIS, similar topics
// are you using all the information available?

// put observations together
// check for edge cases
// try "dumb" solutions, you're fast enough to rewrite
// clean up the implementation
// keep it simple

// check for overflow
// check for small N
// check for array with same or monotonic a_i
