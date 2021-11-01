#include <iostream>
#include <climits>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
        boost::no_property, boost::property<boost::edge_weight_t, int> >    graph_t;
typedef boost::property_map<graph_t, boost::edge_weight_t>::type            weight_map;
typedef boost::graph_traits<graph_t>::edge_descriptor                       edge_desc;
typedef boost::graph_traits<graph_t>::vertex_descriptor                     vertex_desc;
int t, n, m, k, T;

void build_tele_edges(graph_t &G, weight_map &weights,const vector<int> &teles) {
    int n = boost::num_vertices(G);
    vector<int> scc_map(n); // exterior property map
    int nscc = boost::strong_components(G, boost::make_iterator_property_map(
        scc_map.begin(),
        boost::get(boost::vertex_index, G)
    ));

    vector<int> scc_count(nscc, -1);

    for(int i = 0; i < T; i++)
        scc_count[scc_map[teles[i]]]++;

    for(int i = 0; i < T; i++) {
        edge_desc e = boost::add_edge(teles[i], n+scc_map[teles[i]], G).first;
        weights[e] = 0;
        e = boost::add_edge(n+scc_map[teles[i]], teles[i], G).first;
        weights[e] = scc_count[scc_map[teles[i]]];
    }
}

int dijkstra_dist(const graph_t &G, int s) {
    int n = boost::num_vertices(G);
    vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, s,
        boost::distance_map(
            boost::make_iterator_property_map(
                dist_map.begin(), 
                boost::get(boost::vertex_index, G)
            )
        )
    );
    int min_dist = dist_map[0];
    for(int i=1; i<k; i++){
        min_dist = dist_map[i] < min_dist ? dist_map[i] : min_dist;
    }
    return min_dist;
}

void solve(){
    cin >> n >> m >> k >> T;
    vector<int> teles;
    for(int i = 0; i < T; i++){
        int t_i; cin >> t_i;
        teles.push_back(t_i);
    }
    graph_t G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    for(int i = 0; i < m; i++){
        int u, v, c; cin >> u >> v >> c;
        // inverse for dijkstra
        weights[boost::add_edge(v, u, G).first] = c;
    }
    build_tele_edges(G, weights, teles);
    int res = dijkstra_dist(G, n-1);
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