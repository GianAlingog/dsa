#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const ll INF = 1e18;

vector<vector<pair<int, ll>>> adj;
int N, M, SZ;
vector<ll> a, lb, ub;

void build(int base, int type) {
    if (adj.size() < base + SZ) adj.resize(base + SZ);

    for (int i = 1; i < (SZ / 2); i++) {
        int u = base + i;
        int l = base + (i << 1);
        int r = base + (i << 1|1);
        if (type == 0) {
            adj[l].emplace_back(u, ub[u-base] - ub[l-base]);
            adj[r].emplace_back(u, 0);
        } else if (type == 1) {
            adj[l].emplace_back(u, 0);
            adj[r].emplace_back(u, lb[r-base] - lb[u-base]);
        } else if (type == 2) {
            adj[u].emplace_back(l, 0);
            adj[u].emplace_back(r, lb[r-base] - lb[u-base]);
        } else if (type == 3) {
            adj[u].emplace_back(l, ub[u-base] - ub[l-base]);
            adj[u].emplace_back(r, 0);
        }
    }
}

void addon(int base, int sz, int l, int r, int to, ll w, bool on) {
    l += sz, r += sz;
    while (l <= r) {
        if (l & 1) {
            if (on) adj[base + l].emplace_back(to, w - ub[l]);
            else adj[base + l].emplace_back(to, w + lb[l]);
            l++;
        }

        if (!(r & 1)) {
            if (on) adj[base + r].emplace_back(to, w - ub[r]);
            else adj[base + r].emplace_back(to, w + lb[r]);
            r--;
        }

        l >>= 1, r >>= 1;
    }
}

void addoff(int base, int sz, int l, int r, int fr, ll w, bool on) {
    l += sz, r += sz;
    while (l <= r) {
        if (l & 1) {
            if (on) adj[fr].emplace_back(base + l, w + lb[l]);
            else adj[fr].emplace_back(base + l, w - ub[l]);
            l++;
        }

        if (!(r & 1)) {
            if (on) adj[fr].emplace_back(base + r, w + lb[r]);
            else adj[fr].emplace_back(base + r, w - ub[r]);
            r--;
        }

        l >>= 1, r >>= 1;
    }
}

void solve() {
    cin >> N >> M;

    SZ = 1;
    while (SZ < N) SZ <<= 1;
    SZ <<= 1;

    a.resize(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    using train = tuple<ll, ll, ll, ll, ll>;
    vector<train> b(M);
    for (int i = 0; i < M; i++) {
        ll l, r, L, R, c; cin >> l >> r >> L >> R >> c;
        b[i] = make_tuple(--l, --r, --L, --R, c);
    }

    int STAT = 0, TRAIN = STAT + N;
    int BOARDE = TRAIN + M, BOARDW, LEAVEE, LEAVEW, TOT;

    BOARDW = BOARDE + SZ;
    LEAVEE = BOARDW + SZ;
    LEAVEW = LEAVEE + SZ;
    TOT = LEAVEW + SZ;

    lb.resize(SZ), ub.resize(SZ);
    adj.resize(TOT);

    for (int i = 0; i < SZ/2; i++) {
        lb[SZ/2 + i] = ub[SZ/2 + i] = a[min(i, N-1)];
    }

    for (int i = SZ/2-1; i >= 1; i--) {
        lb[i] = min(lb[i<<1], lb[i<<1|1]);
        ub[i] = max(ub[i<<1], ub[i<<1|1]);
    }

    for (int i = 0; i < N; i++) {
        adj[i].emplace_back(BOARDE + SZ/2 + i, 0);
        adj[i].emplace_back(BOARDW + SZ/2 + i, 0);
        adj[LEAVEE + SZ/2 + i].emplace_back(i, 0);
        adj[LEAVEW + SZ/2 + i].emplace_back(i, 0);
    }

    build(BOARDE, 0);
    build(BOARDW, 1);
    build(LEAVEE, 2);
    build(LEAVEW, 3);

    for (int i = 0; i < M; i++) {
        int j = TRAIN + i;
        const auto &[l, r, L, R, c] = b[i];

        if (r < L) {
            addon(BOARDE, SZ/2, l, r, j, c + a[L], r < L);
            addoff(LEAVEE, SZ/2, L, R, j, - a[L], r < L);
        } else {
            addon(BOARDW, SZ/2, l, r, j, c - a[R], r < L);
            addoff(LEAVEW, SZ/2, L, R, j, + a[R], r < L);
        }
    }

    vector<ll> dist(TOT, INF);
    using state = pair<ll, int>;
    priority_queue<state, vector<state>, greater<state>> pq;

    dist[0] = 0;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto &[v, w] : adj[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }

    for (int i = 1; i < N; i++) {
        cout << (dist[i] == INF ? -1 : dist[i]) << " ";
    }   cout << endl;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
