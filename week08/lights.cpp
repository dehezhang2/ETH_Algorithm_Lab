#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;

using namespace std;

int t, m, n;

void solve(){
    cin >> m >> n;
    vector< pair<Point, long> > peoples(m);
    vector<Point> lights(n);
    for(int i = 0; i < m; i++) cin >> peoples[i].first >> peoples[i].second;
    long h; cin >> h;
    for(int i = 0; i < n; i++) cin >> lights[i];
    Triangulation t;
    t.insert(lights.begin(), lights.end());

    // record the index of the light that killed peoples[i]
    vector<int> light_killers(m, n);       
    int light_kills_all = -1;

    for(int i = 0; i < m; i++){
        auto closest_light = t.nearest_vertex(peoples[i].first)->handle()->point();
        long int threshold = pow(h + peoples[i].second, 2);
        if(CGAL::squared_distance(closest_light, peoples[i].first) >= threshold){
            // at least one survived
            light_kills_all = n;
            continue;
        } else {
            for(int j = 0; j < n; j++){
                if(CGAL::squared_distance(lights[j], peoples[i].first) < threshold){
                    light_killers[i] = j;
                    j = n;
                }
            }
            light_kills_all = max(light_kills_all, light_killers[i]);
        }
    }
    for(int i = 0; i < m; i++){
        if(light_killers[i] == light_kills_all){
            cout << i << " ";
        }
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}