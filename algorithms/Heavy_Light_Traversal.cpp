#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const ll INF = 2e18;
const int MAXN = 5e5;
const int LOGN = 21;

void solve() {
    // we need to do a binary tree like structure then based on the length
    // we can traverse left or right!

    // oops we need to speed up w binjump prolly

    int n; cin >> n;
    vector<int> l(n+2), r(n+2);
    vector<ll> q(n+2), len(n+2);
    vector<ll> val(n+5, 0);
    vector<vector<int>> up(n+5, vector<int>(LOGN));

    up[0][0] = 0, up[1][0] = 1;
    len[0] = len[1] = 1;
    for (int i = 2; i < n+2; i++) {
        cin >> l[i] >> r[i] >> q[i]; q[i]--;
        len[i] = min(len[l[i]] + len[r[i]], INF);

        if (len[l[i]] < len[r[i]]) {
            up[i][0] = r[i];
            val[i] = val[r[i]] + len[l[i]];
        } else {
            up[i][0] = l[i];
            val[i] = val[l[i]];
        }
    }

    for (int j = 1; j < LOGN; j++) {
        for (int i = 0; i < n+2; i++) {
            up[i][j] = up[ up[i][j-1] ][j-1];
        }
    }

    for (int i = 2; i < n+2; i++) {
        ll k = q[i];
        int at = i;
        while (at >= 2) {
            for (int j = LOGN-1; j >= 0; j--) {
                int to = up[at][j];
                if (0 <= k - val[at] + val[to] and k - val[at] + val[to] < len[to]) {
                    k -= val[at] - val[to];
                    at = to;
                }
            }

            if (at < 2) {}
            else if (len[l[at]] <= k) {
                k -= len[l[at]];
                at = r[at];
            } else {
                at = l[at];
            }
        }

        cout << at << endl;
    }

}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
