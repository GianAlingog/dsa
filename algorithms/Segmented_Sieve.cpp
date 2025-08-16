#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

// https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html#segmented-sieve
unordered_set<ll> sieve(ll mx) {
    unordered_set<ll> res;
    for (int i = 2; i < mx; i++) {
        res.insert(i);
    }

    for (int i = 2; i * i < mx; i++) {
        for (int j = i * i; j < mx; j += i) {
            res.extract(j);
        }
    }

    return res;
}

vector<bool> segsieve(ll l, ll r, unordered_set<ll> &base) {
    vector<bool> res(r - l + 1, true);

    for (auto &pr : base) {
        for (ll j = max(pr * pr, (l + pr - 1) / pr * pr); j <= r; j += pr) {
            res[j - l] = false;
        }
    }

    if (l == 1) {
        res[0] = false;
    }

    return res;
}

void solve() {
    ll l, r; cin >> l >> r;

    unordered_set<ll> base = sieve(sqrtl(r) + 1);
    vector<bool> range = segsieve(max(2LL, l+1), r, base);

    vector<ll> news;
    for (ll i = max(2LL, l+1); i <= r; i++) {
        if (range[i - max(2LL, l+1)]) {
            news.push_back(i);
        }
    }

    for (auto &pr : base) {
        ll curr = pr * pr;
        while (curr <= r) {
            if (curr > l) news.push_back(curr);
            if (curr > r / pr) break;
            curr *= pr;
        }
    }

    sort(news.begin(), news.end());
    news.erase(unique(news.begin(), news.end()), news.end());

    cout << news.size() + 1 << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
