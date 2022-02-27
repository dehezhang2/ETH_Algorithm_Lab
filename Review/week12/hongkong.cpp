#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>

#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K>                   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K>     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2                                             Point;
typedef Triangulation::Face_handle                             Face;
using namespace std;

int t, n, m;
K::FT r;

void precompute(Triangulation& t){
    priority_queue< pair<K::FT, Face> > queue;
    for(auto f = t.all_faces_begin(); f != t.all_faces_end(); f++){
        if(t.is_infinite(f)){
            queue.push(make_pair(LONG_MAX, f));
        } else {
            Point outheart = t.dual(f);
            K::FT distance = CGAL::squared_distance(outheart, f->vertex(0)->point());
            queue.push(make_pair(distance, f));
            f->info() = distance;
        }
    }
    while(!queue.empty()){
        K::FT distance = queue.top().first;
        Face current_face = queue.top().second;
        queue.pop();
        if(distance < current_face->info()) continue;
        for(int i = 0; i < 3; i++){
            Face next_face = current_face->neighbor(i);
            K::FT new_distance = min(current_face->info(), t.segment(current_face, i).squared_length());
            if(new_distance > next_face->info()){
                next_face->info() = new_distance;
                queue.push(make_pair(new_distance, next_face));
            }
        }
    }
}

void solve(){
    cin >> n >> m >> r;
    vector <Point> trees(n);
    for(int i = 0; i < n; i++){
        cin >> trees[i];
    }
    Triangulation t; t.insert(trees.begin(), trees.end());
    precompute(t);
    for(int i = 0; i < m; i++){
        Point p; K::FT s;
        cin >> p >> s;
        Point closest = t.nearest_vertex(p)->point();
        K::FT radii = r + s;
        if(CGAL::squared_distance(closest, p) < CGAL::square(radii)){cout << "n";continue;}
        Face face = t.locate(p);
        cout << (face->info() < CGAL::square(2*radii) ? "n":"y");
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}
