#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define fast_io() ios_base::sync_with_stdio(false); cin.tie(NULL)

struct Sparse {
    vector<vector<int>> table;
    int size, LOGN;

    Sparse(vector<int> &data, int n) {
        size = n;

        LOGN = 0;
        while ((1 << LOGN) <= size) LOGN++;

        table = vector<vector<int>>(size, vector<int>(LOGN, 1e9));

        build(data);
    }

    // handle merge here
    int merge(int left, int right) {
        return min(left, right);
    }

    void build(vector<int> &data) {
        for (int i = 0; i < size; i++) {
            table[i][0] = data[i];
        }

        for (int j = 1; j <= LOGN; j++) {
            for (int i = 0; i + (1 << j) - 1 < size; i++) {
                table[i][j] = merge(table[i][j-1], table[i+(1 << (j-1))][j-1]);
            }
        }
    }

    int query(int l, int r) {
        int sz = r - l + 1;
        int j = 0;
        while ((1 << (j + 1)) <= sz) j++;

        return merge(table[l][j], table[r-(1<<(j))+1][j]);
    }
};

// RMQ with sparse table
// https://cses.fi/problemset/task/1647
void solution() {
    int n, q; cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    Sparse sparse = Sparse(a, n);

    while (q--) {
        int l, r; cin >> l >> r;
        l--; r--;

        cout << sparse.query(l, r) << endl;
    }
    return;
}

signed main() {
    fast_io();

    solution();

    return 0;
}