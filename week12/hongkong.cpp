///2
#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <queue>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator EdgeIt;
typedef Triangulation::All_faces_iterator FaceIt;
typedef Triangulation::Face_handle Face;
typedef K::FT FT;
typedef K::Point_2 Point;

using namespace std;

int t, n, m;
FT r;

void precompute(Triangulation& tri){
    priority_queue< pair<FT, Face> > q;
    for(auto face = tri.all_faces_begin(); face != tri.all_faces_end(); face++){
        if(tri.is_infinite(face)){
            q.push(make_pair(LONG_MAX, face));
            face->info() = LONG_MAX;
        } else {
            Point outheart = tri.dual(face);
            FT distance = CGAL::squared_distance(outheart, face->vertex(0)->point());
            q.push(make_pair(distance, face));
            face->info() = distance;
        }
    }

    while(!q.empty()){
        FT distance = q.top().first;
        Face current_face = q.top().second;
        q.pop();
        // current face is updated by another better face
        if(distance < current_face->info()) continue;
        for(int i = 0; i < 3; i++){
            Face next_face = current_face->neighbor(i);
            FT edge_length = tri.segment(current_face, i).squared_length();
            FT new_distance = min(current_face->info(), edge_length);
            if(new_distance > next_face->info()){
                q.push(make_pair(new_distance, next_face));
                next_face->info() = new_distance;
            }
        }
    }

}

void solve(){
    cin >> n >> m >> r;
    vector<Point> trees(n);
    for(int i = 0; i < n ; i++) {
        long x, y; cin >> x >> y;
        trees[i] = Point(x, y);
    }
    Triangulation tri; tri.insert(trees.begin(), trees.end());
    precompute(tri);

    for(int i = 0; i < m; i++){
        long x, y; FT s; cin >> x >> y >> s;
        Point ballon = Point(x, y);
        FT radii = r+s;
        Point closest = tri.nearest_vertex(ballon)->point();
        if(CGAL::squared_distance(ballon, closest) < radii * radii){cout << "n"; continue;}
        Face face = tri.locate(ballon);
        cout << ( face->info() < CGAL::square(2*radii) ? "n": "y");
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
