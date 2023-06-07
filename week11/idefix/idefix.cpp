#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2                                             Point;
typedef K::FT                                                  FT;

using namespace std;

int t, n, m, k;
FT s;
struct Edge{
    int from, to;
    FT dist;
    bool is_bone;
    bool operator<(const Edge& e) const{
        return dist < e.dist;
    }
};

void solve(){
    cin >> n >> m >> s >> k;
    vector< pair<Point, Index> > oaks(n);
    for(int i = 0; i < n; i++){
        cin >> oaks[i].first;
        oaks[i].second = i;
    }
    Triangulation t;
    t.insert(oaks.begin(), oaks.end());
    vector<Edge> edge_list;
    boost::disjoint_sets_with_storage<> emst1(n);
    for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++){
        Index from = e->first->vertex((e->second+1)%3)->info();
        Index to = e->first->vertex((e->second+2)%3)->info();
        FT distance = t.segment(e).squared_length();
        if(distance <= s){
            emst1.union_set(from, to);
        }
        edge_list.push_back((Edge){from, to, distance, false});
    }
    vector<int> bones_cnt_for_component(n, 0);
    Point bone; 
    for(int i = 0; i < m; i++){
        cin >> bone;
        auto closest_point = t.nearest_vertex(bone);
        FT distance = CGAL::squared_distance(closest_point->point(), bone) * 4;
        if(distance <= s){
            bones_cnt_for_component[emst1.find_set(closest_point->info())] ++;
        }
        edge_list.push_back((Edge){closest_point->info(), closest_point->info(), distance, true});
    }
    int a = -1;
    for(int bones_cnt : bones_cnt_for_component){
        a = max(a, bones_cnt);
    }
    boost::disjoint_sets_with_storage<> emst2(n);
    fill(bones_cnt_for_component.begin(), bones_cnt_for_component.end(), 0);
    sort(edge_list.begin(), edge_list.end());
    FT b = -1;
    for(auto edge : edge_list){
        if(edge.is_bone){
            int set_id = emst2.find_set(edge.from);
            bones_cnt_for_component[set_id]++;
            if(bones_cnt_for_component[set_id] >= k){
                b = edge.dist;
                break;
            }
        } else {
            int c1 = emst2.find_set(edge.from);
            int c2 = emst2.find_set(edge.to);
            if(c1 != c2){
                emst2.link(c1, c2);
                int new_set_id = emst2.find_set(edge.from);
                bones_cnt_for_component[new_set_id] = bones_cnt_for_component[c1] + bones_cnt_for_component[c2];
                if(bones_cnt_for_component[new_set_id] >= k){
                    b = edge.dist;
                    break;
                }
            }
        }
    }
    cout << a << " " << b << endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    std::size_t t;
    for (std::cin >> t; t > 0; --t) solve();
    return 0;
}