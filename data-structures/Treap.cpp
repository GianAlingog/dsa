#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

struct node {
    ll val, prior, sum, sz;
    node *l, *r, *p;
    node(ll val, ll prior) :
        val(val), prior(prior), l(nullptr), r(nullptr), p(nullptr),
        sz(1), sum(val)
    {;;}
};

void pull(node *t) {
    if (!t) return;
    t->sz = 1 + (t->l ? t->l->sz : 0) + (t->r ? t->r->sz : 0);
    t->sum = t->val + (t->l ? t->l->sum : 0) + (t->r ? t->r->sum : 0);
    if (t->l) t->l->p = t;
    if (t->r) t->r->p = t;
}

pair<node*, node*> split(node *t, int k) {
    if (!t) return {nullptr, nullptr};
    if ((t->l ? t->l->sz : 0) >= k) {
        auto res = split(t->l, k);
        t->l = res.second;
        if (t->l) t->l->p = t;
        pull(t);
        if (res.first) res.first->p = nullptr;
        return {res.first, t};
    } else {
        auto res = split(t->r, k - (t->l ? t->l->sz : 0) - 1);
        t->r = res.first;
        if (t->r) t->r->p = t;
        pull(t);
        if (res.second) res.second->p = nullptr;
        return {t, res.second};
    }
}

node* merge(node *a, node *b) {
    if (!a or !b) {
        node *t = a ? a : b;
        if (t) t->p = nullptr;
        return t;
    }

    if (a->prior < b->prior) {
        a->r = merge(a->r, b);
        if (a->r) a->r->p = a;
        pull(a);
        a->p = nullptr;
        return a;
    } else {
        b->l = merge(a, b->l);
        if (b->l) b->l->p = b;
        pull(b);
        b->p = nullptr;
        return b;
    }
}

int find(node *t) {
    int res = (t->l ? t->l->sz : 0);
    while (t->p) {
        if (t->p->r == t) res += (t->p->l ? t->p->l->sz : 0) + 1;
        t = t->p;
    }
    return res;
}

void del(node *t, vector<node*> &pos) {
    if (!t) return;

    vector<node*> st;
    st.push_back(t);

    while (!st.empty()) {
        node *u = st.back(); st.pop_back();
        if (u->l) st.push_back(u->l);
        if (u->r) st.push_back(u->r);
        pos[u->val] = nullptr;
        delete u;
    }
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int q; cin >> q;

    vector<node*> pos(q+5, nullptr);
    node *root = new node(0, rng());
    pos[0] = root;

    for (int i = 1; i <= q; i++) {
        int type; cin >> type;

        if (type == 1) {
            int x; cin >> x;
            node *nx = pos[x];
            int ind = find(nx);

            auto res = split(root, ind + 1);
            node *nw = new node(i, rng());
            pos[i] = nw;
            root = merge(merge(res.first, nw), res.second);
        } else {
            int x, y; cin >> x >> y;
            node *nx = pos[x], *ny = pos[y];
            int indx = find(nx), indy = find(ny);
            if (indx > indy) swap(indx, indy);

            int amt = indy - indx - 1;
            if (amt <= 0) {
                cout << 0 << endl;
                continue;
            }

            auto r1 = split(root, indx + 1);
            auto r2 = split(r1.second, amt);

            cout << (r2.first ? r2.first->sum : 0) << endl;

            del(r2.first, pos);
            root = merge(r1.first, r2.second);
        }
    }

    // range deletion....
    // feels like tree structure needed, BST
    // we store the positions in the tree
    // then deleting everything in range means removing a subtree
    // i will totally pull a red black tree here
    // just recalculate values after rebalancing
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
