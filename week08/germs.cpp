#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <algorithm>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef K::Point_2 Point;
using namespace std;
int n, l, b, r, t;
double get_min_dist(const Point& p){
    double horizontal = min(CGAL::abs(p.x()-l), CGAL::abs(p.x()-r));
    double vertical = min(CGAL::abs(p.y()-b), CGAL::abs(p.y()-t));
    return min(horizontal, vertical);
}
double get_time(double dist){
    return ceil(CGAL::to_double(CGAL::sqrt(dist-0.5)));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> n && n){
        cin >> l >> b >> r >> t;
        vector<Point> pts; pts.reserve(n);
        for(int i = 0; i < n; i++){
           Point p; cin >> p;
           pts.emplace_back(p);
        }
        Triangulation t;
        t.insert(pts.begin(), pts.end());
        vector<double> dists;
        for(Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){
            Triangulation::Edge_circulator e = t.incident_edges(v);
            double min_dist = pow(get_min_dist(v->point()), 2) * 4;
            if(e!=0){
                do {
                    if (!t.is_infinite(e)) {
                        double dist = t.segment(e).squared_length();
                        min_dist = min(dist, min_dist);
                    }
                } while (++e != t.incident_edges(v));
            }
            dists.push_back(min_dist);
        }
        sort(dists.begin(), dists.end());
        cout << fixed << setprecision(0);
        cout << get_time(CGAL::sqrt(dists[0]/4.0)) << " " << get_time(CGAL::sqrt(dists[n/2]/4.0)) << " " << get_time(CGAL::sqrt(dists[n-1]/4.0)) << endl;
    }
    return 0;
}