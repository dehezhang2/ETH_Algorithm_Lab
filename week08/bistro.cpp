///1
#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef K::Point_2 Point;
typedef CGAL::Gmpz ET;
using namespace std;

int n, m;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> n && n != 0){
        vector<Point> pts; pts.reserve(n);
        for(int i = 0; i < n; i++){
            Point p; cin >> p;
            pts.push_back(p);
        }
        Triangulation t;
        t.insert(pts.begin(), pts.end());
        cin >> m;
        for(int i = 0; i < m; i++){
            Point p; cin >> p;
            Point nearest = t.nearest_vertex(p)->point();
            cout << fixed << setprecision(0) << CGAL::squared_distance(p, nearest)<< endl;
        }
    }
    return 0;
}