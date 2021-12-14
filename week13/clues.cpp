///1
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/connected_components.hpp>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Tds::Vertex_handle Vh;
typedef K::Point_2 Point;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_it;

typedef std::vector <boost::default_color_type> partition_t;
typedef typename boost::property_map <graph, boost::vertex_index_t>::type index_map_t;
typedef boost::iterator_property_map <partition_t::iterator, index_map_t> partition_map_t;

int t, n, m;
long r_square;

void addEdge_BFS(Vh vertex, Triangulation& tri, graph& G){
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
    vector< pair<Point, int> > stations(n);
    graph G(n);
    for(int i = 0; i < n; i++){
        cin >> stations[i].first;
        stations[i].second = i;
    }
    Triangulation tri;
    tri.insert(stations.begin(), stations.end());

    for(auto vertex = tri.finite_vertices_begin(); vertex != tri.finite_vertices_end(); vertex++) 
        addEdge_BFS(vertex, tri, G);
    
    bool network = boost::is_bipartite(G);

    vector<int> component_map(n);
    boost::connected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 

    for(int i = 0; i < m; i++){
        Point start, end; cin >> start >> end;
        if(!network){cout << "n"; continue;}
        Vh t1 = tri.nearest_vertex(start), t2 = tri.nearest_vertex(end);
        if( CGAL::squared_distance(start, end) <= r_square || 
            component_map[t1->info()] == component_map[t2->info()]&&
            CGAL::squared_distance(start, t1->point()) <= r_square &&
            CGAL::squared_distance(end, t2->point()) <= r_square
        ){
            cout << "y";  
        } else {
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