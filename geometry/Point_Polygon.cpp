#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sp <<" "<<
#define endl "\n"

const ld EPS = 1e-3;

struct Point {
    ld x, y;
    
    Point(ld x = 0, ld y = 0) : x(x), y(y) {;;}

    bool operator==(Point p) const { return tie(x, y) == tie(p.x, p.y); }

    Point operator+(Point p) const { return Point(x+p.x, y+p.y); }
    Point operator-(Point p) const { return Point(x-p.x, y-p.y); }
    Point operator*(ld d) const { return Point(x*d, y*d); }
    Point operator/(ld d) const { return Point(x/d, y/d); }

    ld dist2() const { return x*x + y*y; }
    ld dist() const { return sqrtl(dist2()); }

    ld dot(Point p) const { return x*p.x + y*p.y; }
    ld angle() const { return atan2(y, x); }

    ld cross(Point p) const { return x*p.y - y*p.x; }
    ld cross(Point a, Point b) const { return (a-*this).cross(b-*this); }

    Point unit() const { return *this/dist(); }
    Point rotate(ld a) const { return Point(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a)); }

    friend ostream& operator<<(ostream &os, Point p) {
        // return os << "(" << p.x << ", " << p.y << ")";
        return os << p.x << " " << p.y;
    }
};

struct Polygon {
    int id;
    vector<Point> poly;

    Polygon(int id = -1) : id(id) {;;}

    void input(ll sz) { 
        while (sz--) {
            ld x, y; cin >> x >> y;
            add(Point(x, y));
        }
    }

    void add(Point p) { poly.push_back(p); }
    void add(vector<Point> pp) { for (auto &p : pp) poly.push_back(p); }
    void set(vector<Point> pp) { poly = pp; }
    Point get(ll i) { return poly[i]; } // DANGER
    ll size() const { return poly.size(); }

    ld height() const { return (poly[0]-poly[1]).dist(); } // DANGER
    ld width() const { return (poly[1]-poly[2]).dist(); } // DANGER
    void shift(Point s) { for (auto &p : poly) p = p + s; }

    ld area() const {
        ld res = 0.0;
        int n = poly.size();

        for (int i = 0; i < n; i++) {
            int a = i, b = (i+1) % n;
            Point A = poly[a], B = poly[b];

            res += A.cross(B);
        }

        return abs(res / 2.0);
    }

    void clear() { id = -1, poly.clear(); }

    friend ostream& operator<<(ostream &os, Polygon poly) {
        int n = poly.size();
        os << n << " ";
        for (int i = 0; i < n; i++) {
            if (i) os << " ";
            os << poly.poly[i];
        }

        return os;
    }
};

int ID = 1;
vector<vector<Polygon>> construct, decomp;

void performCuts(const Polygon &poly, vector<Polygon> &pieces) {
    cout << "scissors" << endl;
    cout << poly.id << " " << pieces.size() << endl;
    // cerr << poly.id sp poly << endl;

    for (auto &piece : pieces) {
        piece.id = ID++;
        cout << piece << endl;
    }
}

void performPaste(Polygon &poly, vector<Polygon> &pieces) {
    cout << "tape" << endl;
    cout << pieces.size() << " ";

    for (auto &piece : pieces) {
        cout << piece.id << " ";
    }   cout << endl;

    for (auto &piece : pieces) {
        cout << piece << endl;
    }

    poly.id = ID++;
    cout << poly << endl;
}

// Check if P is in ABC
bool inTriangle(Point p, Point a, Point b, Point c) {
    ld area = abs(a.cross(b, c));
    ld a1 = abs(a.cross(b, p)), a2 = abs(b.cross(c, p)), a3 = abs(c.cross(a, p));
    return abs(area - (a1 + a2 + a3)) < EPS;
}

pair<Polygon, Polygon> decomposeTriangle(Polygon poly) {
    pair<Polygon, Polygon> res;

    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int a = i, b = (i+1) % n, c = (i+2) % n;
        Point A = poly.get(a), B = poly.get(b), C = poly.get(c);

        if (A.cross(B, C) < 0) continue;

        bool convex = true;
        for (int j = 0; j < n; j++) {
            if (j == a or j == b or j == c) continue;
            if (inTriangle(poly.get(j), A, B, C)) {
                convex = false;
                break;
            }
        }

        if (!convex) continue;

        res.first.add({A, B, C});

        for (int j = 0; j < n; j++) {
            if (j == b) continue;
            res.second.add(poly.get(j));
        }

        return res;
    }

    assert(false);
    return res;
}

// Decompose a polygon into triangles
vector<Polygon> decomposeTriangles(Polygon poly, bool apply) {
    vector<Polygon> processed, unprocessed;

    unprocessed.push_back(poly);

    while (!unprocessed.empty()) {
        auto C = unprocessed.back(); unprocessed.pop_back();
        if (C.size() == 3) { processed.push_back(C); continue; }
        auto [A, B] = decomposeTriangle(C);

        A.size() > 3 ? unprocessed.push_back(A) : processed.push_back(A);
        B.size() > 3 ? unprocessed.push_back(B) : processed.push_back(B);
    }

    if (apply) performCuts(poly, processed);

    return processed;
}

