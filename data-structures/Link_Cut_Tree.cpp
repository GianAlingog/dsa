#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

struct Node {
    // 1-indexed nodes. 0 is a placeholder.
    ll ch[2]{0, 0}, fa{0};
    bool rev{false};
    ll val{0}, sum{0};
};

// to be quite honest, the splay tree is all i understand atm
// i am yet to fully grasp queries on LCT
struct LinkCutTree {
    ll N;
    vector<Node> t;

    LinkCutTree(ll n) { init(n); } // allow reinit
    void init(ll n) {
        N = n;
        t.assign(N+1, Node());
    }

    bool is_root(ll x) {
        ll f = t[x].fa;
        return f == 0 or (t[f].ch[0] != x and t[f].ch[1] != x);
    }

    void push_up(ll x) {
        t[x].sum = t[x].val +
                (t[x].ch[0] ? t[t[x].ch[0]].sum : 0) + 
                (t[x].ch[1] ? t[t[x].ch[1]].sum : 0);
    }

    void push_rev(ll x) {
        if (!x) return;
        swap(t[x].ch[0], t[x].ch[1]);
        t[x].rev ^= 1;
    }

    void push_down(ll x) {
        if (t[x].rev) {
            push_rev(t[x].ch[0]);
            push_rev(t[x].ch[1]);
            t[x].rev = false;
        }
    }

    void push_down_all(ll x) {
        static ll st[200005];
        ll top = 0, y = x;
        st[++top] = y;
        while (!is_root(y)) st[++top] = (y = t[y].fa);
        while(top) push_down(st[top--]);
    }

    void rotate(ll x) {
        ll y = t[x].fa, z = t[y].fa;
        ll dx = (t[y].ch[1] == x), dy = (t[z].ch[1] == y);
        if (!is_root(y)) t[z].ch[dy] = x;
        t[x].fa = z;

        t[y].ch[dx] = t[x].ch[dx ^ 1];
        if (t[x].ch[dx ^ 1]) t[t[x].ch[dx ^ 1]].fa = y;

        t[x].ch[dx ^ 1] = y;
        t[y].fa = x;

        push_up(y);
        push_up(x);
    }

