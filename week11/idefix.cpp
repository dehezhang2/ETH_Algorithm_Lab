///2
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef K::Point_2 Point;

#include <boost/pending/disjoint_sets.hpp>
typedef boost::disjoint_sets_with_storage<> uf;

using namespace std;
int t, n, m, k;
long s;

struct Edge {
  K::FT dist;
  int from, to;
  bool is_bone;
  const bool operator<(const Edge e) const {
    return dist < e.dist;
  }
};

void solve(){
    cin >> n >> m >> s >> k;
    vector< pair<Point, int> > oak_trees(n); // point, index
    for(int i = 0; i < n; i++){
        cin >> oak_trees[i].first;
        oak_trees[i].second = i;
    }
    Triangulation t;
    t.insert(oak_trees.begin(), oak_trees.end());

    uf emst(n);
    vector<Edge> edge_list;
    
    // union all the dist that is smaller than s
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        auto from = e->first->vertex((e->second+1)%3);
        auto to = e->first->vertex((e->second+2)%3);
        K::FT dist = CGAL::squared_distance(from->point(), to->point());
        if(dist <= s){
            emst.union_set(from->info(), to->info());
        }
        Edge edge; edge.dist = dist; edge.from = from->info(); edge.to = to->info(); edge.is_bone = false;
        edge_list.push_back(edge);
    }
    
    vector<int> set_cnt(n, 0);
    vector< K::FT> bones(m);                                // distance to the closest
    vector< vector<int> > covered_bones(n, vector<int>());
    for(int i = 0; i < m; i++) {
        Point bone; cin >> bone;
        auto closest_oak = t.nearest_vertex(bone);
        K::FT closest_dist = CGAL::squared_distance(bone, closest_oak->point()) * 4.0;
        bones[i] = closest_dist;
        Edge edge; edge.dist = closest_dist; edge.from = closest_oak->info(); edge.to = closest_oak->info(); edge.is_bone = true;
        edge_list.push_back(edge);
        if( closest_dist <= s ){
            int set_id = emst.find_set(closest_oak->info());
            set_cnt[set_id]++;
        }
    }

    int max_bones = -1;
    for (int i = 0; i < (int)set_cnt.size(); i++) {
        if(max_bones < set_cnt[i]){
            max_bones = set_cnt[i];
        }
    }

    uf emst2(n);
    fill(set_cnt.begin(), set_cnt.end(), 0);
    sort(edge_list.begin(), edge_list.end());
    long q = 0;
    for(auto& edge : edge_list){
        if(edge.is_bone){
            int set_id = emst2.find_set(edge.from);
            set_cnt[set_id]++;
            if(set_cnt[set_id] >= k){
                q = edge.dist;
                break;
            }
        }
        else {
            int set1_id = emst2.find_set(edge.from);
            int set2_id = emst2.find_set(edge.to);
            if(set1_id != set2_id){
                emst2.link(set1_id, set2_id);
                int newid = emst2.find_set(edge.from);
                set_cnt[newid] = set_cnt[set1_id] + set_cnt[set2_id];
                if(set_cnt[newid] >= k){
                    q = edge.dist;
                    break;
                }
            }
        }
    }
    cout << max_bones << " " << q << endl;
    
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