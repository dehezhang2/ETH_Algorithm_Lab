#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;
int t, n, m, k, T;

void build_tele_graph(weighted_graph& G, weight_map& weights, const vector<int>& tele_list){
    vector<int> component_map(n);	// We MUST use such a vector as an Exterior Property Map: Vertex -> Component
	int ncc = boost::strong_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 
    vector<int> component_cnt(ncc, -1);
    for(auto planet : tele_list){
        component_cnt[component_map[planet]]++;
    }
    // create vertual node for telegraph
    for(auto planet : tele_list){
        weights[boost::add_edge(planet, n + component_map[planet], G).first] = 0;
        weights[boost::add_edge(n + component_map[planet], planet, G).first] = component_cnt[component_map[planet]];
    }
}

int dijkstra(weighted_graph& G, int src){
    int n = boost::num_vertices(G);
    std::vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, src,
        boost::distance_map(boost::make_iterator_property_map(
        dist_map.begin(), boost::get(boost::vertex_index, G))));
    int min_dist = dist_map[0];
    for(int i = 0; i < k; i++){
        min_dist = min(min_dist, dist_map[i]);
    }
    return min_dist;
}

void solve(){
    cin >> n >> m >> k >> T;
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    vector<int> tele_list(T);
    for(int i = 0; i < T; i++){
        cin >> tele_list[i];
    }
    for(int i = 0 ; i < m; i++){
        int u, v, c; cin >> u >> v >> c;
        weights[boost::add_edge(v, u, G).first] = c;
    }
    build_tele_graph(G, weights, tele_list);
    int res = dijkstra(G, n-1);
    if(res <= 1000000){
        cout << res << endl;
    } else {
        cout << "no\n";
    }
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