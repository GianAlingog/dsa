#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

void solve() {
    // ok k is small
    // we can probably perform the dp on one of the strings
    // then cap the search space by k

    // transform first i characters in s to first j characters in t
    
    int k; cin >> k;
    string s, t; cin >> s >> t;

    int n = s.size(), m = t.size();
    bool ok = false;
    int mx = k+1;

    if (abs(n-m) <= k) {
        vector<int> prev(m+1), curr(m+1);
        for (int i = 0; i <= m; i++) {
            prev[i] = (i <= k ? i : mx);
        }

        for (int i = 1; i <= n; i++) {
            int lo = max(1, i - k);
            int hi = min(m, i + k);

            curr[0] = (i <= k ? i : mx);

            // perform on the search space
            for (int j = lo; j <= hi; j++) {
                // note to self: don't black box this next time:/
                // https://www.geeksforgeeks.org/dsa/edit-distance-dp-5/
                int cost = (s[i-1] == t[j-1] ? 0 : 1);
                int ins = curr[j-1] + 1;
                int del = prev[j] + 1;
                int sub = prev[j-1] + cost;
                curr[j] = min({ins, del, sub});
            }

            if (lo > 1) curr[lo-1] = mx;
            if (hi < m) curr[hi+1] = mx;

            swap(prev, curr);
        }

        ok = prev[m] <= k;
    }

    cout << (ok ? "Yes" : "No") << endl;
}

// post:
// you can actually just run the std recursive alg
// then prune when abs(i-j) > k :o
// it makes sense in hindsight

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
