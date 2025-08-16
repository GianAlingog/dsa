#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const ll MOD = 1e9+7;
const int MAXN = 2e6+5;

ll fact[MAXN], inv[MAXN];

ll binpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void gen() {
    fact[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }

    inv[MAXN-1] = binpow(fact[MAXN-1], MOD-2);
    for (ll i = MAXN-2; i >= 0; i--) {
        inv[i] = inv[i+1] * (i+1) % MOD;
    }
}

void solve() {
    ll n, k; cin >> n >> k;
    auto choose = [&](ll n, ll k) -> ll {
        if (k > n) return 0;
        return fact[n] * inv[k] % MOD * inv[n-k] % MOD;
    };
    cout << choose(n+k-1, n-1) << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    gen();

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
