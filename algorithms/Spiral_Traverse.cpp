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
    vector<string> grid(n);
    REP(i, 0, n) cin >> grid[i];

    vector<vector<int>> stuff(1005);
    vector<vector<bool>> vis(n, vector<bool>(m));
    int mnr = 0, mxr = n-1, mnc = 0, mxc = m-1;
    int r = 0, c = m-1;
    int curr = 0;
    while (mnr <= r and r <= mxr and mnc <= c and c <= mxc) {
        if (vis[r][c]) break;
        vis[r][c] = true;
        stuff[curr].push_back(grid[r][c] - '0');

        while (c-1 >= mnc and !vis[r][c-1]) {
            c--;
            vis[r][c] = true;
            stuff[curr].push_back(grid[r][c] - '0');
        }

        while (r+1 <= mxr and !vis[r+1][c]) {
            r++;
            vis[r][c] = true;
            stuff[curr].push_back(grid[r][c] - '0');
        }

        while (c+1 <= mxc and !vis[r][c+1]) {
            c++;
            vis[r][c] = true;
            stuff[curr].push_back(grid[r][c] - '0');
        }

        while (r-1 >= mnc and !vis[r-1][c]) {
            r--;
            vis[r][c] = true;
            stuff[curr].push_back(grid[r][c] - '0');
        }
        
        c--;
        mnr++, mxr--;
        mxc++, mnc--;
        curr++;
    }

    // cerr << "here" sp curr << endl;

    int ans = 0;
    REP(i, 0, curr) {
        int k = stuff[i].size();
        if (k < 4) continue;
        reverse(all(stuff[i]));
        REP(j, 0, k) {
            int a = j, b = (j+1) % k, c = (j+2) % k, d = (j+3) % k;
            // cerr << stuff[i][a] << stuff[i][b] << stuff[i][c] << stuff[i][d] << endl;
            if (
                stuff[i][a] == 1 and
                stuff[i][b] == 5 and
                stuff[i][c] == 4 and
                stuff[i][d] == 3
            ) ans++;
        }
    }
    // cerr << endl;

    cout << ans << endl;
    return;
}

signed main() {
    fast_io();

    // solution();

    int tests; cin >> tests;
    while (tests --> 0) {
        solution();
    }

    return 0;
}
