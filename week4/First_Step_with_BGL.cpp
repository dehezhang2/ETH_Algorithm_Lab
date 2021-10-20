#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
        boost::no_property, boost::property<boost::edge_weight_t, int> > weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type  weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor           vertex_desc;

int t, n, m;

int dijkstra_dist(const weighted_graph &G, int s) {
    int n = boost::num_vertices(G);
    vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, s,
        boost::distance_map(
            boost::make_iterator_property_map(
                dist_map.begin(), boost::get(boost::vertex_index, G)
            )
        )
    );
    int max_val = -1;
    for(auto dist:dist_map) max_val = max_val > dist ? max_val : dist;
    return max_val;
}

int kruskal(weighted_graph &G){
    std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
    weight_map weights = boost::get(boost::edge_weight, G);
    int res = 0;
    for (auto it = mst.begin(); it != mst.end(); ++it) {
        res += weights[*it];
    }
    return res;
}

void solve(){
    cin >> n >> m;
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    int src, tar, weight;
    edge_desc e;
    for(int i = 0; i < m; i++){
        cin >> src >> tar >> weight;
        e = boost::add_edge(src, tar, G).first;
        weights[e] = weight;
    }
    cout << kruskal(G) << " " << dijkstra_dist(G, 0)<<endl;
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