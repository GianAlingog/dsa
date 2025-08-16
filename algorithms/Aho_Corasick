#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const int MOD = 998244353;

struct achoo {
    struct chapstick {
        int next[26], link, out;
        chapstick() : link(0), out(0) { fill_n(next, 26, -1); }
    };

    vector<chapstick> t;
    achoo() { t.emplace_back(); }

    void add(string &s, int id) {
        int at = 0;
        for (auto &ch : s) {
            int c = ch - 'a';
            if (t[at].next[c] == -1) {
                t[at].next[c] = t.size();
                t.emplace_back();
            }
            at = t[at].next[c];
        }
        t[at].out |= (1 << id);
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < 26; c++) {
            int at = t[0].next[c];
            if (at != -1) {
                t[at].link = 0;
                q.push(at);
            } else {
                t[0].next[c] = 0;
            }
        }

        while (!q.empty()) {
            int at = q.front(); q.pop();
            t[at].out |= t[t[at].link].out;
            
            for (int c = 0; c < 26; c++) {
                int to = t[at].next[c];
                if (to != -1) {
                    t[to].link = t[t[at].link].next[c];
                    q.push(to);
                } else {
                    t[at].next[c] = t[t[at].link].next[c];
                }
            }
        }
    }
};

// https://atcoder.jp/contests/abc419/tasks/abc419_f
void solve() {
    int n, l; cin >> n >> l;
    vector<string> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    achoo ac;
    for (int i = 0; i < n; i++) ac.add(s[i], i);
    ac.build();

    int states = ac.t.size();
    int m = 1 << n;
    vector<vector<int>> dp(l+1, vector<int>(states * m, 0));
    dp[0][0] = 1;

    for (int len = 0; len < l; len++) {
        for (int state = 0; state < states; state++) {
            int hsh = state * m;
            for (int mask = 0; mask < m; mask++) {
                if (dp[len][hsh + mask] == 0) continue;

                for (int c = 0; c < 26; c++) {
                    int nstate = ac.t[state].next[c];
                    int nmask = mask | ac.t[nstate].out;
                    dp[len+1][nstate * m + nmask] += dp[len][hsh + mask];
                    dp[len+1][nstate * m + nmask] %= MOD;
                }
            }
        }
    }

    ll ans = 0;
    for (int state = 0; state < states; state++) {
        ans += dp[l][state * m + m - 1];
        ans %= MOD;
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
