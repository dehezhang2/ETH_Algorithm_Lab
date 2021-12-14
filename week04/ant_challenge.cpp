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

int t, n, e, s, a, b;

void kruskal(weighted_graph &G, weight_map &weights, weighted_graph &res_G, weight_map &res_weights){
    vector<edge_desc> mst;    // vector to store MST edges (not a property map!)
    boost::kruskal_minimum_spanning_tree(G, back_inserter(mst));
    for (auto it = mst.begin(); it != mst.end(); ++it) {
        auto e = boost::add_edge(boost::source(*it, G), boost::target(*it, G), res_G).first;
        res_weights[e] = weights[*it];
    }
}

int dijkstra_dist(const weighted_graph &G, int src, int tar) {
    int n = boost::num_vertices(G);
    vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, src,
        boost::distance_map(
            boost::make_iterator_property_map(
                dist_map.begin(), boost::get(boost::vertex_index, G)
            )
        )
    );
    return dist_map[tar];
}

void solve(){
    cin >> n >> e >> s >> a >> b;
    vector<weighted_graph> graphs_list(s, weighted_graph(n));
    vector<weight_map> weights_list;

    for(int i = 0; i < s; i++){
        weight_map weights = boost::get(boost::edge_weight, graphs_list[i]);
        weights_list.push_back(weights);
    }
    for(int i = 0; i < e; i++){
        int src, tar; cin >> src >> tar;
        for(int j = 0; j < s; j++){
            int weight;
            cin >> weight;
            auto e = boost::add_edge(src, tar, graphs_list[j]).first;
            weights_list[j][e] = weight;
        }
    }
    weighted_graph res_G(n);
    weight_map res_weights = boost::get(boost::edge_weight, res_G);
    for(int i=0; i<s; i++){
        int hive; cin >> hive;
        kruskal(graphs_list[i], weights_list[i], res_G, res_weights);
    }
    cout << dijkstra_dist(res_G, a, b)<<endl;
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