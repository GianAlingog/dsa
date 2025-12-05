#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
typedef long double ld;
const ll MOD = 998244353, INF = 1e18;
const ld EPS = 1e-12;
#define endl "\n"
#define sp <<" "<<
#define REP(i, a, b) for(ll i = a; i < b; i++)
#define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int>(a, b)(rng);
// shuffle(all(a), rng);

template <typename T>
struct FastSet {
    map<T, int> mp;

    FastSet() {}

    void insert(T x) {
        mp[x]++;
    }

    void erase(T x) {
        mp.erase(x);
    }

    void extract(T x) {
        mp[x]--;
        if (mp[x] == 0) mp.erase(x);
    }

    T top() {
        return mp.rbegin()->first;
    }

    T bot() {
        return mp.begin()->first;
    }

    // if i care enough i could implement some sort of sqrt / log for lb / ub
};

void solution() {
    // oops

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

// #pragma GCC optimize("O3")
// #pragma GCC target ("avx2")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse, sse2, sse3, ssse3, sse4, popcnt, abm, mmx, avx, tune=native")
// #pragma GCC optimize("unroll-loops")

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