    void splay(ll x) {
        push_down_all(x);
        while (!is_root(x)) {
            ll y = t[x].fa;
            if (!is_root(y)) {
                if ((t[t[y].fa].ch[0] == y) ^ (t[y].ch[0] == x)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
        push_up(x);
    }

    ll access(ll x) {
        ll last = 0;
        for (ll y = x; y; y = t[y].fa) {
            splay(y);
            t[y].ch[1] = last;
            push_up(y);
            last = y;
        }
        splay(x);
        return last;
    }

    void make_root(ll x) {
        access(x);
        push_rev(x);
    }

    ll find_root(ll x) {
        access(x);
        while (t[x].ch[0]) {
            push_down(x);
            x = t[x].ch[0];
        }
        splay(x);
        return x;
    }

    void link(ll x, ll y) {
        make_root(x);
        if (find_root(y) != x) {
            t[x].fa = y;
        }
    }

    void cut(ll x, ll y) {
        make_root(x);
        access(y);

        if (t[y].ch[0] == x and t[x].fa == y and t[x].ch[1] == 0) {
            t[y].ch[0] = 0;
            t[x].fa = 0;
            push_up(y);
        }
    }

    ll path_sum(ll x, ll y) {
        make_root(x);
        access(y);
        return t[y].sum;
    }

    void set_val(ll x, ll v) {
        access(x);
        t[x].val = v;
        push_up(x);
    }

    void reset(ll x, ll v = 0) {
        t[x].ch[0] = t[x].ch[1] = t[x].fa = 0;
        t[x].rev = false;
        t[x].val = v;
        t[x].sum = v;
    }
};

struct query {
    ll t, u, x;
    query(ll t = -1, ll u = -1, ll x = -1) : t(t), u(u), x(x) {;;}
};

struct fatty {
    ll l, r, p;
    bool alive = true;
};

struct node {
    ll id = -1, par = -1, val = 0;
    bool alive = true;
    vector<ll> adj;
};

void solve() {
    ll q; cin >> q;

    bool st2 = true;
    vector<query> queries;
    for (ll i = 0; i < q; i++) {
        string type; cin >> type;

        if (type == "GROW") {
            ll u, l; cin >> u >> l;
            if (l > 1) st2 = false;
            queries.emplace_back(0, u, l);
        } else if (type == "CUT") {
            ll u; cin >> u;
            queries.emplace_back(1, u, -1);
        } else if (type == "EDIT") {
            ll u, x; cin >> u >> x;
            queries.emplace_back(2, u, x);
        } else if (type == "ROOT") {
            ll u; cin >> u;
            queries.emplace_back(3, u, -1);
        } else assert(0);
    }

    if (!st2) {
        assert(q <= 1e3+5);
        vector<fatty> st;
        vector<set<ll>> col;
        vector<node> nodes;
        map<ll, ll> feli;
        node rt{0, -1, 0, true, {}};
        nodes.push_back(rt);
        feli[0] = 0;
        ll ri = 0;

        auto loc = [&](ll x) -> ll {
            // ll lo = 0, hi = st.size() - 1;
            // while (lo <= hi) {
            //     ll mi = (lo + hi) / 2;
            //     if (st[mi].l <= x) {
            //         if (x <= st[mi].r)
            //             return mi;
            //         lo = mi + 1;
            //     } else {
            //         hi = mi - 1;
            //     }
            // }

            for (int j = 0; j < st.size(); j++) {
                if (!st[j].alive) continue;
                if (st[j].l <= x and x <= st[j].r)
                    return j;
            }
            
            assert(0);
            return -1;
        };

        auto make = [&](ll x, ll pi) -> ll {
            node nd;
            nd.id = x;
            nd.par = pi;
            nd.val = 0;
            nd.alive = true;
            ll j = nodes.size();
            nodes.push_back(nd);
            if (pi != -1) nodes[pi].adj.push_back(j);
            return feli[x] = j;
        };

        auto fix = [&](ll ci, ll pi) -> void {
            ll oi = nodes[ci].par;
            if (oi == pi) return;
            if (oi != -1) {
                auto &g = nodes[oi].adj;
                auto it = find(g.begin(), g.end(), ci);
                if (it != g.end()) g.erase(it);
            }
            nodes[ci].par = pi;
            if (pi != -1) nodes[pi].adj.push_back(ci);
        };

        auto proc = [&](auto &&proc, ll x) -> ll {
            auto it1 = feli.find(x);
            if (it1 != feli.end()) return it1->second;
            if (x == 0) return ri;

            ll j = loc(x);
            auto &c = col[j];
            ll pi;
            auto it2 = c.lower_bound(x);
            if (it2 == c.begin()) pi = st[j].p;
            else pi = *(--it2);

            pi = proc(proc, pi);
            j = make(x, pi);

            auto it3 = c.insert(x).first;
            auto it4 = next(it3);
            if (it4 != c.end()) {
                ll o = *it4;
                ll oi = feli[o];
                fix(oi, j);
            }

            return j;
        };

        auto delr = [&](ll j, ll L, ll R) -> void {
            auto &c = col[j];
            auto it1 = c.lower_bound(L);
            while (it1 != c.end() and *it1 <= R) {
                auto it2 = feli.find(*it1);
                if (it2 != feli.end()) {
                    ll oi = it2->second;
                    if (oi >= 0 and oi < nodes.size())
                        nodes[oi].alive = false;
                    feli.erase(it2);
                }
                it1 = c.erase(it1);
            }
        };

        auto rem = [&](ll x) -> void {
            ll j = loc(x);
            ll L = st[j].l, R = st[j].r;

            if (!st[j].alive or x > R) return;

            queue<pair<ll, ll>> q;
            q.emplace(x, R);
            delr(j, x, R);
            st[j].r = x - 1;
            if (st[j].l > st[j].r) st[j].alive = false;

            while (!q.empty()) {
                auto [LL, RR] = q.front(); q.pop();
                for (int j = 0; j < st.size(); j++) {
                    if (!st[j].alive) continue;
                    ll p = st[j].p;
                    if (LL <= p and p <= RR) {
                        ll l = st[j].l, r = st[j].r;
                        st[j].alive = false;
                        delr(j, l, r);
                        q.emplace(l, r);
                    }
                }
            }
        };

        auto mx = [&]() -> ll {
            ll mx = 0;
            for (auto &s : st) {
                if (s.alive) mx = max(mx, s.r);
            }
            return mx;
        };

        for (ll i = 0; i < q; i++) {
            auto &[t, u, x] = queries[i];
            if (t == 0) {
                ll nn = mx();
                fatty nw;
                nw.l = nn + 1;
                nw.r = nn + x;
                nw.p = u;
                nw.alive = true;
                st.push_back(nw);
                col.emplace_back();
            } else if (t == 1) {
                rem(u);
            } else if (t == 2) {
                ll j = proc(proc, u);
                nodes[j].val = x;
            } else if (t == 3) {
                ll j = proc(proc, u);
                ll res = 0;
                while (j != -1) {
                    res += nodes[j].val;
                    j = nodes[j].par;
                }
                cout << res << endl;
            }
        }


    } else {
        ll n = q + 5;
        vector<ll> vals(n);
        LinkCutTree lct(n);
        vector<vector<ll>> adj(n);
        vector<ll> par(n, -1);
        vector<bool> alive(n);
        priority_queue<ll> pq;

        auto id = [&](ll i) -> ll {
            return i+1;
        };

        alive[0] = true;
        pq.push(0);

        auto mx = [&]() -> ll {
            while (!pq.empty() and !alive[pq.top()]) pq.pop();
            return pq.top();
        };

        auto rem = [&](ll st) -> void {
            queue<ll> q;
            q.emplace(st);

            while (!q.empty()) {
                auto u = q.front(); q.pop();
                if (!alive[u]) continue;
                alive[u] = false;
                par[u] = -1;

                for (auto &v : adj[u]) {
                    if (alive[v]) {
                        q.emplace(v);
                    }
                }

                vector<ll>().swap(adj[u]);
            }
        };

        for (ll i = 0; i < q; i++) {
            auto &[t, u, x] = queries[i];
            if (t == 0) {
                assert(x == 1);
                ll v = mx() + 1;
                alive[v] = true;
                par[v] = u;
                adj[u].push_back(v);
                pq.emplace(v);

                lct.reset(id(v));
                lct.link(id(v), id(u));
            } else if (t == 1) {
                if (alive[u]) {
                    ll p = par[u];
                    if (p != -1) {
                        lct.cut(id(u), id(p));
                        
                        auto it = find(adj[p].begin(), adj[p].end(), u);
                        assert(it != adj[p].end());
                        if (it != adj[p].end()) adj[p].erase(it);
                    }

                    rem(u);
                }
            } else if (t == 2) {
                lct.set_val(id(u), x);
            } else if (t == 3) {
                assert(alive[u]);
                cout << lct.path_sum(id(0), id(u)) << endl;
            }
        }
    }

    return;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    ll t = 1;
    // cin >> t;
    while (t--)
        solve();
}
