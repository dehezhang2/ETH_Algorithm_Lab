#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace std;
// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor > > > > graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder {
    graph &G;
  public:
    explicit edge_adder(graph &G) : G(G) {}
    void add_edge(int from, int to, long capacity) {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        const auto e = boost::add_edge(from, to, G).first;
        const auto rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }
};
int t, n, m, s, d;
const bool in = 0;
const bool out = 1;
int get_node(int id, bool node_type){ 
    return node_type ? n+id : id;
}

void solve(){
    cin >> n >> m >> s >> d;
    graph G(2*n+2);
    const vertex_desc v_src = 2*n;
    const vertex_desc v_tar = 2*n + 1;
    edge_adder adder(G);
    for(int i = 0; i < n; i++) adder.add_edge(get_node(i, in), get_node(i, out), 1);
    for(int i = 0; i < m; i++){
        int from, to; cin >> from >> to;
        adder.add_edge(get_node(from, out), get_node(to, in), 1);
    }
    for(int i = 0; i < s; i++){
        int start_planet; cin >> start_planet;
        adder.add_edge(v_src, get_node(start_planet, in), 1);
    }
    for(int i = 0; i < d; i++){
        int end_planet; cin >> end_planet;
        adder.add_edge(get_node(end_planet, out), v_tar, 1);
    }
    long flow = boost::push_relabel_max_flow(G, v_src, v_tar);
    cout << flow << endl;
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