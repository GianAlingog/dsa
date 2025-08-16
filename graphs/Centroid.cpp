#include "race.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

vector<bool> good;
vector<ll> sz;
vector<vector<pair<ll, ll>>> adj;

ll n, k;

void subtree(ll u, ll p = -1) {
    sz[u] = 1;
    for (auto &[v, ww] : adj[u]) {
        if (v != p and good[v]) {
            subtree(v, u);
            sz[u] += sz[v];
        }
    }
}

ll centroid(ll targ, ll u, ll p = -1) {
    for (auto &[v, ww] : adj[u]) {
        if (v != p and good[v] and 2 * sz[v] > targ) {
            return centroid(targ, v, u);
        }
    }

    return u;
}

void process(vector<pair<ll, ll>> &w, ll dist, ll cost, ll u, ll p = -1) {
    if (dist > k) return;

    w.push_back({dist, cost});

    for (auto &[v, ww] : adj[u]) {
        if (v != p and good[v]) {
            process(w, dist + ww, cost + 1, v, u);
        }
    }
}

ll dnc(ll st) {
    subtree(st);
    ll siz = sz[st];

    ll cen = centroid(siz, st);

    good[cen] = false;

    unordered_map<ll, vector<pair<ll, ll>>> mp;
    for (auto &[v, ww] : adj[cen]) {
        if (good[v]) {
            process(mp[v], ww, 1, v, cen);
        }
    }

    ll res = LLONG_MAX;
    unordered_map<ll, ll> rec;
    rec[0] = 0;
    
    for (auto &[v, ls] : mp) {
        for (auto &[d, c] : ls) {
            if (k - d >= 0 and rec.count(k - d)) {
                res = min(res, rec[k - d] + c);
            }
        }

        for (auto &[d, c] : ls) {
            if (rec.count(d)) rec[d] = min(rec[d], c);
            else rec[d] = c;
        }
    }

    for (auto &[v, ww] : adj[cen]) {
        if (good[v]) {
            res = min(res, dnc(v));
        }
    }

    return res;
}

int best_path(int N, int K, int H[][2], int L[]) {
    n = N, k = K;
    
    adj.assign(n, {});
    for (int i = 0; i < N - 1; i++) {
        auto [u, v] = H[i];
        ll w = L[i];
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    good.assign(n, true);
    sz.resize(n);
    ll ans = dnc(0);

    return (ans == LLONG_MAX ? -1 : ans);
}
