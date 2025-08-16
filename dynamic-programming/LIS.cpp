#include "magic.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

vector<int> LIS(vector<int> &A) {
    int n = A.size();
    vector<int> res(n, 1), par(n, -1);

    for (int i = 1; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            if (A[i] > A[prev] && res[i] < res[prev] + 1) {
                res[i] = res[prev] + 1;
                par[i] = prev;
            }
        }
    }

    vector<int> lis;
    int at = max_element(res.begin(), res.end()) - res.begin();
    while (at != -1) {
        lis.push_back(A[at]);
        at = par[at];
    }
    reverse(lis.begin(), lis.end());

    return lis;
}

vector<int> LDS(vector<int> &A) {
    int n = A.size();
    vector<int> res(n, 1), par(n, -1);

    for (int i = 1; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            if (A[i] < A[prev] && res[i] < res[prev] + 1) {
                res[i] = res[prev] + 1;
                par[i] = prev;
            }
        }
    }

    vector<int> lds;
    int at = max_element(res.begin(), res.end()) - res.begin();
    while (at != -1) {
        lds.push_back(A[at]);
        at = par[at];
    }
    reverse(lds.begin(), lds.end());

    return lds;
}

// https://qoj.ac/contest/2415/problem/13651
vector<int> Alicia(vector<int> P) {
    {
        auto L = LIS(P);
        if (L.size() >= 16) {
            for (int i = 0, j = 0; i < P.size() and j < 16; i++) {
                if (P[i] == L[j]) {
                    P[i] = -1;
                    j++;
                }
            }
            return P;
        }
    }

    {
        auto L = LDS(P);
        if (L.size() >= 17) {
            for (int i = 0, j = 0; i < P.size() and j < 17; i++) {
                if (P[i] == L[j]) {
                    P[i] = -1;
                    j++;
                }
            }
            return P;
        }
    }

    return P;
}

vector<int> Beatriz(vector<int> Q) {
    set<int> st;
    for (int i = 1; i <= Q.size(); i++) st.insert(i);
    for (auto &x : Q) {
        if (x != -1) st.extract(x);
    }

    if (st.size() == 16) {
        for (auto &x : Q) {
            if (x == -1) {
                auto it = st.begin();
                x = *it;
                st.erase(it);
            }
        }
    } else {
        for (auto &x : Q) {
            if (x == -1) {
                auto it = prev(st.end());
                x = *it;
                st.erase(it);
            }
        }
    }

    return Q;
}
