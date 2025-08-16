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
    int n; cin >> n;
    // sieve ahh

    vector<bool> pr(n+1, true);
    pr[0] = pr[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        for (int j = i * i; j <= n; j += i) {
            pr[j] = false;
        }
    }

    map<int, vector<int>> stuff;
    vector<int> primes;
    for (int i = 1; i <= n; i++) {
        if (pr[i]) {
            primes.push_back(i);
        }
    }

    reverse(all(primes));
    for (int i = 0; i < primes.size(); i++) {
        int x = primes[i];
        for (int j = 2 * x; j <= n; j += x) {
            if (!pr[j]) {
                pr[j] = true;
                stuff[x].push_back(j);
            }
        }
        stuff[x].push_back(x);
    }

    vector<int> ans(n+1);
    iota(all(ans), 0);

    for (auto &p : primes) {
        if (stuff[p].size() > 1) {
            int m = stuff[p].size();
            for (int i = 0; i < m; i++) {
                int j = (i-1+m) % m;
                ans[stuff[p][j]] = stuff[p][i];
                // cerr << p sp stuff[p][j] sp stuff[p][i] << endl;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }   cout << endl;

    // for (int i = 1; i <= n; i++) {
    //     cerr << __gcd(ans[i] ,i) << " ";
    // }   cerr << endl;
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
