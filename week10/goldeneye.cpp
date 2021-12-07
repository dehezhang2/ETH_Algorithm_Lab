///2
#include <iostream>
#include <vector>
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
int t, n, m;
long p;

struct Edge {
  K::FT dist;
  int from, to;
  const bool operator<(const Edge e) const {
    return dist < e.dist;
  }
};

double ceil_to_double(const K::FT &x) {
    double a = std::ceil(CGAL::to_double(x));
    while (a < x)
        a += 1;
    while (a - 1 >= x)
        a -= 1;
    return a;
}

void solve(){
    cin >> n >> m >> p;
    vector< pair<Point, int> > pts(n);
    for(int i = 0; i < n; i++){
        cin >> pts[i].first;
        pts[i].second = i;
    } 
    Triangulation t;
    t.insert(pts.begin(), pts.end());

    uf emst_p(n);
    vector<Edge> edge_list;
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        auto from = e->first->vertex((e->second+1)%3);
        auto to = e->first->vertex((e->second+2)%3);
        K::FT dist = CGAL::squared_distance(from->point(), to->point());
        if(dist <= p){
            emst_p.union_set(from->info(), to->info());
        }
        Edge edge; edge.dist = dist; edge.from = from->info(); edge.to = to->info();
        edge_list.push_back(edge);
    }
    vector<K::FT> max_of_first_last_dist_list(m);
    vector< pair<int, int> > from_closest_to_closest_pair_list(m);
    vector<bool> result_list(m);
    for(int i = 0; i < m; i++){
        Point from, to; cin >> from >> to;
        auto from_closest = t.nearest_vertex(from);
        auto to_closest = t.nearest_vertex(to);
        K::FT dist_from = CGAL::squared_distance(from, from_closest->point());
        K::FT dist_to = CGAL::squared_distance(to, to_closest->point());
        max_of_first_last_dist_list[i] = max(dist_from, dist_to);
        from_closest_to_closest_pair_list[i] = make_pair(from_closest->info(), to_closest->info());
        result_list[i] = (max_of_first_last_dist_list[i] <= p/4.0 && emst_p.find_set(from_closest->info()) == emst_p.find_set(to_closest->info()) );
        cout << (result_list[i] ? "y":"n");
    }
    cout << endl;
    // for each source -> target, add edge util they are connected => save the max edge
    sort(edge_list.begin(), edge_list.end());
    uf emst_a(n);
    K::FT max_dist_all = 0;
    int j = 0;
    for(int i = 0; i < m; i++){
        max_dist_all = max(max_dist_all, max_of_first_last_dist_list[i] * 4.0);
        for(; emst_a.find_set(from_closest_to_closest_pair_list[i].first) != emst_a.find_set(from_closest_to_closest_pair_list[i].second); j++){
            emst_a.union_set(edge_list[j].from, edge_list[j].to);
            max_dist_all = max(max_dist_all, edge_list[j].dist);
        }
    }

    uf emst_b(n);
    K::FT max_dist_part = 0;
    j = 0;
    for(int i = 0; i < m; i++){
        if(result_list[i]){
            max_dist_part = max(max_dist_part, max_of_first_last_dist_list[i] * 4.0);
            for(; emst_b.find_set(from_closest_to_closest_pair_list[i].first) != emst_b.find_set(from_closest_to_closest_pair_list[i].second); j++){
                emst_b.union_set(edge_list[j].from, edge_list[j].to);
                max_dist_all = max(max_dist_part, edge_list[j].dist);
            }
        }
    }
    cout << fixed << setprecision(0) << ceil_to_double(max_dist_all) << endl << ceil_to_double(max_dist_part) << endl;
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