#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll MOD = 998244353;
const ll INF = 1e18;
const ld EPS = 1e-12;

#define endl "\n"
#define sp <<" "<<
#define F0R(i, b) for(ll i = 0; i < (b); i++)
#define FOR(i, a, b) for(ll i = (a); i < (b); i++)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((ll)(x).size())

const int MAXN = 1e6+5;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll __lcm(ll a, ll b) {
    return a / __gcd(a, b) * b;
}

vector<int> primeFactors(int n) {
    // change to set if needed
    vector<int> factors;

    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }

    if (n > 1)
        factors.push_back(n);

    // sort(factors.begin(), factors.end());

    return factors;
}

// Euler's Totient Function
// Point query
int phi(int n) {
    int ans = n;

    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0)
            n /= i;
        
        // Prove this
        ans -= ans / i;
    }

    if (n > 1)
        ans -= ans / n;

    return ans;
}

// Range query [1, n]
int phis[MAXN];
void ETF() {
    for (int i = 1; i < MAXN; i++)
        phis[i] = i;
    
    for (int i = 2; i < MAXN; i++) {
        // If i is prime
        if (phis[i] == i) {
            for (int j = i; j < MAXN; j+=i)
                phis[j] -= phis[j] / i;
        }
    }
}

int divs[MAXN];

// https://cses.fi/problemset/task/1713
void solution() {
    int n; cin >> n;
    
    ll ans = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ans += i * i == n ? 1 : 2;
        }
    }

    cout << ans << endl;
    // cout << divs[n] << endl;
    return;
}

signed main() {
    fast_io();

    // Alternative solution
    // for (int i = 1; i < MAXN; i++) {
    //     for (int j = i; j <= MAXN; j+=i) {
    //         divs[j]++;
    //     }
    // }

    int tests; cin >> tests;
    while (tests --> 0) {
        solution();
    }

    return 0;
}

// Extras
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
// unordered_map<long long, int, custom_hash> safe_map;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int>(a, b)(rng);
// shuffle(all(a), rng);
