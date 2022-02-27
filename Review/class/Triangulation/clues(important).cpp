#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
// BGL includes 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/bipartite.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>   graph;
typedef boost::graph_traits<graph>::vertex_descriptor   vertex_desc;// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<graph>::edge_iterator   edge_it;// to iterate over all edges

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2                                             Point;
typedef Tds::Vertex_handle                                 Vh;

using namespace std;
int t, n, m, r;
long r_square;

void BFS_construction(Vh vertex, Triangulation& tri, graph& G){
    set<Vh> visited;
    vector<Vh> queue; queue.push_back(vertex); visited.insert(vertex);
    while(!queue.empty()){
        auto next_vertex = queue[queue.size() - 1]; queue.pop_back();
        if(next_vertex != vertex) boost::add_edge(vertex->info(), next_vertex->info(), G);
        auto neighbor = next_vertex->incident_vertices();
        
        do {
            if (!tri.is_infinite(neighbor) && visited.find(neighbor) == visited.end() && CGAL::squared_distance(vertex->point(), neighbor->point()) <= r_square) {
                visited.insert(neighbor);
                queue.push_back(neighbor);
            }
        } while(++neighbor != next_vertex->incident_vertices());
    }
}

void solve(){
    cin >> n >> m >> r_square;
    r_square *= r_square;
    vector< pair<Point, int> > station_list(n);
    for(int i = 0; i < n; i++){
        cin >> station_list[i].first;
        station_list[i].second = i;
    }
    Triangulation t;
    t.insert(station_list.begin(), station_list.end());
    graph G(n);
    for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++){
        BFS_construction(v, t, G);
    }
    bool feasible = boost::is_bipartite(G);
    vector<int> component_map(n);
    int ncc = boost::connected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G)));

    for(int i = 0; i < m; i++){
        Point start, end; cin >> start >> end;
        if(!feasible) {cout << "n"; continue;}
        Vh station_start = t.nearest_vertex(start), station_end = t.nearest_vertex(end);
        if(
            CGAL::squared_distance(start, end) <= r_square ||
            (
                component_map[station_start->info()] == component_map[station_end->info()] &&
                CGAL::squared_distance(start, station_start->point())<= r_square &&
                CGAL::squared_distance(end, station_end->point())<= r_square
            )
        ){
            cout << "y";
        } else{
            cout << "n";
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