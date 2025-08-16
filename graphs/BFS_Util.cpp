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

const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};
const char dir[4] = {'L', 'R', 'U', 'D'};

void solution() {
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    REP(i, 0, n) cin >> grid[i];

    queue<pair<pair<int, int>, bool>> q;
    vector<vector<bool>> vis(n, vector<bool>(m)), vis2 = vis;

    auto check = [&](int rr, int cc) -> bool {
        return (0 <= rr and rr < n and 0 <= cc and cc < m) and (grid[rr][cc] != '#');
    };

    auto win = [&](int rr, int cc) -> bool {
        return (rr == 0 or rr == n-1 or cc == 0 or cc == m-1);
    };

    bool ok = false;
    pair<int, int> start = {-1, -1}, end = {-1, -1};
    REP(i, 0, n) REP(j, 0, m) {
        if (grid[i][j] == 'M') q.push({{i, j}, true}), vis[i][j] = true;
    }

    REP(i, 0, n) REP(j, 0, m) {
        if (grid[i][j] == 'A') q.push({{i, j}, false}), start = {i, j}, ok = win(i, j);
    }

    if (ok) {
        cout << "YES" << endl;
        cout << 0 << endl;
        return;
    }

    while (!q.empty()) {
        auto [at, b] = q.front(); q.pop();
        auto [r, c] = at;

        REP(i, 0, 4) {
            int nr = r + dr[i], nc = c + dc[i];

            if (!check(nr, nc)) continue;
            if (vis[nr][nc]) continue;

            if (!b and win(nr, nc)) {
                ok = true;
                end = {nr, nc};
                break;
            }

            vis[nr][nc] = true;
            q.push({{nr, nc}, b});
        }
    }

    if (!ok) {
        cout << "NO" << endl;
        return;
    }

    vector<vector<pair<int, int>>> par(n, vector<pair<int, int>>(m, {-1, -1}));
    queue<pair<int, int>> p;
    p.push(end);
    vis2[end.fi][end.se] = true;

    while (!p.empty()) {
        auto [r, c] = p.front(); p.pop();

        REP(i, 0, 4) {
            int nr = r + dr[i], nc = c + dc[i];

            if (!check(nr, nc)) continue;
            if (vis2[nr][nc]) continue;

            par[nr][nc] = {r, c};
            vis2[nr][nc] = true;
            p.push({nr, nc});

            if (grid[nr][nc] == 'A') break;
        }
    }

    string ans;
    vector<pair<int, int>> path;
    while (start != end) {
        pair<int, int> next = par[start.fi][start.se];

        REP(i, 0, 4) {
            if (next.fi - start.fi == dr[i] and next.se - start.se == dc[i]) {
                ans.push_back(dir[i]);
                break;
            }
        }

        start = next;
    }

    cout << "YES" << endl;
    cout << ans.size() << endl;
    cout << ans << endl;

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
