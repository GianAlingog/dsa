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

// Will transfer all other string stuff to this folder instead soon:/
// https://cp-algorithms.com/string/prefix-function.html#final-algorithm
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

void solution() {
    string s, t; cin >> s >> t;
    map<char, int> cnts, cntt, cntr;
    for (auto &c : s) cnts[c]++;
    for (auto &c : t) cntt[c]++;
    auto res = prefix_function(t);
    int best = res.back();
    string rem = t.substr(best);
    for (auto &c : rem) cntr[c]++;

    string ans = "";
    bool ok = true;
    for (auto &[c, x] : cntt) {
        if (cnts[c] < x) {
            ok = false;
            break;
        }
    }

    if (!ok) {
        cout << s << endl;
        return;
    }

    for (auto &[c, x] : cntt) cnts[c] -= x;
    ans += t;

    while (true) {
        ok = true;
        for (auto &[c, x] : cntr) {
            if (cnts[c] < x) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            break;
        }

        for (auto &[c, x] : cntr) cnts[c] -= x;
        ans += rem;
    }

    for (auto &[c, x] : cnts) ans += string(x, c);
    cout << ans << endl;

    return;
}

signed main() {
    fast_io();

    solution();

    return 0;
}
