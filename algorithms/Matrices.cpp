#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll MOD = 1e9+7;
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

vector<vector<int>> mat = {
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // 1
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, // 2
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // 3
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 4
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // 5
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // 6
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // 7
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 8
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // 9
};

inline vector<vector<int>> mul(vector<vector<int>> &a, vector<vector<int>> &b) {
    vector<vector<int>> c(10, vector<int>(10));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= MOD;
            }
        }
    }

    return c;
}

const int MAXN = 2e5+25;
int dp[10][MAXN];

void gen() {
    vector<vector<int>> base = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 9
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // 1
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, // 2
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // 3
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 4
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // 5
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // 6
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // 7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 8
    };

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < 10; j++) {
            ll cnt = 0;
            for (int k = 0; k < 10; k++) {
                cnt += base[j][k];
                cnt %= MOD;
            }
            dp[j][i] = cnt;
        }

        base = mul(base, mat);
    }
}

void solution() {
    int n, m; cin >> n >> m;
    vector<int> dig;
    while (n) {
        dig.push_back(n % 10);
        n /= 10;
    }

    int ans = 0;
    for (auto &d : dig) {
        ans += dp[d][m];
        ans %= MOD;
    }

    cout << ans << endl;

    return;
}

signed main() {
    fast_io();

    gen();

    int tests; cin >> tests;
    while (tests --> 0) {
        solution();
    }

    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;

// typedef long long ll;
// typedef long double ld;

// const ll MOD = 998244353;
// const ll INF = 1e18;
// const ld EPS = 1e-12;

// #define endl "\n"
// #define sp <<" "<<
// #define REP(i, a, b) for(ll i = a; i < b; i++)
// #define dbg(x) cout << #x << " = " << x << endl
// #define mp make_pair
// #define pb push_back
// #define fi first
// #define se second
// #define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)
// #define all(x) (x).begin(), (x).end()
// #define rall(x) (x).rbegin(), (x).rend()
// #define sz(x) ((ll)(x).size())

// struct custom_hash {
//     static uint64_t splitmix64(uint64_t x) {
//         // http://xorshift.di.unimi.it/splitmix64.c
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }

//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
//         return splitmix64(x + FIXED_RANDOM);
//     }
// };

// template <typename Key, typename Value>
// using hash_map = unordered_map<Key, Value, custom_hash>;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// // uniform_int_distribution<int>(a, b)(rng);
// // shuffle(all(a), rng);

// vector<vector<ll>> binMul(vector<vector<ll>> &a, ll b, int n) {
//     vector<vector<ll>> c(n, vector<ll>(n, 0));
//     REP(i, 0, n) {
//         c[i][i] = 1;
//     }

//     // be careful as matrix multiplication is not associative
//     while (b) {
//         if (b & 1)
//             c = mul(c, a, n);
//         a = mul(a, a, n);
//         b >>= 1;
//     }

//     return c;

// }

// vector<vector<ll>> mul(vector<vector<ll>> &a, vector<vector<ll>> &b, int n) {
//     vector<vector<ll>> c(n, vector<ll>(n, 0));
//     REP(i, 0, n) {
//         REP(j, 0, n) {
//             REP(k, 0, n) {
//                 c[i][j] += a[i][k] * b[k][j];
//                 c[i][j] %= MOD;
//             }
//         }
//     }

//     return c;
// }

// void solution() {
    
//     return;
// }

// signed main() {
//     fast_io();

//     // solution();

//     int tests; cin >> tests;
//     while (tests --> 0) {
//         solution();
//     }

//     return 0;
// }

// // Notes
// // is it binsearchable?
// // is it greedy?
// // is it DP?
// // if online round: search OEIS, similar topics

// // put observations together
// // check for edge cases
// // try "dumb" solutions, you're fast enough to rewrite
// // clean up the implementation
// // keep it simple

// // check for overflow
// // check for small N
// // check for array with same or monotonic a_i
