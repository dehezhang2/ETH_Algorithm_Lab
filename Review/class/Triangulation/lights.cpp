#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <vector>
#include <algorithm>
#include <iostream>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_2<K>                   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2                                             Point;
typedef K::FT                                                  FT;

using namespace std;
int t, m, n;
FT h;

void solve(){
    cin >> m >> n;
    vector< pair<Point, FT> > peoples(m);
    vector<Point>  lamps(n);
    for(int i = 0; i < m; i++){
        cin >> peoples[i].first >> peoples[i].second;
    }
    cin >> h;
    for(int i = 0; i < n; i++){
        cin >> lamps[i];
    }
    int the_lamp_that_kills_all = -1;
    Triangulation t; t.insert(lamps.begin(), lamps.end());
    vector<int> killed_by(m, n);
    for(int i = 0; i < m; i++){
        FT radii = h + peoples[i].second;
        radii *= radii;
        if(CGAL::squared_distance(t.nearest_vertex(peoples[i].first)->point(), peoples[i].first) >= radii){
            the_lamp_that_kills_all = n;
        } else {
            for(int j = 0; j < n; j++){
                if(CGAL::squared_distance(lamps[j], peoples[i].first) < radii){
                    killed_by[i] = j;
                    break;
                }
            }
            the_lamp_that_kills_all = max(the_lamp_that_kills_all, killed_by[i]);
        }
    }
    for(int i = 0; i < m; i++){
        if(killed_by[i]==the_lamp_that_kills_all) cout << i << " ";
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}