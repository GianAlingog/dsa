#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

struct fwick2d {
    int n, m;
    vector<vector<int>> tr;

    fwick2d(int n, int m) : n(n), m(m), tr(n+1, vector<int>(m+1)) {;;}

    void add(int r, int c, int val) {
        for (; r <= n; r += r & -r) {
            for (int x = c; x <= m; x += x & -x) {
                tr[r][x] += val;
            }
        }
    }

    int sum(int r, int c) {
        int res = 0;
        for (; r; r -= r & -r) {
            for (int x = c; x; x -= x & -x) {
                res += tr[r][x];
            }
        }
        return res;
    }

    int sum(int r1, int c1, int r2, int c2) {
        return sum(r2, c2) - sum(r1-1, c2) - sum(r2, c1-1) + sum(r1-1, c1-1);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    fwick2d fwick(n, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            if (c == '*') fwick.add(i, j, 1);
        }
    }

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int r, c; cin >> r >> c;
            if (fwick.sum(r, c, r, c) == 1) {
                fwick.add(r, c, -1);
            } else {
                fwick.add(r, c, 1);
            }
        } else {
            int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
            cout << fwick.sum(r1, c1, r2, c2) << endl;
        }
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
