#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const ll MOD = 1e6;
const ll MAXK = 1e6+1;
const ll MAXN = 1e3+1;

ll nck[MAXN][MAXN];
vector<ll> divs[MAXK];

void gen() {
    nck[0][0] = 1;

    for (int n = 1; n < MAXN; n++) {
        nck[n][0] = nck[n][n] = 1;
        for (int k = 1; k < n; k++) {
            nck[n][k] = (nck[n-1][k-1] + nck[n-1][k]) % MOD;
        }
    }

    for (int i = 1; i * i < MAXK; i++) {
        for (int j = i; j < MAXK; j += i) {
            divs[j].push_back(i);
        }
    }
}

void solve() {
    ll n, m, k; cin >> n >> m >> k;

    if (k > n * m) {
        cout << 0 << endl;
        return;
    }

    ll ans = 0;
    for (auto &x : divs[k]) {
        ll d1 = x, d2 = k / x;
        if (d1 <= n and d2 <= m) {
            ans += (nck[n-1][d1-1] * nck[m-1][d2-1]) % MOD;
            ans %= MOD;
        }
    }

    cout << ans << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    gen();

    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
