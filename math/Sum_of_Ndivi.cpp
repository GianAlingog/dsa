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
    ll n; cin >> n;

    // sum of (a, b) such that a > b
    // a = N - b (1 to N)
    // subtract multiples of b : N / b (1 to N)
    // fk ts im moving to paper

    // n(n+1) / 2 - sig(n / i)
    ll ans = ((n % MOD) * ((n + 1) % MOD)) % MOD;
    ans = (ans * binpow(2, MOD-2)) % MOD;

    // bcs floor we can group by same rem, should be sublinear
    ll curr = 0, i = 1;
    while (i <= n) {
        ll rem = n / i;
        ll mx = n / rem;
        ll amt = (mx - i + 1) % MOD;
        curr = (curr + (amt * (rem % MOD)) % MOD) % MOD;
        i = mx + 1;
    }

    // cerr << ans sp curr << endl;
    ans = (((ans - curr) % MOD) + MOD) % MOD;
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
