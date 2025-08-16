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

const ll bad[4] = {2, 3, 5, 7};

ll count(ll x) {
    ll res = 0;
    for (int m = 1; m < (1 << 4); m++) {
        int amt = __builtin_popcount(m);
        ll L = 1;
        for (int i = 0; i < 4; i++) {
            if (m & (1 << i)) {
                L = (L * bad[i]) / __gcd(L, bad[i]);
            }
        }

        ll cnt = x / L;
        res += (amt % 2 == 1 ? +cnt : -cnt);
    }

    return res;
}

void solution() {
    ll l, r; cin >> l >> r;
    ll tot = r - l + 1;
    cout << (tot - (count(r) - count(l-1))) << endl;
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
// #define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)
// #define all(x) (x).begin(), (x).end()
// #define rall(x) (x).rbegin(), (x).rend()

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

// const int MAXN = 1e6;

// vector<int> trial(int x) {
//     set<int> temp;
//     for (int d = 2; d * d <= x; d++) {
//         while (x % d == 0) {
//             x /= d;
//             temp.insert(d);
//         }
//     }

//     if (x > 1) temp.insert(x);

//     vector<int> res(all(temp));
//     return res;
// }

// void solution() {
//     int n; cin >> n;
//     vector<int> a(n);
//     REP(i, 0, n) cin >> a[i];

//     vector<ll> ans(MAXN+1);
//     auto calc = [&](vector<int> &divs) -> ll {
//         ll res = 0;
//         int m = divs.size();
//         for (int i = 1; i < (1 << m); i++) {
//             int cnt = 0;
//             ll y = 1;
//             for (int j = 0; j < m; j++) {
//                 if (i & (1 << j)) {
//                     y *= divs[j];
//                     cnt++;
//                 }
//             }

//             if (cnt % 2) {
//                 res += ans[y];
//                 res %= MOD;
//             } else {
//                 res -= ans[y];
//                 res %= MOD;
//                 res += MOD;
//                 res %= MOD;
//             }
//         }

//         return res;
//     };

//     auto work = [&](vector<int> &divs, ll x) -> void {
//         int m = divs.size();
//         for (int i = 1; i < (1 << m); i++) {
//             int cnt = 0;
//             ll y = 1;
//             for (int j = 0; j < m; j++) {
//                 if (i & (1 << j)) {
//                     y *= divs[j];
//                     cnt++;
//                 }
//             }

//             ans[y] += x;
//             ans[y] %= MOD;
//         }
//     };


//     ll x;
//     REP(i, 0, n) {
//         vector<int> divs = trial(a[i]);
//         if (i == 0) {
//             x = 1;
//             work(divs, x);
//         } else {
//             x = calc(divs);
//             work(divs, x);
//         }
//     }

//     cout << x << endl;
//     return;
// }

// signed main() {
//     fast_io();

//     solution();

//     return 0;
// }
