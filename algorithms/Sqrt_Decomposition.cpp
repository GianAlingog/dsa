#include "elephants.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const int RES = 500;
const int INF = 1e9+5;

int n, l, b, c;

struct bucket {
    vector<int> a;
    vector<int> cost, end;

    bool below(int x) {
        if (a.empty()) return false;
        int l = a.front();
        return x <= l;
    }

    bool above(int x) {
        if (a.empty()) return true;
        int r = a.back();
        return r <= x;
    }

    bool check(int x) {
        if (a.empty()) return false;
        int l = a.front(), r = a.back();
        return l <= x and x <= r;
    }

    void insert(int x) {
        auto it = lower_bound(a.begin(), a.end(), x);
        a.insert(it, x);
    }

    void erase(int x) {
        auto it = lower_bound(a.begin(), a.end(), x);
        if (it == a.end() or *it != x) return;
        a.erase(it);
    }

    void compute() {
        int m = a.size();
        cost.assign(m, 0);
        end.assign(m, 0);

        int j = m;
        for (int i = m-1; i >= 0; i--) {
            while (j > i+1 and a[j-1] > a[i] + l) j--;
            if (j < m) {
                cost[i] = cost[j] + 1;
                end[i] = end[j];
            } else {
                cost[i] = 1;
                end[i] = a[i] + l;
            }
        }
    }
};

vector<int> x;
vector<bucket> buckets;

void build() {
    vector<int> r = x;
    sort(r.begin(), r.end());

    for (int i = 0; i < b; i++) {
        buckets[i].a.clear();
    }

    for (int i = 0; i < n; i++) {
        buckets[i / b].insert(r[i]);
    }

    for (int i = 0; i < b; i++) {
        buckets[i].compute();
    }
}

void init(int N, int L, int X[]) {
    n = N, l = L, c = 0;

    x.resize(N);
    for (int i = 0; i < N; i++) {
        x[i] = X[i];
    }

    b = sqrt(n) + 2;
    while (b * b >= n) b--;
    b++;
    buckets.resize(b);

    build();
}

int update(int i, int y) {
    int give = -1, take = -1;
    for (int j = 0; j < b; j++) {
        if (buckets[j].check(x[i])) {
            take = j;
        }
    }
    buckets[take].erase(x[i]);
    buckets[take].compute();
    x[i] = y;

    for (int j = 0; j < b; j++) {
        if (buckets[j].check(y)) {
            give = j;
        }
    }
    
    if (give == -1) {
        for (int j = 0; j < b; j++) {
            if (buckets[j].below(y)) {
                give = j;
                break;
            }
        }
    }

    if (give == -1) {
        for (int j = 0; j < b; j++) {
            if (buckets[j].above(y)) {
                give = j;
            }
        }
    }

    buckets[give].insert(y);
    buckets[give].compute();

    c++;
    if (c == RES) {
        c = 0;
        build();
    }

    int ans = 0, at = -INF;
    for (int j = 0; j < b; j++) {
        int idx = upper_bound(buckets[j].a.begin(), buckets[j].a.end(), at) - buckets[j].a.begin();
        if (idx < buckets[j].a.size()) {
            ans += buckets[j].cost[idx];
            at = buckets[j].end[idx];
        }
    }
    return ans;
}