// Compose rectangles from triangles (not optimal cut usage)
vector<Polygon> composeRectangles(vector<Polygon> &pieces, bool apply) {
    vector<Polygon> res;

    for (auto &piece : pieces) {
        Point A, B, C, D;

        int n = piece.size();
        assert(n == 3);

        // Find longest height to:
        // - guarantee altitude is inside the triangle
        // - splitting by the altitute results in two triangles
        for (int i = 0; i < n; i++) {
            int u = i, v = (i+1) % n, w = (i+2) % n;
            Point U = piece.get(u), V = piece.get(v), W = piece.get(w);
            if ((U-V).dist() > (A-B).dist()) { A = U, B = V, C = W; }
        }

        // Dear Prof. Schneider, I finally used something you taught me.
        // Project AC onto AB
        {
            Point u = B - A, v = C - A;
            D = A + (u * (v.dot(u) / u.dot(u)));
        }

        // 90-degree check
        assert((B-D).dot(C-D) < EPS);

        // Split into two right triangles
        vector<Polygon> right(2), cuts, pastes;
        Point E, F;

        right[0].add({A, D, C});
        right[1].add({C, D, B});

        if (apply) performCuts(piece, right);

        {
            // Split into a trapezoid and right triangle
            // Similar triangles
            Point M = (C+D) / 2;
            Point N = (A+C) / 2;

            vector<Polygon> split(2);

            split[0].add({A, D, M, N});
            split[1].add({N, M, C});

            if (apply) performCuts(right[0], split);
            else pastes.push_back(split[0]), pastes.push_back(split[1]);

            // Combine into a rectangle
            E = (A-D) + M;

            split[1].set({N, E, A});

            cuts.push_back(split[0]);
            cuts.push_back(split[1]);
        }

        {
            // Split into a trapezoid and right triangle
            // Similar triangles
            Point M = (C+D) / 2;
            Point N = (B+C) / 2;

            vector<Polygon> split(2);

            split[0].add({D, B, N, M});
            split[1].add({M, N, C});

            if (apply) performCuts(right[1], split);
            else pastes.push_back(split[0]), pastes.push_back(split[1]);

            // Combine into a rectangle
            F = (B-D) + M;

            split[1].set({F, N, B});

            cuts.push_back(split[0]);
            cuts.push_back(split[1]);
        }

        Polygon G;
        G.set({A, B, F, E});

        if (apply) performPaste(G, cuts);
        else construct.push_back(cuts), decomp.push_back(pastes);

        res.push_back(G);
    }

    return res;
}

vector<Polygon> normalizeRectangles(vector<Polygon> &pieces, vector<ld> &heights, bool apply) {
    vector<Polygon> res;

    assert(pieces.size() == heights.size());

    int n = pieces.size();
    for (int i = 0; i < n; i++) {
        Polygon piece = pieces[i];

        assert(piece.size() == 4);
        ld h = piece.height();

        // Two cases: smaller or larger

        if (h > heights[i]) {
            while (h > 2 * heights[i]) {
                Point A, B, C, D, E, F, G, H, S;
                A = piece.get(0);
                B = piece.get(1);
                C = piece.get(2);
                D = piece.get(3);
                S = D - A;
                E = (A + B) / 2;
                F = E + S;
                G = F + S;
                H = D + S;

                vector<Polygon> split(2);
                split[0].set({A, E, F, D});
                split[1].set({E, B, C, F});
                performCuts(piece, split);

                piece.set({A, E, G, H});
                split[1].set({D, F, G, H});
                performPaste(piece, split);

                h = piece.height();
            }
        }
        
        else {
            while (h < heights[i]) {
                Point A, B, C, D, E, F, G, H, S;
                A = piece.get(0);
                B = piece.get(1);
                C = piece.get(2);
                D = piece.get(3);
                S = B - A;
                E = (A + D) / 2;
                F = E + S;
                G = F + S;
                H = B + S;

                vector<Polygon> split(2);
                split[0].set({A, B, F, E});
                split[1].set({E, F, C, D});
                performCuts(piece, split);

                piece.set({A, H, G, E});
                split[1].set({B, H, G, F});
                performPaste(piece, split);

                h = piece.height();
            }
        }

        // We now cannot perform more mul/div by 2 operations
        // Shift by dh in at most 2 cuts
        ld dh = h - heights[i];
        Point A, B, C, D, E, F, G, H, S, T;
        A = piece.get(0);
        B = piece.get(1);
        C = piece.get(2);
        D = piece.get(3);
        S = (B - A).unit() * dh;
        E = A + S;
        F = C - S;
        G = B - S;
        ld pr = (E - A).dist() / (G - A).dist();
        T = (F - A).unit() * (F - A).dist() * pr;
        H = A + T;

        vector<Polygon> split(3);
        split[0].set({E, B, C, F, H});
        split[1].set({A, F, D});
        split[2].set({A, E, H});

        performCuts(piece, split);

        // Let D be stationary
        Point nA, nB, nC, Q;
        ld dw = (H - E).dist();
        Q = (A - D).unit() * dw;
        split[0].shift(Q - S);
        split[2].set({F+Q-S, C+Q-S, F});

        piece.set({A+Q, G+Q, F, D});

        performPaste(piece, split);

        res.push_back(piece);
    }

    return res;
}

