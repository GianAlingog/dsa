#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

inline int chb(char c) {
    if ('0' <= c and c <= '9') return c - '0';
    return c - 'a' + 10;
}

const int BIT = 164;
using tl = bitset<BIT>;

// soon i will learn the kactl imple of linearBinary
struct xor_basis {
    array<tl, BIT> b{};

    xor_basis() {;;}
    
    bool add(tl x) {
        for (int i = BIT-1; i >= 0; i--) {
            if (!x.test(i)) continue;
            if (b[i].any()) x ^= b[i];
            else {
                b[i] = x;
                return true;
            }
        }
        return false;
    }

    bool check(tl x) {
        for (int i = BIT-1; i >= 0; i--) {
            if (!x.test(i)) continue;
            if (!b[i].any()) return false;
            x ^= b[i];
        }
        return true;
    }
};

void solve() {
    int n, m, k; cin >> n >> m >> k;
    xor_basis xb;

    vector<tl> a(n);

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        // reverse(s.begin(), s.end());

        tl x;
        for (int j = 0; j < k; j++) {
            int res = chb(s[j]);
            for (int b = 0; b < 4; b++) {
                if (res & (1 << b)) x.set(j * 4 + b);
            }
        }

        a[i] = x;
    }

    vector<tl> b(m);
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        // reverse(s.begin(), s.end());

        tl x;
        for (int j = 0; j < k; j++) {
            int res = chb(s[j]);
            for (int b = 0; b < 4; b++) {
                if (res & (1 << b)) x.set(j * 4 + b);
            }
        }

        b[i] = x;
    }

    int zero = 1e9;
    vector<int> ans(m, 1e9);
    for (int i = 0; i < n; i++) {
        if (a[i].none()) zero = min(zero, i+1);

        bool res = xb.add(a[i]);
        if (!res) zero = min(zero, i+1);

        for (int j = 0; j < m; j++) {
            if (b[j].none()) ans[j] = min(ans[j], zero);
            else if (xb.check(b[j])) ans[j] = min(ans[j], i+1);
        }
    }

    for (auto &x : ans) cout << (x == 1e9 ? -1 : x) << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
