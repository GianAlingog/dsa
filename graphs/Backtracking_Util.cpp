#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const int dr[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dc[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

void solve() {
    int rr, cc; cin >> cc >> rr; rr--, cc--;

    bool found = false;
    using state = tuple<int, int, int>;
    vector<vector<int>> grid(8, vector<int>(8));

    auto in = [&](int r, int c) -> bool {
        return (0 <= r and r < 8 and 0 <= c and c < 8);
    };

    auto calc = [&](int r, int c) -> int {
        int res = 0;
        for (int i = 0; i < 8; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (in(nr, nc) and grid[nr][nc] == 0) res++;
        }
        return res;
    };

    auto dfs = [&](auto &&dfs, int r, int c, int at) -> void {
        grid[r][c] = at;
        if (at == 64) {
            found = true;
            return;
        }

        vector<state> cands;
        for (int i = 0; i < 8; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (in(nr, nc) and grid[nr][nc] == 0) {
                cands.emplace_back(calc(nr, nc), nr, nc);
            }
        }

        sort(cands.begin(), cands.end());
        for (auto &[d, nr, nc] : cands) {
            dfs(dfs, nr, nc, at + 1);
            if (found) return;
        }

        grid[r][c] = 0;
    };

    dfs(dfs, rr, cc, 1);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] < 10) cout << 0;
            cout << grid[i][j] << " ";
        }
        cout << endl;
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
