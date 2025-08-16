#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

struct fwicku {
    int n;
    vector<int> tree;

    fwicku(int n) : n(n), tree(n+1, 0) {;;}

    void add(int i, int v) {
        for (i++; i <= n; i += i & -i) tree[i] += v;
    }

    int sum(int i) {
        int res = 0;
        for (i++; i; i -= i & -i) res += tree[i];
        return res;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r; l--, r--;
        queries[i] = {l, r};
    }

    vector<int> o(q);
    iota(o.begin(), o.end(), 0);
    sort(o.begin(), o.end(), [&](int i, int j) {
        return queries[i].second < queries[j].second;
    });

    int at = 0;
    fwicku tr(n);
    vector<int> ans(q);
    map<int, int> last;
    for (int t = 0; t < n; t++) {
        // first update the element right now
        if (last.count(a[t]))
        tr.add(last[a[t]], -1);
        tr.add((last[a[t]] = t), +1);

        // proceed with queries
        if (at >= q or queries[o[at]].second > t) continue;
        int to = at;
        while (to < q and queries[o[to]].second == t) to++;
        for (int i = at; i < to; i++) {
            auto &[l, r] = queries[o[i]];
            ans[o[i]] = tr.sum(l, r);
        }
        at = to;
    }

    for (auto &x : ans) cout << x << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