Polygon combineRectangle(vector<Polygon> &pieces, ld height) {
    // Stack all pieces together
    Polygon res;
    ld width = 0;

    for (auto &piece : pieces) {
        ld w = piece.width();

        Point A(0, height), B(0, 0), C(w, 0), D(w, height), S(width, 0);
        piece.set({A+S, B+S, C+S, D+S});

        width += w;
    }

    Point A(0, height), B(0, 0), C(width, 0), D(width, height);
    res.set({A, B, C, D});

    performPaste(res, pieces);

    return res;
}

vector<Polygon> separateRectangle(Polygon rect, vector<Polygon> &pieces, ld height) {
    vector<Polygon> res;

    for (auto &piece : pieces) {
        ld area = piece.area();
        ld width = area / height;

        if (abs(rect.width() - width) < EPS) {
            res.push_back(rect);
            continue;
        }

        Point A, B, C, D, E, F, S;
        A = rect.get(0);
        B = rect.get(1);
        C = rect.get(2);
        D = rect.get(3);
        E = D - width;
        F = C - width;

        vector<Polygon> split(2);
        split[0].set({A, B, F, E});
        split[1].set({E, F, C, D});
        
        performCuts(rect, split);

        rect = split[0];
        res.push_back(split[1]);

        assert(abs(split[1].area() - area) < EPS);
    }

    return res;
}

pair<Point, ld> findTransformation(const Polygon &source, const Polygon &target) {
    assert(source.size() == target.size());
    
    Point s1 = source.poly[0], s2 = source.poly[1];
    Point t1 = target.poly[0], t2 = target.poly[1];
    
    Point translation = t1 - s1;
    
    Point sv = s2 - s1;
    Point tv = t2 - t1;
    ld angle = tv.angle() - sv.angle();
    
    return {translation, angle};
}

Point transformPoint(const Point &p, const Point &center, const Point &translation, ld angle) {
    Point translated = p - center;
    Point rotated = translated.rotate(angle);
    return rotated + center + translation;
}

vector<Polygon> composeTriangles(vector<Polygon> &pieces, vector<Polygon> &blueprint, vector<Polygon> &target) {
    vector<Polygon> res;

    assert(pieces.size() == blueprint.size());
    assert(pieces.size() == construct.size());
    assert(pieces.size() == decomp.size());

    int n = pieces.size();
    for (int i = 0; i < n; i++) {
        auto &piece = pieces[i];
        auto &blue = blueprint[i];
        
        auto [translation, angle] = findTransformation(blue, piece);
        Point center = blue.poly[0];
        
        vector<Polygon> relayed;
        for (auto &rpol : construct[i]) {
            Polygon transformed;
            transformed.id = rpol.id;
            
            for (int j = 0; j < rpol.size(); j++) {
                Point P = rpol.get(j);
                Point Q = transformPoint(P, center, translation, angle);
                transformed.add(Q);
            }
            
            relayed.push_back(transformed);
        }

        performCuts(piece, relayed);

        for (int j = 0; j < 4; j++) {
            decomp[i][j].id = relayed[j].id;
        }
        
        performPaste(target[i], decomp[i]);

        res.push_back(target[i]);
    }

    return res;
}

// https://oj.uz/problem/statistics/CEOI19_scissors
void solve() {
    Polygon S(0), T;
    int s; cin >> s; S.input(s);
    int t; cin >> t; T.input(t);

    ld h = sqrtl(T.area());

    vector<Polygon> U1 = decomposeTriangles(S, true);
    vector<Polygon> U2 = composeRectangles(U1, true);
    vector<ld> H1(U2.size(), h);
    vector<Polygon> U3 = normalizeRectangles(U2, H1, true);
    Polygon U4 = combineRectangle(U3, h);

    vector<Polygon> V1 = decomposeTriangles(T, false);
    vector<Polygon> V2 = composeRectangles(V1, false);
    vector<Polygon> V3 = separateRectangle(U4, V2, h);
    vector<ld> H2; for (auto &poly : V2) H2.push_back(poly.height());
    vector<Polygon> V4 = normalizeRectangles(V3, H2, true); 
    vector<Polygon> V5 = composeTriangles(V4, V2, V1);

    performPaste(T, V5);
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cout << fixed << setprecision(12);
    // cerr << fixed << setprecision(3);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
