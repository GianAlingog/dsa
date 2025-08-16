#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const ll MOD = 998244353;

ll binpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    const int MAXN = 2e5+5;
    vector<ll> fac(MAXN), inv(MAXN);

    fac[0] = fac[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fac[i] = (fac[i-1] * i) % MOD;
    }

    inv[MAXN-1] = binpow(fac[MAXN-1], MOD-2);
    for (int i = MAXN-2; i >= 0; i--) {
        inv[i] = (inv[i+1] * (i+1)) % MOD;
    }

    auto nck = [&](ll n, ll k) -> ll {
        return (((fac[n] * inv[k]) % MOD) * inv[n-k]) % MOD;
    };

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + a[i] * nck(2*n-i-1, n)) % MOD;
    }
    
    cout << ans << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
