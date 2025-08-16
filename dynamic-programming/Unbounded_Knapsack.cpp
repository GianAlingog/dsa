#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll MOD = 1e9 + 7;
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

// I really don't want to add this here, since it's memorable enough but whatevs
void solution() {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    REP(i, 0, n) cin >> a[i];

    vector<ll> dp(x+1);
    dp[0] = 1;

    REP(i, 0, n) {
        for (int w = a[i]; w <= x; w++) {
            dp[w] += dp[w - a[i]];
            dp[w] %= MOD;
        }
    }

    cout << dp[x] << endl;

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
