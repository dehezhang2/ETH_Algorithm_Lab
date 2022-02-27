///1
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <climits>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_2<K>                   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<Index, K>    Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef Tds::Vertex_handle                                     Vh;
typedef Triangulation::Face_handle                             Face;
typedef K::Point_2                                             Point;
typedef K::FT                                                  FT;

using namespace std;

void dijkstra_construction(Triangulation& t){
    priority_queue< pair<FT, Face> > queue;
    for(auto f = t.all_faces_begin(); f != t.all_faces_end(); f++){
        if(t.is_infinite(f)){
            queue.push(make_pair(LONG_MAX, f));
            f->info() = LONG_MAX;
        } else {
            queue.push(make_pair(0,f));
            f->info() = 0;
        }
    }
    while(!queue.empty()){
        FT clearance = queue.top().first;
        Face current_face = queue.top().second; queue.pop();
        if(current_face->info() > clearance) continue;
        for(int i = 0; i < 3; i++){
            Face next_face = current_face->neighbor(i);
            FT new_clearance = CGAL::min(clearance, t.segment(current_face, i).squared_length());
            if(next_face->info() < new_clearance){
                next_face->info() = new_clearance;
                queue.push(make_pair(new_clearance, next_face));
            }
        }
    }
}

int n, m;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> n && n){
        vector<Point> infected(n);
        for(int i = 0; i < n; i++){
            cin >> infected[i];
        }
        Triangulation t; t.insert(infected.begin(), infected.end());
        dijkstra_construction(t);
        cin >> m;
        Point query; FT d;
        for(int i = 0; i < m; i++){
            cin >> query >> d;
            bool feasible = (CGAL::squared_distance(query, t.nearest_vertex(query)->point()) >= d) 
                        && (t.locate(query)->info() >= d*4);
            cout << (feasible ? "y" : "n");
        }
        cout << endl;
    }
    return 0;
}